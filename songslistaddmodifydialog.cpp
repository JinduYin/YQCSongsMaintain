#include "songslistaddmodifydialog.h"

#include "pagingtableview.h"
#include "tablemodel.h"
#include "enuminfo.h"
#include <QFile>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QPainter>
#include <QFileDialog>
#include <QStyleOption>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QDebug>

SongsListAddModifyDialog::SongsListAddModifyDialog(QWidget *parent)
    : DropShadowWidget(parent)
{
    setFixedHeight(650);
    setFixedWidth(900);
    _sql = NULL;

    initWidget();
    initWidgetValue();

    connect(pushButton_close, &QPushButton::clicked, this, &SongsListAddModifyDialog::close);
    connect(pushButton_search, &QPushButton::clicked, this, &SongsListAddModifyDialog::serachMusic);

    connect(view_music, &PagingTableView::currentRow, this, &SongsListAddModifyDialog::deleteMusic);
    connect(view_addMusic, &PagingTableView::currentRow, this, &SongsListAddModifyDialog::addMusicDetail);
    connect(pushButton_save, &QPushButton::clicked, this, &SongsListAddModifyDialog::save);

    connect(view_addMusic, &PagingTableView::play, this, &SongsListAddModifyDialog::playAddMusic);
    connect(view_music, &PagingTableView::play, this, &SongsListAddModifyDialog::play);
}

SongsListAddModifyDialog::~SongsListAddModifyDialog()
{

}

void SongsListAddModifyDialog::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void SongsListAddModifyDialog::initWidget()
{
    widgetTitle = new QWidget(this);
    widgetCenter = new QWidget(this);
    widgetBottom = new QWidget(this);

    label_title = new QLabel(widgetTitle);
    label_music = new QLabel(this);
    lineEdit_search = new QLineEdit(this);

    pushButton_close = new QPushButton(widgetTitle);
    pushButton_save = new QPushButton(this);
    pushButton_search = new QPushButton(lineEdit_search);

    view_addMusic = new PagingTableView(widgetCenter);
    view_music = new PagingTableView(widgetBottom);

    QHBoxLayout *title_layout = new QHBoxLayout();
    title_layout->addWidget(label_title);
    title_layout->addStretch();
    title_layout->addWidget(pushButton_close);
    title_layout->setContentsMargins(20, 0, 20, 0);
    title_layout->setSpacing(0);
    widgetTitle->setLayout(title_layout);

    QHBoxLayout *searchLayout = new QHBoxLayout();
    searchLayout->addStretch();
    searchLayout->addWidget(lineEdit_search);
    searchLayout->setContentsMargins(0, 10, 20, 0);
    searchLayout->setSpacing(10);

    QVBoxLayout *centerLayout = new QVBoxLayout();
    centerLayout->addLayout(searchLayout);
    centerLayout->addWidget(view_addMusic);
    centerLayout->setContentsMargins(20, 0, 20, 0);
    centerLayout->setSpacing(10);
    widgetCenter->setLayout(centerLayout);


    QVBoxLayout *music_layout = new QVBoxLayout();
    music_layout->addWidget(label_music);
    music_layout->addWidget(view_music);
    music_layout->setContentsMargins(20, 10, 20, 0);
    widgetBottom->setLayout(music_layout);

    QHBoxLayout *save_layout = new QHBoxLayout();
    save_layout->addStretch();
    save_layout->addWidget(pushButton_save);
    save_layout->addStretch();
    save_layout->setContentsMargins(0, 10, 0, 10);

    QVBoxLayout *vLayout = new QVBoxLayout();

    vLayout->addWidget(widgetTitle);
    vLayout->addWidget(widgetCenter);
    vLayout->addWidget(widgetBottom);
    vLayout->addLayout(save_layout);
    vLayout->setContentsMargins(0, 0, 0, 0);
    vLayout->setSpacing(0);

    this->setLayout(vLayout);
}

void SongsListAddModifyDialog::initWidgetValue()
{
    QFile qss(":/qss/title.qss");
    qss.open(QFile::ReadOnly);
    this->setStyleSheet(qss.readAll());
    qss.close();

    label_title->setText("添加歌星");
    label_music->setText("已选歌星");

    pushButton_save->setText("保存");
    lineEdit_search->setPlaceholderText("输入歌星/歌曲名字");

    widgetTitle->setFixedHeight(33);

    label_music->setFixedSize(60, 24);
    lineEdit_search->setFixedSize(260, 24);

    pushButton_close->setFixedSize(14, 14);
    pushButton_save->setFixedSize(60, 24);

    this->setObjectName("WidgetCenter");
    widgetTitle->setObjectName("TitleWidget");
    label_title->setObjectName("TitleLabel");

    label_music->setObjectName("Label");
    lineEdit_search->setObjectName("LineEdit");

    pushButton_save->setObjectName("Button");
    pushButton_search->setObjectName("SerachButton");
    pushButton_close->setObjectName("CloseButton");

    QRect rect = lineEdit_search->geometry();
    lineEdit_search->setTextMargins(0, 0, 20, 0);
    pushButton_search->setGeometry(rect.width()-25, 3, 20, 20);
    pushButton_search->setCursor(Qt::PointingHandCursor);

    view_addMusic->setWidgetBottomHidden();
    view_music->setWidgetBottomHidden();

    if(!rowList.isEmpty())
        rowList.clear();

    view_addMusic->setFmAddMusicDelegate("添加");
    view_music->setFmAddMusicDelegate("取消");
}

void SongsListAddModifyDialog::setTitle(const QString &str)
{
    label_title->setText(str);
}

void SongsListAddModifyDialog::initSql(MysqlQuery *sql, QSqlQuery &query)
{
    if(!rowList.isEmpty())
        rowList.clear();
    _sql = sql;
    _query = query;
}

void SongsListAddModifyDialog::initType(const QString &type, const int &widItem)
{
    _type = type;
    _widItem = widItem;
}

void SongsListAddModifyDialog::setReplaceRow(const bool &rep, const int &row)
{

}

void SongsListAddModifyDialog::setViewValue(const QString &type)
{
    _type = type;

    _query.clear();
    view_music->tableView->clear();
    if(!_sql->queryMediaList(type,  _query)) return;
    view_music->setTotal_Rows_Pages(_query.size());

    view_music->showUploadMediaListData(_query);
    view_music->getValue(rowList);
}

void SongsListAddModifyDialog::serachMusic()
{
    QString str = lineEdit_search->text();
    if(str.isEmpty())
        return;

    _querySearch.clear();
    if(_sql->querySongOrSingerSearch(str, _querySearch))
        view_addMusic->showUploadData(_querySearch, true);
}

void SongsListAddModifyDialog::addMusicDetail(const int &row)
{
    _querySearch.seek(row);
    QStringList tempValue;
    getMusicDetail(_querySearch, tempValue);

    rowList.append(tempValue);
    view_music->setModelValue(rowList);
}

void SongsListAddModifyDialog::save()
{
    if(!media.isEmpty())
        media.clear();

    for(int i=0; i<rowList.size(); i++){
        Media _media;
        QStringList list;
        list = rowList.at(i);
        _media.mid = list.at(0);
        _media.serial_id = list.at(1);
        _media.name = list.at(2);
        _media.singer = list.at(3);
        _media.language = list.at(4);
        _media.type = list.at(5);

        media.append(_media);
    }

    emit update_view(media);
    this->close();
}

void SongsListAddModifyDialog::play(const int &row, const int &)
{
    int size = rowList.size();
    if(row > size || row < 0)
        return;

    QStringList list = rowList.at(row);
    QString path = list.at(6);
    if(!path.isEmpty())
        view_addMusic->palyVideo(path);
}

void SongsListAddModifyDialog::playAddMusic(const int &row, const int &)
{
    _querySearch.seek(row);
    QString path = _querySearch.value("_path").toString();
    if(!path.isEmpty())
        view_addMusic->palyVideo(path);
}

void SongsListAddModifyDialog::deleteMusic(const int &row)
{    
    rowList.removeAt(row);
    view_music->setModelValue(rowList);
}

void SongsListAddModifyDialog::getMusicDetail(QSqlQuery &querySearch, QStringList &tempValue)
{
    tempValue << querySearch.value("_mid").toString()
              << querySearch.value("_serial_id").toString()
              << querySearch.value("_name").toString()
              << querySearch.value("_singer").toString()
              << querySearch.value("_language").toString()
              << querySearch.value("_type").toString()
              << querySearch.value("_path").toString();
}


