#include "blackwidget.h"
#include "pagingtableview.h"
#include "tablemodel.h"
#include "mysqlquery.h"
#include "yqcdelegate.h"
#include "dropshadowwidget.h"
#include <QLabel>
#include <QList>
#include <QFile>
#include <QPainter>
#include <QCheckBox>
#include <QPushButton>
#include <QTableView>
#include <QDesktopWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDebug>
#define DEFAULT_ROWCOUNT 20  //每页默认行数

BlackWidget::BlackWidget(QWidget *parent, int itemIndex)
    : QWidget(parent),
    _itemIndex(itemIndex)
{
    initWidget();
    readAndSetStyleSheet();

    setWidgetValue(_itemIndex);
}

BlackWidget::~BlackWidget()
{
    if(curlDownlaod){
        delete curlDownlaod;
        curlDownlaod = NULL;
    }
}

void BlackWidget::readAndSetStyleSheet()
{
    QFile qss(":/qss/songquery.qss");
    qss.open(QFile::ReadOnly);
    this->setStyleSheet(qss.readAll());
    qss.close();

    this->setObjectName("Widget");
    widgetTitle->setObjectName("TopWidget");
    label_title->setObjectName("TitleLabel");
    pushButton_cancel->setObjectName("Button");
    pushButton_checkBox->setObjectName("CheckBoxButton");
}

void BlackWidget::initWidget()
{
    curlDownlaod = new CurlUpload();
    runPath = QCoreApplication::applicationDirPath();
    runPath.replace(runPath.size()-9, 9, "/Resources/image/" );

    widgetTitle = new QWidget(this);
    label_title = new QLabel(widgetTitle);
    pushButton_cancel = new QPushButton(widgetTitle);
    tableView = new PagingTableView(this);    
    pushButton_checkBox = new QPushButton(tableView);
    pushButton_checkBox->setCheckable(true);

    connect(tableView, &PagingTableView::updateView, this, &BlackWidget::show_black);
    connect(pushButton_checkBox, &QPushButton::clicked, tableView, &PagingTableView::checkBoxIsAll);
    connect(pushButton_cancel, &QPushButton::clicked, this, &BlackWidget::cancelBlackMush);
    connect(tableView, &PagingTableView::currentRow, this, &BlackWidget::cancelBlack);

    QHeaderView *headerView = tableView->tableView->horizontalHeader();
    QRect rect = headerView->geometry();
    QRect checkBoxRect = QRect(rect.x()+12, rect.y()+12, 16, 16);
    pushButton_checkBox->setGeometry(checkBoxRect);

    widgetTitle->setFixedHeight(60);
    pushButton_cancel->setFixedWidth(90);
    pushButton_cancel->setFixedHeight(36);
    pushButton_cancel->setText("批量取消");
    widgetTitle->setStyleSheet("border-bottom: 1px solid rgb(201, 201, 201);");

    title_layout = new QHBoxLayout();
    title_layout->addWidget(label_title);
    title_layout->addStretch();
    title_layout->addWidget(pushButton_cancel);
    title_layout->setContentsMargins(20, 0, 24, 0);
    title_layout->setSpacing(0);

    widgetTitle->setLayout(title_layout);

    tableView_layout = new QVBoxLayout();
    vLayout = new QVBoxLayout();

    tableView_layout->addWidget(tableView);
    tableView_layout->setContentsMargins(12, 0, 12, 0);
    tableView_layout->setSpacing(0);

    vLayout->addWidget(widgetTitle);
    vLayout->addLayout(tableView_layout);
    vLayout->setContentsMargins(0, 0, 0, 0);
    vLayout->setSpacing(0);

    this->setLayout(vLayout);
}

void BlackWidget::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void BlackWidget::setWidgetValue(int  itemIndex)
{
    if (itemIndex == stacked_mediablack)
        label_title->setText("歌曲黑名单");
    else if (itemIndex == stacked_actorblack)
        label_title->setText("歌星黑名单");
}

void BlackWidget::initSqlQuery(MysqlQuery *sql)
{
    _sql = sql;
}

void BlackWidget::initBlack_Media()
{
    tableView->setShowCheckBox();
    tableView->initMediaDelegate();
}

void BlackWidget::initBlack_Actor()
{
    tableView->setShowCheckBox();
    tableView->initActorDelegate();
}

void BlackWidget::initBlack_Total()
{
    qint64 total=0;
    if(_itemIndex == stacked_mediablack){
        if(!_sql->queryCountBlack_M(total)) return;
    }
    if(_itemIndex == stacked_actorblack){
        if(!_sql->queryCountBlack_A(total)) return;
    }

    tableView->setTotal_Rows_Pages(total);
}

void BlackWidget::show_black()
{    
    if (_itemIndex != stacked_mediablack && _itemIndex != stacked_actorblack)
        return;

    initBlack_Total();
    query.clear();
    tableView->tableView->clear();    

    if(_itemIndex == stacked_mediablack){
        if(_sql->queryMediaBlack(tableView->limitArgu, query))
            tableView->showUploadData(query, true);

    }else if(_itemIndex == stacked_actorblack){
        if(_sql->queryActorBlack(tableView->limitArgu, query))
           tableView->showUploadData(query, false);
    }else
        return;
}


void BlackWidget::addBlackRightMenu()
{

}

void BlackWidget::cancelBlack(const int &row)
{
    query.seek(row);
    qint64 _id = -1;
    QVector<qint64> _mids;
    if(_itemIndex == stacked_mediablack){
        _id = query.value("_mid").toLongLong();
        if(!_sql->updateMediaBlack(_id, 0)) return;
    }
    if(_itemIndex == stacked_actorblack){
        _id = query.value("_sid").toLongLong();
        _sql->getMidsOfSid(_id, _mids);
        if (_sql->updateMediaBlackMush(_mids, 0))
            _sql->updateActorBlack(_id, 0);
    }    
    show_black();
}

void BlackWidget::cancelBlackMush()
{
    QVector<int> rows;
    tableView->m_checkBoxDelegate->getIconStatus(rows);

    QVector<qint64> _ids;
    QVector<qint64> _mids;
    if(_itemIndex == stacked_mediablack){
        for(int i=0; i<rows.count(); i++){
            query.seek(rows.at(i));
            _ids.append(query.value("_mid").toLongLong());
        }

        if(!_ids.isEmpty())
            _sql->updateMediaBlackMush(_ids, 0);
    }

    if(_itemIndex == stacked_actorblack){
        for(int i=0; i<rows.count(); i++){
            query.seek(rows.at(i));
            _ids.append(query.value("_sid").toLongLong());
        }

        for(int i=0; i<_ids.size(); i++){
            _mids.clear();
            _sql->getMidsOfSid(_ids.at(i), _mids);
            if (_sql->updateMediaBlackMush(_mids, 0))
                _sql->updateActorBlack(_ids.at(i), 0);
        }
    }

    show_black();      
}

void BlackWidget::setBlackColumnWidth_Media(TableView *widget)
{
    int width = widget->width();
    int total = 8;
    widget->setColumnWidth(0, (width/total));
    widget->setColumnWidth(1, (width/total));
    widget->setColumnWidth(2, (width/total));
    widget->setColumnWidth(3, (width/total));
    widget->setColumnWidth(4, (width/total));
    widget->setColumnWidth(5, (width/total));
    widget->setColumnWidth(6, (width/total));
    widget->setColumnWidth(7, (width/total));
}

void BlackWidget::setBlackColumnWidth_Actor(QTableView *widget)
{
    int width = widget->width();
    int total = 16;
    widget->setColumnWidth(actBlack_check, (width/total)*1);
    widget->setColumnWidth(actBlack_image, (width/total)*3);
    widget->setColumnWidth(actBlack_name, (width/total)*3);
    widget->setColumnWidth(actBlack_sex, (width/total)*3);
    widget->setColumnWidth(actBlack_nation, (width/total)*3);
    widget->setColumnWidth(actBlack_edit, (width/total)*3);
}

//void BlackWidget::setMediaValue(const QSqlQuery &query, QStringList &rowValue, int index)
//{
//    rowValue.clear();
//    rowValue.append(QString::number(index));
//    rowValue.append(query.value("_name").toString());
//    rowValue.append(query.value("_singer").toString());
//    rowValue.append(query.value("_language").toString());
//    rowValue.append(query.value("_type").toString());
//    QString track = QString("原%1 伴%2")
//                    .arg(query.value("_original_track").toString())
//                    .arg(query.value("_sound_track").toString());
//    rowValue.append(track);
//}

//void BlackWidget::setActorValue(const QSqlQuery &query, const QString &runPath, int index, QStringList &rowValue)
//{
//    rowValue.clear();
//    rowValue.append(QString::number(index));

//    QString filePath;
//    filePath = runPath + query.value("_name").toString();
//    filePath += ".jpg";
//    QFile file(filePath);
//    if (!file.exists()){
//        curlDownlaod->downloadActorImage(query.value("_name").toString(), filePath);
//    }

//    rowValue.append(filePath);
//    rowValue.append(query.value("_name").toString());
//    rowValue.append(query.value("_sex").toString());
//    rowValue.append(query.value("_nation").toString());
//}

