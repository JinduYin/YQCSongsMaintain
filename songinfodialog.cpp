#include "songinfodialog.h"
#include "typeindexvalue.h"
#include "mysqlquery.h"
#include <QFile>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QDateTime>
#include <QStyleOption>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
SongInfoDialog::SongInfoDialog(QWidget *parent)
    :DropShadowWidget(parent),
      mid(-1),
      _sql(NULL)
{
    setFixedHeight(694);
    setFixedWidth(1110);

    _sql = NULL;
    mid = -1;

    initWidget();
    initWidgetValue();


}

SongInfoDialog::~SongInfoDialog()
{

}

void SongInfoDialog::initWidget()
{
    label = new QLabel(this);
    widgetTitle = new QWidget(this);
    widgetCenter = new QWidget(this);
    widgetUpdate = new QWidget(this);
    widgetSave = new QWidget(this);
    label_title = new QLabel(widgetTitle);
    pushButton_close = new QPushButton(widgetTitle);

    info = new SongInfoWidget(widgetCenter);
    label_videoPreview = new QLabel(widgetCenter);
    pushButton_videoPreview = new QPushButton(widgetCenter);

    pushButton_Yes = new QPushButton(widgetUpdate);
    pushButton_update = new QPushButton(widgetUpdate);
    pushButton_save = new QPushButton(widgetSave);

    connect(pushButton_close, &QPushButton::clicked, this, &SongInfoDialog::close);
    connect(pushButton_Yes, &QPushButton::clicked, this, &SongInfoDialog::close);
    connect(pushButton_update, &QPushButton::clicked, this, &SongInfoDialog::updateMediaValue);
    connect(pushButton_save, &QPushButton::clicked, this, &SongInfoDialog::save);

    label_prompt = new QLabel(widgetSave);
    label_prompt_tooptip = new QLabel(widgetSave);

    hLayout = new QHBoxLayout();
    hLayout->addWidget(label_title);
    hLayout->addStretch();
    hLayout->addWidget(pushButton_close);
    hLayout->setContentsMargins(20, 0, 20, 0);
    hLayout->setSpacing(0);
    widgetTitle->setLayout(hLayout);

    previewLayout = new QHBoxLayout();
    previewLayout->addWidget(label_videoPreview);
    previewLayout->addWidget(pushButton_videoPreview);
    previewLayout->addStretch();
    previewLayout->setContentsMargins(28, 10, 0, 0);
    previewLayout->setSpacing(10);

    updateLayout = new QHBoxLayout();
    updateLayout->addStretch();
    updateLayout->addWidget(pushButton_Yes);
    updateLayout->addWidget(pushButton_update);
    updateLayout->addStretch();
    updateLayout->setContentsMargins(0, 0, 0, 0);
    updateLayout->setSpacing(20);
    widgetUpdate->setLayout(updateLayout);

    promptLayout = new QHBoxLayout();
    saveLayout = new QHBoxLayout();
    promptLayout->addStretch();
    promptLayout->addWidget(label_prompt_tooptip);
    promptLayout->addWidget(label_prompt);
    promptLayout->setContentsMargins(0, 0, 10, 10);
    promptLayout->setSpacing(0);
    widgetSave->setLayout(promptLayout);


    infoLayout = new QVBoxLayout();
    infoLayout->addWidget(label);
    infoLayout->addWidget(info);
    infoLayout->setContentsMargins(20, 0, 20, 0);
    infoLayout->setSpacing(0);

    wbLayout = new QVBoxLayout();
    vLayout = new QVBoxLayout();

    wbLayout->addLayout(infoLayout);
    wbLayout->addLayout(previewLayout);
    wbLayout->addStretch();
    wbLayout->addWidget(widgetUpdate);
    wbLayout->addWidget(widgetSave);
    wbLayout->setContentsMargins(0, 0, 0, 10);
    wbLayout->setSpacing(0);
    widgetCenter->setLayout(wbLayout);

    vLayout->addWidget(widgetTitle);
    vLayout->addWidget(widgetCenter);
    vLayout->setContentsMargins(0, 0, 0, 0);
    vLayout->setSpacing(0);


    this->setLayout(vLayout);   
}

void SongInfoDialog::initWidgetValue()
{
    QFile qss(":/qss/title.qss");
    qss.open(QFile::ReadOnly);
    this->setStyleSheet(qss.readAll());
    qss.close();

    pushButton_save->setGeometry(this->width()/2 - 45, widgetSave->rect().y(), 90, 36);
    label->setFixedHeight(20);
    label->setObjectName("Label");
    label_prompt->setFixedHeight(36);
    label_videoPreview->setFixedWidth(80);
    pushButton_save->setFixedWidth(90);
    pushButton_save->setFixedHeight(36);
    pushButton_Yes->setFixedHeight(36);
    pushButton_Yes->setFixedWidth(90);
    pushButton_update->setFixedHeight(36);
    pushButton_update->setFixedWidth(90);
    pushButton_videoPreview->setFixedHeight(36);
    pushButton_videoPreview->setFixedWidth(90);
    pushButton_close->setFixedHeight(14);
    pushButton_close->setFixedWidth(14);
    widgetTitle->setFixedHeight(38);
    widgetTitle->setObjectName("TitleWidget");
    widgetCenter->setObjectName("WidgetCenter");
    widgetUpdate->setObjectName("WidgetCenter");
    widgetSave->setObjectName("WidgetCenter");
    pushButton_close->setObjectName("CloseButton");
    pushButton_Yes->setObjectName("Button");
    pushButton_update->setObjectName("Button");
    pushButton_save->setObjectName("Button");
    pushButton_videoPreview->setObjectName("Button");
    label_videoPreview->setObjectName("LineHidden");
    label_title->setObjectName("TitleLabel");
    label_prompt_tooptip->setObjectName("TooptipLabelImage");
    label_prompt->setObjectName("LineHidden");



    label_videoPreview->setText("视频预览");
    label_title->setText("歌曲详情");
    label_prompt->setText("为必填项目");
    pushButton_Yes->setText("确认");
    pushButton_update->setText("修改");
    pushButton_videoPreview->setText("预览");
    pushButton_save->setText("保存");

    widgetSave->setHidden(true);
    widgetUpdate->setHidden(false);
    info->infoLayout->setSpacing(22);
    selectStyleSheet(true);
    info->set_disabled();
}

void SongInfoDialog::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void SongInfoDialog::setTitleString(const QString &title)
{
    label_title->setText(title);
}

void SongInfoDialog::setSqlPointer(MysqlQuery *sql)
{
    _sql = sql;
}

void SongInfoDialog::setValue(const Media _media)
{
    mid = _media.mid.toLongLong();
    info->setMediaValue(_media);
    //    for (int i=0; i<_media.musicTag.size(); i++)
}

void SongInfoDialog::setComboBoxValue(QComboBox *combobox, QList<QString> list)
{
    QStringList items(list);
    if(items.isEmpty())
        return;
    QString currentStr = combobox->currentText();
    int index = list.indexOf(currentStr);

    combobox->clear();
    combobox->insertItems(0, items);
    combobox->setCurrentIndex(index);
}

void SongInfoDialog::updateMediaValue()
{    
    selectStyleSheet(false);
    info->set_enabled();
    widgetSave->setHidden(false);
    widgetUpdate->setHidden(true);
    setTitleString("歌曲修改");

    setComboBoxValue(info->comboBox_language, info->language.values());
    setComboBoxValue(info->comboBox_version, info->version.values());
    setComboBoxValue(info->comboBox_source, info->source.values());
    setComboBoxValue(info->comboBox_type, info->type.values());
    setComboBoxValue(info->comboBox_resolution, info->resolution.values());
    setComboBoxValue(info->comboBox_rthym, info->rthym.values());
    setComboBoxValue(info->comboBox_match, info->match.values());
    setComboBoxValue(info->comboBox_enabled, info->enabled.values());
    setComboBoxValue(info->comboBox_original_track, info->track.values());
    setComboBoxValue(info->comboBox_sound_track, info->track.values());
    setComboBoxValue(info->comboBox_quality, info->quality.values());
    setComboBoxValue(info->comboBox_effect, info->effect.values());
    setComboBoxValue(info->comboBox_pitch, info->pitch.values());
}

void SongInfoDialog::save()
{
    QString title("保存提示");
    QString content("必填项未填写完整！");
    QMessageBox box(QMessageBox::Warning, title, content);
    box.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    box.setButtonText(QMessageBox::Ok, "确定");
    box.setButtonText(QMessageBox::Cancel, "取消");

    if(info->isEmpty()){
        box.exec();
        return;
    }

    Media media;
    info->getMediaValue(media);

//    qint64 ser_id = _sql->isMediaSerialId(media.serial_id.toLongLong());
//    if(ser_id)
//    {
//        content = QString("serial_id : %1已经存在!\n 最大serial_id : %2").arg(media.serial_id).arg(ser_id);
//        box.exec();
//        return;
//    }

    QFile file(media.path);
    if(file.exists())
        media.path = info->uploadV(media.path);

    file.setFileName(media.lyric);
    if(file.exists())
        media.lyric = info->uploadL(media.lyric);


    media.update_time = QDateTime::currentDateTime().toString("yyyy-MM-dd");
    if(mid != -1){
        if(_sql->updateMedia(mid, media, info->media))
            this->close();
    }
}

void SongInfoDialog::selectStyleSheet(bool hidden)
{
    QString sytle = "QLabel#Label{\
                        background: transparent;\
                        font-size: 14px;\
                     }\
                    QLabel#TooptipLabel{\
                        image:url(:/other/images/required.png);\
                    }\
                    QPushButton#Button{\
                    background-color: rgb(255, 255, 255);\
                    border: 1px solid rgb(170, 170, 170);\
                    color:rgb(88, 88, 88);\
                    font-size:14px;\
                    border-radius:5px;\
                    }\
                    QPushButton#Button:hover{\
                    background-color:rgb(255, 255, 255);\
                    border: 1px solid rgb(42, 42, 42);\
                    color:rgb(42, 42, 42);\
                    }\
                    QPushButton#Button:pressed{\
                    background-color: rgb(255, 146, 62);\
                    border: 1px solid rgb(255, 146, 62);\
                    color:rgb(255, 255, 255);\
                    }\
                    QPushButton#CalendarButton{\
                    border-image:url(:/other/images/calendar_normal.png);\
                    }\
                    QPushButton#CalendarButton:hover{\
                    border-image:url(:/other/images/calendar_hovering.png);\
                    }\
                    \
                    QPushButton#CalendarButton:pressed{\
                    border-image:url(:/other/images/calendar_pressed.png);\
                    }\
                    \
                    QPushButton#AnnotationButton{\
                    border-image:url(:/other/images/annotation_normal.png);\
                    }\
                    QPushButton#AnnotationButton:pressed{\
                    border-image:url(:/other/images/annotation_pressed.png);\
                    }\
                    \
                    QPushButton#PlusButton{\
                    border-image:url(:/other/images/plus_normal.png);\
                    }\
                    \
                    QPushButton#PlusButton:hover{\
                    border-image:url(:/other/images/plus_on.png);\
                    }\
                    \
                    QPushButton#PlusButton:pressed{\
                    border-image:url(:/other/images/plus_pressed.png);\
                    }\
                    \
                    QPushButton#PlusButton:disabled{\
                    border-image:url(:/other/images/plus_gray.png);\
                    }\
                    \
                    QLineEdit#LineEdit{\
                    border: 1px solid rgb(170, 170, 170);\
                    color:rgb(202, 202, 202);\
                    border-radius:5px;\
                    }\
                    QLineEdit#LineEdit:hover{\
                    border: 1px solid rgb(42, 42, 42);\
                    color:rgb(202, 202, 202);\
                    }\
                    QLineEdit#LineEdit:pressed{\
                    border: 1px solid rgb(255, 146, 62);\
                    color:rgb(88, 88, 88);\
                    }\
                    QLineEdit#LineEdit:disabled{\
                    color:rgb(202, 202, 202);\
                    border: 1px solid rgb(170, 170, 170);\
                    }\
                    \
                    \
                    QComboBox#Combobox{\
                    border:1px solid rgb(170, 170, 170);\
                    border-radius:5px;\
                    font-size:14px;\
                    color:rgb(88, 88, 88);\
                    }\
                    QComboBox#Combobox::down-arrow{\
                    image:url(:/arrow/images/combobox_down.png);\
                    }\
                    QComboBox#Combobox::down-arrow:on{\
                    image:url(:/arrow/images/combobox_up.png);\
                    }\
                    QComboBox#Combobox QAbstractItemView{\
                     border:1px solid rgb(255, 146, 62);\
                     selection-color:rgb(255, 255, 255);\
                     selection-background-color:rgb(255, 146, 62);\
                     color:rgb(00, 00, 00);\
                    }\
                    \
                    QComboBox#Combobox QAbstractItemView::item{\
                        height:30px;\
                    }\
                    \
                    QComboBox#Combobox::drop-down{\
                    width:20px;\
                    border:none;\
                    }\
                    QComboBox#Combobox:on{\
                    border:1px solid rgb(255, 146, 62);\
                    border-top-left-radius:5px;\
                    border-top-right-radius:5px;\
                    border-bottom-left-radius:0px;\
                    border-bottom-right-radius:0px;\
                    }\
                    \
                    QComboBox#Combobox:hover{\
                    border:1px solid rgb(42, 42, 42);\
                    color:rgb(42, 42, 42);\
                    }\
                    QComboBox#Combobox:disabled{\
                    border:1px solid rgb(201, 201, 201);\
                    color:rgb(225, 225, 225);\
                    }";


    QString hiddenStyle = "QLabel{\
                    background: transparent;\
                    color:rgb(183, 183, 183);\
                    font-size: 14px;\
                }\
                \
                QLineEdit{\
                    background: transparent;\
                    border: 0px;\
                    color:rgb(88, 88, 88);\
                    border-radius:5px;\
                }\
                \
                \
                QComboBox{\
                    background: transparent;\
                    border:0px;\
                    border-radius:5px;\
                    font-size:14px;\
                    color:rgb(88, 88, 88);\
                }\
                \
                QComboBox::down-arrow{\
                    border-style:none;\
                }\
                QComboBox::down-arrow:on{\
                    border-style:none;\
                }\
                QComboBox QAbstractItemView{\
                     border:1px solid rgb(255, 146, 62);\
                     selection-color:rgb(255, 255, 255);\
                     selection-background-color:rgb(255, 146, 62);\
                     color:rgb(00, 00, 00);\
                }\
                \
                QComboBox QAbstractItemView::item{\
                        height:30px;\
                }\
                \
                QComboBox::drop-down{\
                    width:20px;\
                    border:none;\
                }\
                QComboBox:on{\
                    border:0px solid rgb(255, 146, 62);\
                    border-top-left-radius:5px;\
                    border-top-right-radius:5px;\
                    border-bottom-left-radius:0px;\
                    border-bottom-right-radius:0px;\
                }";

    if (hidden){
        info->setStyleSheet(hiddenStyle);
        label_videoPreview->setStyleSheet("background: transparent;\
                                           color:rgb(183, 183, 183);\
                                           font-size: 14px;");
    }
    else{
        info->setStyleSheet(sytle);
        label_videoPreview->setStyleSheet("background: transparent;\
                                           color:rgb(0, 0, 0  );\
                                           font-size: 14px;");
    }
}


