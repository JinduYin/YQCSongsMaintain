#include "adwidget.h"
#include "pagingtableview.h"
#include "mysqlquery.h"
#include "tablemodel.h"
#include "defistruct.h"
#include "fmaddmodifydialog.h"
#include "enuminfo.h"
#include "songslistaddmodifydialog.h"
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QFile>
#include <QPainter>
#include <QTableView>
#include <QHBoxLayout>
#include <QVBoxLayout>
AdWidget::AdWidget(QWidget *parent)
    : QWidget(parent)
{
    initWidget();
    readAndSetStyleSheet();
    initWidgetValue();
    setWidgetSize();

    connect(tableView_Ad, &PagingTableView::updateView, this, &AdWidget::setAdValue);    
    connect(combobox_type, SIGNAL(currentIndexChanged(int)), this, SLOT(combobox_IndexChanged(int)));

    connect(tableView_Ad, &PagingTableView::moveUp, this, &AdWidget::moveUp);
    connect(tableView_Ad, &PagingTableView::moveDown, this, &AdWidget::moveDown);
    connect(tableView_Ad, &PagingTableView::currentRow, this, &AdWidget::deleteMusic);
    connect(tableView_Ad, &PagingTableView::play, this, &AdWidget::play);

    connect(pushButton_add, &QPushButton::clicked, this, &AdWidget::addMusic);
}

AdWidget::~AdWidget()
{

}

void AdWidget::readAndSetStyleSheet()
{
    QFile qss(":/qss/songquery.qss");
    qss.open(QFile::ReadOnly);
    this->setStyleSheet(qss.readAll());
    qss.close();

    this->setObjectName("Widget");
    widgetTitle->setObjectName("TopWidget");
    widgetCenter->setObjectName("CenterWidget");
    label_title->setObjectName("TitleLabel");
    pushButton_add->setObjectName("Button");
    combobox_type->setObjectName("Combobox");

    label_type->setObjectName("Label");    
}

void AdWidget::initWidget()
{
    widgetTitle = new QWidget(this);
    widgetCenter = new QWidget(this);
    label_title = new QLabel(widgetTitle);
    label_type = new QLabel(widgetCenter);
    pushButton_add = new QPushButton(widgetTitle);
    combobox_type = new QComboBox(widgetCenter);

    tableView_Ad = new PagingTableView(this);

    title_layout = new QHBoxLayout();
    title_layout->addWidget(label_title);
    title_layout->addStretch();
    title_layout->addWidget(pushButton_add);
    title_layout->setContentsMargins(20, 0, 24, 0);
    title_layout->setSpacing(0);

    widgetTitle->setLayout(title_layout);

    type_layout = new QHBoxLayout();
    type_layout->addWidget(label_type);
    type_layout->addWidget(combobox_type);
    type_layout->addStretch();
    type_layout->setContentsMargins(46, 20, 0, 20);
    type_layout->setSpacing(10);

    widgetCenter->setLayout(type_layout);

    tableView_layout = new QVBoxLayout();
    vLayout = new QVBoxLayout();

    tableView_layout->addWidget(tableView_Ad);
    tableView_layout->setContentsMargins(12, 20, 12, 3);
    tableView_layout->setSpacing(0);

    vLayout->addWidget(widgetTitle);
    vLayout->addWidget(widgetCenter);
    vLayout->addLayout(tableView_layout);
    vLayout->setContentsMargins(0, 0, 0, 0);
    vLayout->setSpacing(0);

    this->setLayout(vLayout);
}

void AdWidget::initWidgetValue()
{
    label_title->setText("广告歌曲");
    label_type->setText("歌曲类型");
    pushButton_add->setText("添加歌曲");

    QStringList type;
    type << "宣传歌曲" << "锁屏状态" << "开关机歌曲" << "大堂歌曲";
    combobox_type->addItems(type);
    combobox_type->setCurrentIndex(0);

    tableView_Ad->setAdDelegate();
}

void AdWidget::setWidgetSize()
{
    widgetTitle->setFixedHeight(60);
    pushButton_add->setFixedWidth(90);
    pushButton_add->setFixedHeight(36);

    combobox_type->setFixedWidth(150);
    combobox_type->setFixedHeight(36);
}

void AdWidget::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void AdWidget::initSql(MysqlQuery *sql)
{
    _sql = sql;
}

void AdWidget::setAdValue()
{
    query.clear();
    tableView_Ad->tableView->clear();
    QString type = getType();
    if(!_sql->queryMediaList(type, tableView_Ad->limitArgu,  query)) return;
    tableView_Ad->setTotal_Rows_Pages(query.size());

    tableView_Ad->showUploadMediaListData(query);
}

void AdWidget::combobox_IndexChanged(const int &)
{
    setAdValue();
}

QString AdWidget::getType()
{
    QString str = NULL;
    if(combobox_type->currentIndex() == 0)
        str = "ad_publicity";
    else if(combobox_type->currentIndex() == 1)
        str = "ad_lock";
    else if(combobox_type->currentIndex() == 2)
        str = "ad_shutdown";
    else if(combobox_type->currentIndex() == 3)
        str = "ad_hall";

    return str;
}

void AdWidget::getAdValue(const QSqlQuery &_query, MediaList &_list)
{
    _list.type =  getType();   //_query.value("_type").toString();
    _list.index = _query.value("_index").toString();
    _list.mid = _query.value("_mid").toString();
    _list.serial_id = _query.value("_serial_id").toString();
}

void AdWidget::moveUp(const int &row)
{
    if(row  <= 0)
        return;

    query.seek(row);

    MediaList ad, adPre;
    getAdValue(query, ad);

    if(!query.previous())
        return;
    getAdValue(query, adPre);

    if(_sql->updateMediaList(ad, adPre)){
       if(_sql->updateMediaList(adPre, ad));
       else
           _sql->updateMediaList(ad, adPre);
    }

    setAdValue();
}

void AdWidget::moveDown(const int &row)
{
    if(row >= query.size() - 1)
        return;
    query.seek(row);

    MediaList ad, adNext;
    getAdValue(query, ad);

    if(!query.next())
        return;
    getAdValue(query, adNext);

    if(_sql->updateMediaList(ad, adNext)){
        if(_sql->updateMediaList(adNext, ad));
        else
            _sql->updateMediaList(ad, adNext);
    }

    setAdValue();
}

void AdWidget::deleteMusic(const int &row)
{
    query.seek(row);
    MediaList ad;
    getAdValue(query, ad);

    if(_sql->deleteMedialist(ad))
        setAdValue();
}

void AdWidget::addMusic()
{
//    FmAddModifyDialog *ad = new FmAddModifyDialog();
//    connect(ad, SIGNAL(update_view()), this, SLOT(setAdValue()));
//    ad->setTitle("添加歌曲");
//    ad->setType_delegate(widItem_AD);
//    ad->initMediaList();
//    ad->initSql(_sql, query);
//    ad->initType(getType());
////    ad->setAdViewValue(getType());
//    ad->exec();

    SongsListAddModifyDialog *dialog = new SongsListAddModifyDialog();
    connect(dialog, SIGNAL(update_view(QList<Media>)),
            this, SLOT(insertMediaList(QList<Media>)));
    dialog->setTitle("添加歌曲");
    dialog->initSql(_sql, query);
    dialog->initType(getType(), widItem_AD);
    dialog->exec();
}

void AdWidget::insertMediaList(QList<Media> _media)
{
    QList<MediaList> addM;
    QStringList list;
    qint64 maxIndex = -1;
    _sql->getMaxMediaListIndex(maxIndex);
    if(maxIndex == -1)
        return;

    for(int i=0; i<_media.size(); i++){
        maxIndex++;
        MediaList media;
        QString tempStr;
        tempStr.append(QString("'%1'").arg(getType()));
        tempStr.append(", ");
        tempStr.append(QString::number(maxIndex));
        tempStr.append(", ");
        tempStr.append(_media.at(i).mid);

        list.append(tempStr);

        ///json使用
        media.index = QString::number(maxIndex);
        media.type = getType();
        media.serial_id = _media.at(i).serial_id;

        addM.append(media);
    }

    _sql->addMediaList(getType(), list, addM);
    setAdValue();
}

void AdWidget::play(const int &row, const int &)
{
    query.seek(row);
    QString path = query.value("_path").toString();
    tableView_Ad->palyVideo(path);
}


