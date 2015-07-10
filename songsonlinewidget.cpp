#include "songsonlinewidget.h"
#include "songinfowidget.h"
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

SongsOnlineWidget::SongsOnlineWidget(QWidget *parent)
    : QWidget(parent)
{
    initWidget();
    readAndSetStyleSheet();
    initWidgetValue();   
    tableView_songsOnline->setMediaOnlineDelegate();

    connect(pushButton_preview, &QPushButton::clicked, this, &SongsOnlineWidget::preview);
    connect(pushButton_upload, &QPushButton::clicked, this, &SongsOnlineWidget::upload);
    connect(pushButton_save, &QPushButton::clicked, this, &SongsOnlineWidget::save);
}

SongsOnlineWidget::~SongsOnlineWidget()
{

}

void SongsOnlineWidget::readAndSetStyleSheet()
{
    QFile qss(":/qss/songonline.qss");
    qss.open(QFile::ReadOnly);
    this->setStyleSheet(qss.readAll());
    qss.close();

    this->setObjectName("Widget");
    widgetTitle->setObjectName("TopWidget");
    widgetCenter->setObjectName("CenterWidget");
    label_title->setObjectName("TitleLabel");
    label_select->setObjectName("SelectLabel");

    lineEdit_upload->setObjectName("LineEdit");

    pushButton_preview->setObjectName("Button");
    pushButton_upload->setObjectName("Button");
    pushButton_save->setObjectName("Button");
}

void SongsOnlineWidget::initWidget()
{
    widgetTitle = new QWidget(this);
    widgetCenter = new QWidget(this);

    widget_info = new SongInfoWidget(widgetCenter);
    label_title = new QLabel(widgetTitle);
    label_select = new QLabel(widgetCenter);

    lineEdit_upload = new QLineEdit(widgetTitle);
    pushButton_upload = new QPushButton(widgetTitle);
    pushButton_preview = new QPushButton(widgetTitle);
    pushButton_save = new QPushButton(widgetCenter);

    tableView_songsOnline = new PagingTableView(this);

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

    label_select->setFixedHeight(36);
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

    centerLayout->addWidget(label_select);    
    centerLayout->addLayout(infoSavelayout);
    centerLayout->setContentsMargins(20, 0, 0, 0);
    centerLayout->setSpacing(0);
    widgetCenter->setLayout(centerLayout);

    tableViewLayout = new QVBoxLayout();
    vLayout = new QVBoxLayout();
    tableViewLayout->addWidget(tableView_songsOnline);
    tableViewLayout->setContentsMargins(20, 15, 12, 3);

    vLayout->addWidget(widgetTitle);
    vLayout->addWidget(widgetCenter);
    vLayout->addLayout(tableViewLayout);
    vLayout->setContentsMargins(0, 0, 0, 0);
    vLayout->setSpacing(0);

    this->setLayout(vLayout);
}

void SongsOnlineWidget::initWidgetValue()
{
    label_title->setText("歌曲上线");
    label_select->setText("歌曲添加");
    lineEdit_upload->setPlaceholderText("表格内容必须与数据库字段一致");
    pushButton_preview->setText("浏览");
    pushButton_upload->setText("批量上传");
    pushButton_save->setText("保存上传");
}

void SongsOnlineWidget::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void SongsOnlineWidget::initComboboxValue(MysqlQuery *sql)
{
    _sql = sql;

    _sql->getMediaLanguage(language);
    _sql->getMediaType(type);
    _sql->getMediaEffect(effect);
    _sql->getMediaResolution(resolution);
    _sql->getMediaQuality(quality);
    _sql->getMediaSource(source);
    _sql->getMediaVersion(version);
    _sql->getMediaRthym(rthym);
    _sql->getMediaPitch(pitch);

    widget_info->set_comboBox_Language(language);
    widget_info->set_comboBox_type(type);
    widget_info->set_comboBox_effect(effect);
    widget_info->set_comboBox_resolution(resolution);
    widget_info->set_comboBox_quality(quality);
    widget_info->set_comboBox_source(source);
    widget_info->set_comboBox_version(version);
    widget_info->set_comboBox_rthym(rthym);
    widget_info->set_comboBox_pitch(pitch);
    widget_info->set_comboBox_Remain();
}

void SongsOnlineWidget::preview()
{
    QMessageBox::information(this, "提示", "浏览");
}

void SongsOnlineWidget::upload()
{
    QMessageBox::information(this, "提示", "上传");
}

void SongsOnlineWidget::save()
{
    Media media;
    widget_info->getMediaValue(media);

    QString title("保存提示");
    QString content("必填项未填写完整！");
    QMessageBox box(QMessageBox::Warning, title, content);
    box.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    box.setButtonText(QMessageBox::Ok, "确定");
    box.setButtonText(QMessageBox::Cancel, "取消");

    if(widget_info->isEmpty()){
        box.exec();
        return;
    }

    qint64 ser_id = _sql->isMediaSerialId(media.serial_id.toLongLong());
    if(ser_id > 0)
    {
        content = QString("serial_id : %1已经存在!\n 最大serial_id : %2").arg(media.serial_id).arg(ser_id);
        QMessageBox box(QMessageBox::Warning, title, content);
        box.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        box.setButtonText(QMessageBox::Ok, "确定");
        box.setButtonText(QMessageBox::Cancel, "取消");
        box.exec();
        return;
    }

    QFile file(media.path);
    if(file.exists())
        media.path = widget_info->uploadV(media.path);

    file.setFileName(media.lyric);
    if(file.exists())
            media.lyric = widget_info->uploadL(media.lyric);


    if(_sql->insertMedia(media))
        updateView(media);
}

void SongsOnlineWidget::updateView(const Media &media)
{
    QStringList list;
    list.append(media.mid);
    list.append(media.serial_id);
    list.append(media.name);
    list.append(media.singer);
    list.append(language.value(media.language.toInt()));
    list.append(type.value(media.type.toInt()));

    rowList.append(list);
    tableView_songsOnline->setModelValue(rowList);
}
