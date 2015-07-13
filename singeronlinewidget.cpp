#include "singeronlinewidget.h"
#include "singerinfowdiget.h"
#include "pagingtableview.h"
#include "mysqlquery.h"
#include <QFile>
#include <QLabel>
#include <QPainter>
#include <QLineEdit>
#include <QTableView>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QCoreApplication>
SingerOnlineWidget::SingerOnlineWidget(QWidget *parent)
    : QWidget(parent)
{
    initWidget();
    readAndSetStyleSheet();
    initWidgetValue();

    widget_info->isSingerOnline();
    tableView_singerOnline->setActorOnlineDelegate();
    connect(pushButton_upload, &QPushButton::clicked, this, &SingerOnlineWidget::upload);
    connect(pushButton_preview, &QPushButton::clicked, this, &SingerOnlineWidget::preview);
    connect(pushButton_save, &QPushButton::clicked, this, &SingerOnlineWidget::save);
}

SingerOnlineWidget::~SingerOnlineWidget()
{

}

void SingerOnlineWidget::readAndSetStyleSheet()
{
    QFile qss(":/qss/songonline.qss");
    qss.open(QFile::ReadOnly);
    this->setStyleSheet(qss.readAll());
    qss.close();

    this->setObjectName("Widget");
    widgetTitle->setObjectName("TopWidget");
    widgetCenter->setObjectName("CenterWidget");
    label_title->setObjectName("TitleLabel");
    label_addSinger->setObjectName("SelectLabel");

    lineEdit_upload->setObjectName("LineEdit");

    pushButton_preview->setObjectName("Button");
    pushButton_upload->setObjectName("Button");
    pushButton_save->setObjectName("Button");
}

void SingerOnlineWidget::initWidget()
{
    widgetTitle = new QWidget(this);
    widgetCenter = new QWidget(this);

    widget_info = new SingerInfoWdiget(widgetCenter);

    label_title = new QLabel(widgetTitle);
    label_addSinger = new QLabel(widgetCenter);

    lineEdit_upload = new QLineEdit(widgetTitle);
    pushButton_upload = new QPushButton(widgetTitle);
    pushButton_preview = new QPushButton(widgetTitle);
    pushButton_save = new QPushButton(widgetCenter);

    tableView_singerOnline = new PagingTableView(this);

    previewLayout = new QHBoxLayout();
    uploadLayout = new QHBoxLayout();
    titleLayout = new QHBoxLayout();

    lineEdit_upload->setFixedHeight(36);
    lineEdit_upload->setFixedWidth(260);
    pushButton_preview->setFixedHeight(36);
    pushButton_preview->setFixedWidth(60);
    pushButton_upload->setFixedHeight(36);
    pushButton_upload->setFixedWidth(90);
    pushButton_save->setFixedHeight(36);
    pushButton_save->setFixedWidth(90);

    label_addSinger->setFixedHeight(36);
    widgetTitle->setFixedHeight(60);

    previewLayout->addWidget(lineEdit_upload);
    previewLayout->addWidget(pushButton_preview);
    previewLayout->setContentsMargins(0, 0, 0, 0);
    previewLayout->setSpacing(10);

    uploadLayout->addLayout(previewLayout);
    uploadLayout->addWidget(pushButton_upload);
    uploadLayout->setContentsMargins(0, 0, 0, 0);
    uploadLayout->setSpacing(30);

    titleLayout->addWidget(label_title);
    titleLayout->addStretch();
    titleLayout->addLayout(uploadLayout);
    titleLayout->setContentsMargins(20, 0, 24, 0);
    titleLayout->setSpacing(0);
    widgetTitle->setLayout(titleLayout);

    saveLayout = new QHBoxLayout();
    infoSavelayout = new QVBoxLayout();
    centerLayout = new QVBoxLayout();

    saveLayout->addStretch();
    saveLayout->addWidget(pushButton_save);
    saveLayout->addStretch();
    saveLayout->setContentsMargins(0, 15, 0, 10);
    saveLayout->setSpacing(0);

    infoSavelayout->addWidget(widget_info);
    infoSavelayout->addLayout(saveLayout);
    infoSavelayout->setContentsMargins(26, 0, 0, 0);
    infoSavelayout->setSpacing(0);

    centerLayout->addWidget(label_addSinger);
    centerLayout->addLayout(infoSavelayout);
    centerLayout->setContentsMargins(20, 0, 0, 0);
    centerLayout->setSpacing(0);
    widgetCenter->setLayout(centerLayout);

    tableViewLayout = new QVBoxLayout();
    vLayout = new QVBoxLayout();
    tableViewLayout->addWidget(tableView_singerOnline);
    tableViewLayout->setContentsMargins(20, 15, 12, 3);

    vLayout->addWidget(widgetTitle);
    vLayout->addWidget(widgetCenter);
    vLayout->addLayout(tableViewLayout);
    vLayout->setContentsMargins(0, 0, 0, 0);
    vLayout->setSpacing(0);

    this->setLayout(vLayout);
}

void SingerOnlineWidget::initWidgetValue()
{
    label_title->setText("歌星上线");
    label_addSinger->setText("歌星添加");
    lineEdit_upload->setPlaceholderText("表格内容必须与数据库字段一致");
    pushButton_preview->setText("浏览");
    pushButton_upload->setText("批量上传");
    pushButton_save->setText("保存上传");
}

void SingerOnlineWidget::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void SingerOnlineWidget::initComboboxValue(MysqlQuery *sql)
{
    _sql = sql;

    _sql->getSex(sex);
    _sql->getNation(nation);

    widget_info->set_comboBox_sex(sex);
    widget_info->set_comboBox_nation(nation);
    widget_info->set_comboBox_Remain();
}

void SingerOnlineWidget::updateView(Actor actor)
{
    QString filePath;
    QString runPath = QCoreApplication::applicationDirPath();
    runPath.replace(runPath.size()-9, 9, "/Resources/image/" );
    filePath = runPath + actor.name;
    filePath += ".jpg";

    QFile file(filePath);
    if (!file.exists()){
        CurlUpload *curlDownlaod = new CurlUpload();
        curlDownlaod->downloadActorImage(actor.name, filePath);

        delete curlDownlaod;
    }

    QStringList list;
    list.append(actor.sid);
    list.append(actor.serial_id);
    if(!filePath.isEmpty())
        list.append(filePath);
    else
        list.append("");
    list.append(actor.name);
    list.append(sex.value(actor.sex.toInt()));
    list.append(nation.value(actor.nation.toInt()));

    rowList.append(list);
    tableView_singerOnline->setModelValue(rowList);
}

void SingerOnlineWidget::upload()
{
    QMessageBox::information(this, "提示", "批量上传");
}

void SingerOnlineWidget::preview()
{
    QMessageBox::information(this, "提示", "浏览");
}

void SingerOnlineWidget::save()
{

    if(widget_info->isEmpty()){
        QMessageBox box(QMessageBox::Warning, "保存提示", "必填项未填写完整！");
        box.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        box.setButtonText(QMessageBox::Ok, "确定");
        box.setButtonText(QMessageBox::Cancel, "取消");
        box.exec();
        return;
    }

    Actor actor;
    widget_info->getActorOnlineValue(actor);

    ///-1 没有重复
    qint64 ser_id = _sql->isActorSerialId(actor.serial_id.toLongLong());
    if(ser_id > 0)
    {
        QString content = QString("serial_id : %1已经存在!\n 最大serial_id : %2").arg(actor.serial_id).arg(ser_id);
        QMessageBox box(QMessageBox::Warning, "SERIAL_ID重复提示", content);
        box.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        box.setButtonText(QMessageBox::Ok, "确定");
        box.setButtonText(QMessageBox::Cancel, "取消");
        box.exec();
        return;
    }

    QString path = actor.image;
    if(path.isEmpty())
        return;
    QFile file(path);
    if(file.exists())
    {
        QString retStr = "";
        CurlUpload *curlUpload = new CurlUpload();
        retStr = curlUpload->uploadActorImage(path);
        widget_info->setImageOnlineRetPath(retStr);

        delete curlUpload;
    }

    if(_sql->insertActor(actor))
        updateView(actor);
}

