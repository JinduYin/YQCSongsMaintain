#include "fmwidget.h"
#include "fminfowidget.h"
#include "mysqlquery.h"
#include "tablemodel.h"
#include "pagingtableview.h"
#include "fmaddmodifydialog.h"
#include "enuminfo.h"
#include "curlupload.h"

#include <QMenu>
#include <QAction>
#include <QFile>
#include <QLabel>
#include <QPalette>
#include <QPainter>
#include <QLineEdit>
#include <QCheckBox>
#include <QComboBox>
#include <QSettings>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDebug>
#include <QCoreApplication>
//#include <QNetworkReply>
//#include <QNetworkAccessManager>

#include <QMessageBox>
#define DEFAULT_FMNUM 2

FMWidget::FMWidget(QWidget *parent)
    : QWidget(parent)
{
    initWidget();
    readAndSetStyleSheet();
    initWidgetValue();
    setWidgetSize();
    initMenuAction();

    limitArgu.curMaxVal = -1;
    limitArgu.curMinVal = -1;
    limitArgu.currentpage = 0;
    limitArgu.limitOffset = -1;
    limitArgu.limitStartVal = -1;
    limitArgu.rowNum = -1;
    limitArgu.totalPage = -1;
    limitArgu.totalRow = -1;
    limitArgu.tagPage = -1;

    index = 0;


    connect(pushButton_upPage, &QPushButton::clicked, this, &FMWidget::up_page);
    connect(pushButton_nextPage, &QPushButton::clicked, this, &FMWidget::next_page);
    connect(pushButton_firstPage, &QPushButton::clicked, this, &FMWidget::first_page);
    connect(pushButton_lastpage, &QPushButton::clicked, this, &FMWidget::last_page);
    connect(pushButton_jumpPage, &QPushButton::clicked, this, &FMWidget::jump_page);

    connect(lineEdit_jump, &QLineEdit::editingFinished, this, &FMWidget::jumpEditFinish);
    connect(pushButton_jumpPage, &QPushButton::clicked, this, &FMWidget::jumpEditFinish);    
}

FMWidget::~FMWidget()
{

}

void FMWidget::readAndSetStyleSheet()
{
    QFile qss(":/qss/songquery.qss");
    qss.open(QFile::ReadOnly);
    this->setStyleSheet(qss.readAll());
    qss.close();

    this->setObjectName("Widget");
    widgetTitle->setObjectName("TopWidget");
    widgetCenter->setObjectName("CenterWidget");
    label_title->setObjectName("TitleLabel");
    pushButton_upload->setObjectName("Button");
    pushButton_newFM->setObjectName("Button");
    lineEdit_upload->setObjectName("LineEdit");

    label_center->setObjectName("CenterLabel");


    label_totalNum->setObjectName("Label");
    label_showPage->setObjectName("Label");
    lineEdit_jump->setObjectName("LineEdit");
    pushButton_upPage->setObjectName("Button");
    pushButton_nextPage->setObjectName("Button");
    pushButton_firstPage->setObjectName("Button");
    pushButton_lastpage->setObjectName("Button");
    pushButton_jumpPage->setObjectName("Button");

    QString strStyle("border: 1px solid rgb(170, 170, 170);border-radius:5px;");
    QString pushButtonStyle("border: 0px;");
    label_showPage->setAlignment(Qt::AlignCenter);
    lineEdit_jump->setAlignment(Qt::AlignCenter);
    label_showPage->setStyleSheet(strStyle);
    lineEdit_jump->setStyleSheet(strStyle);

    pushButton_upPage->setStyleSheet(pushButtonStyle);
    pushButton_nextPage->setStyleSheet(pushButtonStyle);
    pushButton_firstPage->setStyleSheet(pushButtonStyle);
    pushButton_lastpage->setStyleSheet(pushButtonStyle);
    pushButton_jumpPage->setStyleSheet(pushButtonStyle);
}

void FMWidget::initMenuAction()
{
    fm01->setContextMenuPolicy(Qt::CustomContextMenu);
    fm02->setContextMenuPolicy(Qt::CustomContextMenu);

    fmMenu01 = new QMenu(fm01);
    fmMenu02 = new QMenu(fm02);
    fmMoveUp = new QAction("上移", this);
    fmMoveDown = new QAction("下移", this);

    connect(fmMoveUp, &QAction::triggered, this, &FMWidget::fmMoveUpList);
    connect(fmMoveDown, &QAction::triggered, this, &FMWidget::fmMoveDownList);

    connect(fm01, &FmInfoWidget::customContextMenuRequested, this, &FMWidget::on_fm01_customContextMenuRequested);
    connect(fm02, &FmInfoWidget::customContextMenuRequested, this, &FMWidget::on_fm02_customContextMenuRequested);

    connect(pushButton_newFM, &QPushButton::clicked, this, &FMWidget::newFmList);
    connect(fm01, &FmInfoWidget::modifyFm, this, &FMWidget::modifyFmList);
    connect(fm01, &FmInfoWidget::deleteFm, this, &FMWidget::deleteFmList);
    connect(fm02, &FmInfoWidget::modifyFm, this, &FMWidget::modifyFmList);
    connect(fm02, &FmInfoWidget::deleteFm, this, &FMWidget::deleteFmList);    
}

void FMWidget::initWidget()
{    
    widgetTitle = new QWidget(this);
    widgetCenter = new QWidget(this);
    widgetBottom = new QWidget(this);

    label_title = new QLabel(widgetTitle);
    label_center = new QLabel(widgetCenter);

    lineEdit_upload = new QLineEdit(widgetTitle);
    pushButton_upload = new QPushButton(widgetTitle);
    pushButton_newFM = new QPushButton(widgetTitle);

    fm01 = new FmInfoWidget(widgetCenter);
    fm02 = new FmInfoWidget(widgetCenter);

    upload_layout = new QHBoxLayout();
    newFM_layout = new QHBoxLayout();
    title_layout = new QHBoxLayout();

    upload_layout->addWidget(lineEdit_upload);
    upload_layout->addWidget(pushButton_upload);
    upload_layout->setContentsMargins(0, 0, 0, 0);
    upload_layout->setSpacing(10);

    newFM_layout->addLayout(upload_layout);
    newFM_layout->addWidget(pushButton_newFM);
    newFM_layout->setContentsMargins(0, 0, 0, 0);
    newFM_layout->setSpacing(30);

    title_layout->addWidget(label_title);
    title_layout->addStretch();
    title_layout->addLayout(newFM_layout);
    title_layout->setContentsMargins(20, 0, 20, 0);
    title_layout->setSpacing(0);

    widgetTitle->setLayout(title_layout);

    fmTop_layout = new QVBoxLayout();
    fm_layout = new QVBoxLayout();
    fmTop_layout->addWidget(fm01, 0, Qt::AlignTop);
    fmTop_layout->addWidget(label_center, 0, Qt::AlignTop);
    fmTop_layout->setContentsMargins(0, 0, 0, 0);
    fmTop_layout->setSpacing(8);

    fm_layout->addLayout(fmTop_layout);
    fm_layout->addWidget(fm02, 0, Qt::AlignTop);
    fm_layout->addStretch();
    fm_layout->setContentsMargins(0, 0, 0, 8);
    fm_layout->setSpacing(0);

    widgetCenter->setLayout(fm_layout);

    vLayout = new QVBoxLayout();
    vLayout->addWidget(widgetTitle);
    vLayout->addWidget(widgetCenter);
    vLayout->addWidget(widgetBottom);
    vLayout->setContentsMargins(0, 0, 0, 0);
    vLayout->setSpacing(0);

    this->setLayout(vLayout);


    label_totalNum = new QLabel(widgetBottom);
    label_showPage = new QLabel(widgetBottom);

    lineEdit_jump = new QLineEdit(widgetBottom);

    pushButton_upPage = new QPushButton(widgetBottom);
    pushButton_nextPage = new QPushButton(widgetBottom);
    pushButton_firstPage = new QPushButton(widgetBottom);
    pushButton_lastpage = new QPushButton(widgetBottom);
    pushButton_jumpPage = new QPushButton(widgetBottom);

    QHBoxLayout *showPage_layout = new QHBoxLayout();
    showPage_layout->addWidget(label_totalNum);
    showPage_layout->addStretch();
    showPage_layout->setContentsMargins(5, 0, 0, 0);
    showPage_layout->setSpacing(8);

    QHBoxLayout *chanagePage_layout = new QHBoxLayout();
    chanagePage_layout->addStretch();
    chanagePage_layout->addWidget(pushButton_firstPage);
    chanagePage_layout->addWidget(pushButton_upPage);
    chanagePage_layout->addWidget(label_showPage);
    chanagePage_layout->addWidget(pushButton_nextPage);
    chanagePage_layout->addWidget(pushButton_lastpage);
    chanagePage_layout->setContentsMargins(0, 0, 0, 0);
    chanagePage_layout->setSpacing(8);

    QHBoxLayout *jumpPage = new QHBoxLayout();
    jumpPage->addWidget(lineEdit_jump);
    jumpPage->addWidget(pushButton_jumpPage);
    jumpPage->setContentsMargins(0, 0, 0, 0);
    jumpPage->setSpacing(8);

    QHBoxLayout *chanage_jump_layout = new QHBoxLayout();
    chanage_jump_layout->addLayout(chanagePage_layout);
    chanage_jump_layout->addLayout(jumpPage);
    chanage_jump_layout->setContentsMargins(0, 0, 0, 0);
    chanage_jump_layout->setSpacing(20);

    QHBoxLayout *bottom_Layout = new QHBoxLayout();
    bottom_Layout->addLayout(showPage_layout);
    bottom_Layout->addStretch();
    bottom_Layout->addLayout(chanage_jump_layout);
    bottom_Layout->setContentsMargins(0, 0, 0, 0);
    bottom_Layout->setSpacing(0);

    widgetBottom->setLayout(bottom_Layout);
}

void FMWidget::initWidgetValue()
{
    label_title->setText("FM歌单管理");
    pushButton_newFM->setText("新建歌单");
    pushButton_upload->setText("上传表格");
    lineEdit_upload->setPlaceholderText("表格内容必须与数据库字段一致");


    pushButton_upPage->setText("上一页");
    pushButton_nextPage->setText("下一页");
    pushButton_firstPage->setText("首页");
    pushButton_lastpage->setText("末页");
    pushButton_jumpPage->setText("跳转");
    label_showPage->setText(" / ");
}

void FMWidget::setWidgetSize()
{
    widgetTitle->setFixedHeight(60);
    widgetBottom->setFixedHeight(48);
    lineEdit_upload->setFixedWidth(260);
    lineEdit_upload->setFixedHeight(36);

    pushButton_upload->setFixedHeight(36);
    pushButton_upload->setFixedWidth(90);
    pushButton_newFM->setFixedHeight(36);
    pushButton_newFM->setFixedWidth(90);

    label_center->setFixedHeight(28);


    pushButton_upPage->setFixedHeight(30);
    pushButton_nextPage->setFixedHeight(30);
    pushButton_firstPage->setFixedHeight(30);
    pushButton_lastpage->setFixedHeight(30);
    pushButton_jumpPage->setFixedHeight(30);
    pushButton_upPage->setFixedWidth(60);
    pushButton_nextPage->setFixedWidth(60);
    pushButton_firstPage->setFixedWidth(50);
    pushButton_lastpage->setFixedWidth(50);
    pushButton_jumpPage->setFixedWidth(50);

    label_showPage->setFixedHeight(30);
    label_showPage->setFixedWidth(60);

    lineEdit_jump->setFixedHeight(30);
    lineEdit_jump->setFixedWidth(50);
}

void FMWidget::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void FMWidget::initSql(MysqlQuery *sql)
{
    _sql = sql;
}

void FMWidget::setFmValue()
{
    if(!_sql->queryFMSongList(query)) return;

    label_totalNum->setText(QString("总%1个歌单").arg(query.size()));
    limitArgu.totalRow = query.size();
    limitArgu.totalPage = (query.size()/2) +  (query.size()%2?1:0);
    limitArgu.rowNum = 2;

    show_FM();
}

void FMWidget::show_FM()
{
    label_showPage->setText(QString("%1/%2").arg(limitArgu.currentpage+1).arg(limitArgu.totalPage));

    query.seek(2*limitArgu.currentpage);
    query.previous();

    if(query.next()){
        fm01->setFmName(query.value("_title").toString());
        setFmImage(query.value("_title").toString(), 1);
        if(_sql->queryFMSongListDetail(query.value("_lid").toLongLong(), queryList)){
            fm01->setTotalRows(queryList.size());
            fm01->setTotal(queryList.size());
        }
        fm01->setTableValue(queryList);
    }

    if(query.next()){
        fm02->setFmName(query.value("_title").toString());
        setFmImage(query.value("_title").toString(), 2);
        if(_sql->queryFMSongListDetail(query.value("_lid").toLongLong(), queryList)){
            fm02->setTotalRows(queryList.size());
            fm02->setTotal(queryList.size());
        }
        fm02->setTableValue(queryList);
        fm02->setHidden(false);
    }else{
       fm02->setHidden(true);
    }
}

void FMWidget::up_page()
{
    if (limitArgu.currentpage <= 0)
        return;

    limitArgu.currentpage--;
    limitArgu.tagPage = paging_upPage;
    show_FM();
}

void FMWidget::next_page()
{
    if (limitArgu.currentpage >= limitArgu.totalPage - 1)
        return;

    limitArgu.currentpage++;
    limitArgu.tagPage = paging_nextPage;
    show_FM();
}

void FMWidget::first_page()
{
    limitArgu.currentpage = 0;
    show_FM();
}

void FMWidget::last_page()
{
    limitArgu.currentpage = limitArgu.totalPage - 1;
    show_FM();
}

void FMWidget::jump_page(const int page)
{
    limitArgu.currentpage = page;
    show_FM();
}


void FMWidget::jumpEditFinish()
{
    if(lineEdit_jump->text().toInt() < 1
        || lineEdit_jump->text().toInt() > limitArgu.totalPage)
        return;
    jump_page(lineEdit_jump->text().toInt() -1);
}

void FMWidget::on_fm01_customContextMenuRequested(const QPoint &pos)
{

    fmMenu01->clear();
    QRect rect = fm01->getRightButtonGeometry();
    if(pos.x() > rect.x()
        && pos.x() < rect.width()
        && pos.y() > rect.y()
        && pos.y() < rect.height()){

        if(limitArgu.currentpage != 0)
            fmMenu01->addAction(fmMoveUp);

        if(!fm02->isHidden())
            fmMenu01->addAction(fmMoveDown);
        fmMenu01->exec(QCursor::pos());
    }
}

void FMWidget::on_fm02_customContextMenuRequested(const QPoint &pos)
{

    fmMenu02->clear();
    QRect rect = fm01->getRightButtonGeometry();
    if(pos.x() > rect.x()
        && pos.x() < rect.width()
        && pos.y() > rect.y()
        && pos.y() < rect.height()){

        fmMenu02->addAction(fmMoveUp);
        if(limitArgu.currentpage != limitArgu.totalPage - 1)
            fmMenu02->addAction(fmMoveDown);
        fmMenu02->exec(QCursor::pos());
    }
}

void FMWidget::fmMoveUpList()
{
    int index = getOffset();

    SongList value, valuePre;
    query.seek(index);
    getFmvalue(query, value);

    if(!query.previous())
        return;
    getFmvalue(query, valuePre);


    qint64 maxLid = -1;
    _sql->getFmMaxLid(maxLid);
    if(maxLid == -1) return;
    if(!_sql->updateMoveFmLid(valuePre.lid.toLongLong(), value.lid.toLongLong(), maxLid)) return;

    QString lid = value.lid;
    QString serial_id = value.serial_id;
    value.lid = valuePre.lid;
    value.serial_id = valuePre.serial_id;
    valuePre.lid = lid;
    valuePre.serial_id = serial_id;
    if(_sql->updateFmLid(value, valuePre)){
       if(_sql->updateFmLid(valuePre, value));
       else
           _sql->updateFmLid(value, value);
    }

    setFmValue();
}

void FMWidget::fmMoveDownList()
{
    int index = getOffset();

    SongList value, valueNext;
    query.seek(index);
    getFmvalue(query, value);

    if(!query.next())
        return;
    getFmvalue(query, valueNext);

    qint64 maxLid = -1;
    _sql->getFmMaxLid(maxLid);
    if(maxLid == -1) return;
    if(!_sql->updateMoveFmLid(value.lid.toLongLong(), valueNext.lid.toLongLong(), maxLid)) return;


    QString lid = value.lid;
    QString serial_id = value.serial_id;
    value.lid = valueNext.lid;
    value.serial_id = valueNext.serial_id;
    valueNext.lid = lid;
    valueNext.serial_id = serial_id;

    if(_sql->updateFmLid(valueNext, value)){
        if(_sql->updateFmLid(value, valueNext));
        else
            _sql->updateFmLid(valueNext, value);
    }

    setFmValue();
}

int FMWidget::getOffset()
{
    int index = 0;
    QPoint point = QCursor::pos();
    QRect rect = label_center->geometry();
    if(point.y() < rect.y())
        index = limitArgu.currentpage * DEFAULT_FMNUM + 0;
    else
        index = limitArgu.currentpage * DEFAULT_FMNUM + 1;

    if(fm02->isHidden()){
        index--;
    }

    return index;
}

void FMWidget::getFmvalue(const QSqlQuery &query, SongList &value)
{
    value.lid = query.value("_lid").toString();
    value.serial_id = query.value("_serial_id").toString();
    value.title = query.value("_title").toString();
    value.image = query.value("_image").toString();
    value.type = query.value("_type").toString();
    value.count = query.value("_count").toString();
    value.special = query.value("_special").toString();
}

void FMWidget::setFmImage(const QString &title, const int &_index)
{
//    QSettings *readConfig = new QSettings("SongsMaintain.conf", QSettings::IniFormat);
//    readConfig->setIniCodec("UTF-8");

//    QString hostName = readConfig->value("/SERVER/hostname", "http://192.168.1.243").toString();
//    hostName.append("/fm/");
//    hostName.append(title);
//    hostName.append(".jpg");

//    index = _index;
//    QNetworkAccessManager  *manager = new QNetworkAccessManager(this);
//    connect(manager, SIGNAL(finished(QNetworkReply*)),
//                    this, SLOT(replyFinished(QNetworkReply*)));
//    manager->get(QNetworkRequest(QUrl(hostName.toLocal8Bit())));

    QString filePath;
    QString runPath = QCoreApplication::applicationDirPath();
    runPath.replace(runPath.size()-9, 9, "/Resources/image/" );
    filePath = runPath + title;
    filePath += ".jpg";

    QFile file(filePath);
    if (!file.exists()){
        CurlUpload *curlDownlaod = new CurlUpload();
        curlDownlaod->download_fmImage(title, filePath);
        delete curlDownlaod;
    }

    if(_index == 1)
        fm01->setImage(filePath);
    else if(_index == 2)
        fm02->setImage(filePath);
}

//void FMWidget::replyFinished(QNetworkReply *reply)
//{
//    QPixmap pixmap;
//    if(reply->error() == QNetworkReply::NoError)
//    {
//        pixmap.loadFromData(reply->readAll());
//        if(index == 1)
//            fm01->setImage(pixmap);
//        else if(index == 2)
//            fm02->setImage(pixmap);
//    }

//    index = -1;
//}


void FMWidget::newFmList()
{
    FmAddModifyDialog *newFm = new FmAddModifyDialog();
    connect(newFm, SIGNAL(update_view()), this, SLOT(setFmValue()));
    newFm->setTitle("新建歌单");
    newFm->initSql(_sql, query);
    newFm->setFmState(fm_new);
    newFm->setType_delegate(widItem_FM);
    newFm->setSavePushbuttonHidden(false);
    newFm->exec();
}

void FMWidget::modifyFmList()
{
    FmAddModifyDialog *modFm = new FmAddModifyDialog();
    connect(modFm, SIGNAL(update_view()), this, SLOT(setFmValue()));
    modFm->setTitle("添加歌曲");
    int index = getOffset();
    query.seek(index);
    modFm->initSql(_sql, query);
    modFm->setFmState(fm_modify);
    modFm->setFmViewValue();
    modFm->setType_delegate(widItem_FM);
    modFm->setSavePushbuttonHidden(true);
    modFm->exec();
}

void FMWidget::deleteFmList()
{
    int index = getOffset();

    query.seek(index);
    qint64 lid = query.value("_lid").toLongLong();
    QString title = query.value("_title").toString();
    qint64 serial_id = query.value("_serial_id").toLongLong();

    if(!_sql->deleteFmSonglist(lid, title, serial_id))
        QMessageBox::information(this, "删除错误提示", QString("FM歌单:%1删除失败").arg(query.value("_title").toString()));


    if(fm02->isHidden() && limitArgu.currentpage > 0)
        limitArgu.currentpage--;

    setFmValue();
}
