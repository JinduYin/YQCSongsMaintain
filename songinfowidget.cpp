#include "songinfowidget.h"
#include "curlupload.h"
#include "singeraddmodifydialog.h"
#include <QFile>
#include <QLabel>
#include <QPainter>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QFileDialog>
#include <QCalendarWidget>
#include <QProcessEnvironment>
#include <QCursor>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QDebug>

SongInfoWidget::SongInfoWidget(QWidget *parent)
    : QWidget(parent)
{
    initWidget();
    readAndSetStyleSheet();
    setWidgetSize();
    initWidgetValue();
    isRequired();

    match.insert(1, "是");
    match.insert(0, "否");

    enabled.insert(1, "启用");
    enabled.insert(0, "禁用");

    track.insert(0, "0");
    track.insert(1, "1");

    connect(PushButton_question, &QPushButton::pressed, this, &SongInfoWidget::PushButton_question_pressed);
    connect(PushButton_question, &QPushButton::released, this, &SongInfoWidget::PushButton_question_released);
    connect(pushButton_calendar, &QPushButton::clicked, this, &SongInfoWidget::getCalendarDate);
    connect(calendar, &QCalendarWidget::selectionChanged, this, &SongInfoWidget::setDateTime);

    connect(pushButton_addSinger, &QPushButton::clicked, this, &SongInfoWidget::addSinger);
    connect(pushButton_upload_video, &QPushButton::clicked, this, &SongInfoWidget::uploadVideo);
    connect(pushButton_upload_lyric, &QPushButton::clicked, this, &SongInfoWidget::uploadLyric);
}

SongInfoWidget::~SongInfoWidget()
{

}

void SongInfoWidget::readAndSetStyleSheet()
{
    QFile qss(":/qss/songinfo.qss");
    qss.open(QFile::ReadOnly);
    this->setStyleSheet(qss.readAll());
    qss.close();

    this->setObjectName("Widget");    

    lineEdit_serial_id->setObjectName("LineEdit");
    lineEdit_upload_video->setObjectName("LineEdit");
    lineEdit_pinyin->setObjectName("LineEdit");
    lineEdit_head->setObjectName("LineEdit");
    lineEdit_create_time->setObjectName("LineEdit");

    lineEdit_name->setObjectName("LineEdit");
    lineEdit_lyric->setObjectName("LineEdit");
    lineEdit_header->setObjectName("LineEdit");
    lineEdit_words->setObjectName("LineEdit");
    lineEdit_prelude->setObjectName("LineEdit");

    lineEdit_addSinger->setObjectName("LineEdit");
    lineEdit_info->setObjectName("LineEdit");


    comboBox_language->setObjectName("Combobox");
    comboBox_version->setObjectName("Combobox");
    comboBox_source->setObjectName("Combobox");

    comboBox_type->setObjectName("Combobox");
    comboBox_resolution->setObjectName("Combobox");
    comboBox_rthym->setObjectName("Combobox");

    comboBox_match->setObjectName("Combobox");
    comboBox_enabled->setObjectName("Combobox");
    comboBox_original_track->setObjectName("Combobox");
    comboBox_sound_track->setObjectName("Combobox");
    comboBox_quality->setObjectName("Combobox");
    comboBox_effect->setObjectName("Combobox");
    comboBox_pitch->setObjectName("Combobox");

    comboBox_attribute01->setObjectName("Combobox");
    comboBox_attribute02->setObjectName("Combobox");
    comboBox_attribute03->setObjectName("Combobox");
    comboBox_attribute04->setObjectName("Combobox");
    comboBox_attribute05->setObjectName("Combobox");
    comboBox_attribute06->setObjectName("Combobox");

    pushButton_calendar->setObjectName("CalendarButton");
    pushButton_addSinger->setObjectName("Button");
    pushButton_upload_video->setObjectName("Button");
    pushButton_upload_lyric->setObjectName("Button");
    PushButton_question->setObjectName("AnnotationButton");
    PushButton_attribute->setObjectName("PlusButton");
}

void SongInfoWidget::initWidget()
{
    widgetLeft = new QWidget(this);
    widgetCenter = new QWidget(this);
    widgetRight = new QWidget(this);
    widgetTrack = new QWidget(widgetRight);        

    calendar = new QCalendarWidget(this);
    calendar->resize(280, 180);

    label_serial_id = new QLabel(widgetLeft);
    label_upload_video = new QLabel(widgetLeft);
    label_language = new QLabel(widgetLeft);
    label_version = new QLabel(widgetLeft);
    label_pinyin = new QLabel(widgetLeft);
    label_head = new QLabel(widgetLeft);
    label_source = new QLabel(widgetLeft);
    label_create_time = new QLabel(widgetLeft);

    label_name = new QLabel(widgetCenter);
    label_lyric = new QLabel(widgetCenter);
    label_type = new QLabel(widgetCenter);
    label_resolution = new QLabel(widgetCenter);
    label_header = new QLabel(widgetCenter);
    label_words = new QLabel(widgetCenter);
    label_prelude = new QLabel(widgetCenter);
    label_prelude_unit = new QLabel(widgetCenter);
    label_rthym = new QLabel(widgetCenter);

    label_addSinger = new QLabel(widgetRight);
    label_match = new QLabel(widgetCenter);
    label_enabled = new QLabel(widgetCenter);
    label_track = new QLabel(widgetCenter);
    label_original_track = new QLabel(widgetCenter);
    label_sound_track = new QLabel(widgetCenter);
    label_quality = new QLabel(widgetCenter);
    label_effect = new QLabel(widgetCenter);
    label_info = new QLabel(widgetCenter);
    label_pitch = new QLabel(widgetCenter);

    label_attribute = new QLabel(this);

    label_serial_id_tooptip = new QLabel(widgetLeft);
    label_upload_video_tooptip = new QLabel(widgetLeft);
    label_language_tooptip = new QLabel(widgetLeft);
    label_version_tooptip = new QLabel(widgetLeft);
    label_pinyin_tooptip = new QLabel(widgetLeft);
    label_head_tooptip = new QLabel(widgetLeft);
    label_source_tooptip = new QLabel(widgetLeft);
    label_create_time_tooptip = new QLabel(widgetLeft);

    label_name_tooptip = new QLabel(widgetCenter);
    label_lyric_tooptip = new QLabel(widgetCenter);
    label_type_tooptip = new QLabel(widgetCenter);
    label_resolution_tooptip = new QLabel(widgetCenter);
    label_header_tooptip = new QLabel(widgetCenter);
    label_words_tooptip = new QLabel(widgetCenter);
    label_prelude_tooptip = new QLabel(widgetCenter);
    label_rthym_tooptip = new QLabel(widgetCenter);

    label_addSinger_tooptip = new QLabel(widgetRight);
    label_match_tooptip = new QLabel(widgetRight);
    label_enabled_tooptip = new QLabel(widgetRight);
    label_track_tooptip = new QLabel(widgetRight);
    label_quality_tooptip = new QLabel(widgetRight);
    label_effect_tooptip = new QLabel(widgetRight);
    label_info_tooptip = new QLabel(widgetRight);
    label_pitch_tooptip = new QLabel(widgetRight);

    label_attribute_tooptip = new QLabel(this);

    lineEdit_serial_id = new QLineEdit(widgetLeft);
    lineEdit_upload_video = new QLineEdit(widgetLeft);
    lineEdit_pinyin = new QLineEdit(widgetLeft);
    lineEdit_head = new QLineEdit(widgetLeft);
    lineEdit_create_time = new QLineEdit(widgetLeft);

    lineEdit_name = new QLineEdit(widgetCenter);
    lineEdit_lyric = new QLineEdit(widgetCenter);
    lineEdit_header = new QLineEdit(widgetCenter);
    lineEdit_words = new QLineEdit(widgetCenter);
    lineEdit_prelude = new QLineEdit(widgetCenter);

    lineEdit_addSinger = new QLineEdit(widgetRight);
    lineEdit_info = new QLineEdit(widgetRight);

    comboBox_language = new QComboBox(widgetLeft);
    comboBox_version = new QComboBox(widgetLeft);
    comboBox_source = new QComboBox(widgetLeft);

    comboBox_type = new QComboBox(widgetCenter);
    comboBox_resolution = new QComboBox(widgetCenter);
    comboBox_rthym = new QComboBox(widgetCenter);

    comboBox_match = new QComboBox(widgetRight);
    comboBox_enabled = new QComboBox(widgetRight);
    comboBox_original_track = new QComboBox(widgetRight);
    comboBox_sound_track = new QComboBox(widgetRight);
    comboBox_quality = new QComboBox(widgetRight);
    comboBox_effect = new QComboBox(widgetRight);
    comboBox_pitch = new QComboBox(widgetRight);

    comboBox_attribute01 = new QComboBox(this);
    comboBox_attribute02 = new QComboBox(this);
    comboBox_attribute03 = new QComboBox(this);
    comboBox_attribute04 = new QComboBox(this);
    comboBox_attribute05 = new QComboBox(this);
    comboBox_attribute06 = new QComboBox(this);

    pushButton_calendar = new QPushButton(lineEdit_create_time);
    pushButton_addSinger = new QPushButton(widgetRight);
    pushButton_upload_video = new QPushButton(widgetLeft);
    pushButton_upload_lyric = new QPushButton(widgetCenter);
    PushButton_question = new QPushButton(widgetRight);
    PushButton_attribute = new QPushButton(this);


    serial_id_layout = new QHBoxLayout();
    upload_video_pushbutton_layout = new QHBoxLayout();
    upload_video_layout = new QHBoxLayout();
    language_layout = new QHBoxLayout();
    version_layout = new QHBoxLayout();
    pinyin_layout = new QHBoxLayout();
    head_layout = new QHBoxLayout();
    source_layout = new QHBoxLayout();
    create_time_layout = new QHBoxLayout();
    leftLayout = new QVBoxLayout();

    serial_id_layout->addWidget(label_serial_id_tooptip);
    serial_id_layout->addWidget(label_serial_id);
    serial_id_layout->addWidget(lineEdit_serial_id);
    serial_id_layout->setContentsMargins(0, 0, 0, 0);
    serial_id_layout->setSpacing(0);

    upload_video_pushbutton_layout->addWidget(lineEdit_upload_video);
    upload_video_pushbutton_layout->addWidget(pushButton_upload_video);
    upload_video_pushbutton_layout->setContentsMargins(0, 0, 0, 0);
    upload_video_pushbutton_layout->setSpacing(10);
    upload_video_layout->addWidget(label_upload_video_tooptip);
    upload_video_layout->addWidget(label_upload_video);
    upload_video_layout->addLayout(upload_video_pushbutton_layout);
    upload_video_layout->addStretch();
    upload_video_layout->setContentsMargins(0, 0, 0, 0);
    upload_video_layout->setSpacing(0);

    language_layout->addWidget(label_language_tooptip);
    language_layout->addWidget(label_language);
    language_layout->addWidget(comboBox_language);
    language_layout->setContentsMargins(0, 0, 0, 0);
    language_layout->setSpacing(0);

    version_layout->addWidget(label_version_tooptip);
    version_layout->addWidget(label_version);
    version_layout->addWidget(comboBox_version);
    version_layout->setContentsMargins(0, 0, 0, 0);
    version_layout->setSpacing(0);

    pinyin_layout->addWidget(label_pinyin_tooptip);
    pinyin_layout->addWidget(label_pinyin);
    pinyin_layout->addWidget(lineEdit_pinyin);
    pinyin_layout->setContentsMargins(0, 0, 0, 0);
    pinyin_layout->setSpacing(0);

    head_layout->addWidget(label_head_tooptip);
    head_layout->addWidget(label_head);
    head_layout->addWidget(lineEdit_head);
    head_layout->setContentsMargins(0, 0, 0, 0);
    head_layout->setSpacing(0);

    source_layout->addWidget(label_source_tooptip);
    source_layout->addWidget(label_source);
    source_layout->addWidget(comboBox_source);
    source_layout->setContentsMargins(0, 0, 0, 0);
    source_layout->setSpacing(0);

    create_time_layout->addWidget(label_create_time_tooptip);
    create_time_layout->addWidget(label_create_time);
    create_time_layout->addWidget(lineEdit_create_time);
    create_time_layout->setContentsMargins(0, 0, 0, 0);
    create_time_layout->setSpacing(0);

    leftLayout->addLayout(serial_id_layout);
    leftLayout->addLayout(upload_video_layout);
    leftLayout->addLayout(language_layout);
    leftLayout->addLayout(version_layout);
    leftLayout->addLayout(pinyin_layout);
    leftLayout->addLayout(head_layout);
    leftLayout->addLayout(source_layout);
    leftLayout->addLayout(create_time_layout);
    leftLayout->setContentsMargins(0, 0, 0, 0);
    leftLayout->setSpacing(10);
    widgetLeft->setLayout(leftLayout);



    name_layout = new QHBoxLayout();
    upload_lyric_pushbutton_layout = new QHBoxLayout();
    upload_lyric_layout = new QHBoxLayout();
    type_layout = new QHBoxLayout();
    resolution_layout = new QHBoxLayout();
    header_layout = new QHBoxLayout();
    words_layout = new QHBoxLayout();
    prelude_layout = new QHBoxLayout();
    prelude_unit_layout = new QHBoxLayout();
    rthym_layout = new QHBoxLayout();
    centerLayout = new QVBoxLayout();

    name_layout->addWidget(label_name_tooptip);
    name_layout->addWidget(label_name);
    name_layout->addWidget(lineEdit_name);
    name_layout->setContentsMargins(0, 0, 0, 0);
    name_layout->setSpacing(0);

    upload_lyric_pushbutton_layout->addWidget(lineEdit_lyric);
    upload_lyric_pushbutton_layout->addWidget(pushButton_upload_lyric);
    upload_lyric_pushbutton_layout->setContentsMargins(0, 0, 0, 0);
    upload_lyric_pushbutton_layout->setSpacing(10);
    upload_lyric_layout->addWidget(label_lyric_tooptip);
    upload_lyric_layout->addWidget(label_lyric);
    upload_lyric_layout->addLayout(upload_lyric_pushbutton_layout);
    upload_lyric_layout->addStretch();
    upload_lyric_layout->setContentsMargins(0, 0, 0, 0);
    upload_lyric_layout->setSpacing(0);

    type_layout->addWidget(label_type_tooptip);
    type_layout->addWidget(label_type);
    type_layout->addWidget(comboBox_type);
    type_layout->setContentsMargins(0, 0, 0, 0);
    type_layout->setSpacing(0);

    resolution_layout->addWidget(label_resolution_tooptip);
    resolution_layout->addWidget(label_resolution);
    resolution_layout->addWidget(comboBox_resolution);
    resolution_layout->setContentsMargins(0, 0, 0, 0);
    resolution_layout->setSpacing(0);

    header_layout->addWidget(label_header_tooptip);
    header_layout->addWidget(label_header);
    header_layout->addWidget(lineEdit_header);
    header_layout->setContentsMargins(0, 0, 0, 0);
    header_layout->setSpacing(0);

    words_layout->addWidget(label_words_tooptip);
    words_layout->addWidget(label_words);
    words_layout->addWidget(lineEdit_words);
    words_layout->setContentsMargins(0, 0, 0, 0);
    words_layout->setSpacing(0);

    prelude_unit_layout->addWidget(lineEdit_prelude);
    prelude_unit_layout->addWidget(label_prelude_unit);
    prelude_unit_layout->setContentsMargins(0, 0, 0, 0);
    prelude_unit_layout->setSpacing(10);
    prelude_layout->addWidget(label_prelude_tooptip);
    prelude_layout->addWidget(label_prelude);
    prelude_layout->addLayout(prelude_unit_layout);
    prelude_layout->addStretch();
    prelude_layout->setContentsMargins(0, 0, 0, 0);
    prelude_layout->setSpacing(0);

    rthym_layout->addWidget(label_rthym_tooptip);
    rthym_layout->addWidget(label_rthym);
    rthym_layout->addWidget(comboBox_rthym);
    rthym_layout->setContentsMargins(0, 0, 0, 0);
    rthym_layout->setSpacing(0);

    centerLayout->addLayout(name_layout);
    centerLayout->addLayout(upload_lyric_layout);
    centerLayout->addLayout(type_layout);
    centerLayout->addLayout(resolution_layout);
    centerLayout->addLayout(header_layout);
    centerLayout->addLayout(words_layout);
    centerLayout->addLayout(prelude_layout);
    centerLayout->addLayout(rthym_layout);
    centerLayout->setContentsMargins(0, 0, 0, 0);
    centerLayout->setSpacing(10);
    widgetCenter->setLayout(centerLayout);


    addSinger_pushbutton_layout = new QHBoxLayout();
    addSinger_layout = new QHBoxLayout();
    match_layout = new QHBoxLayout();
    enabled_layout = new QHBoxLayout();
    track_layout = new QHBoxLayout();
    track_help_layout = new QHBoxLayout();
    original_track_layout = new QHBoxLayout();
    sound_track_layout = new QHBoxLayout();
    quality_layout = new QHBoxLayout();
    effect_layout = new QHBoxLayout();
    info_layout = new QHBoxLayout();
    pitch_layout = new QHBoxLayout();
    rightLayout = new QVBoxLayout();

    addSinger_pushbutton_layout->addWidget(pushButton_addSinger);
    addSinger_pushbutton_layout->addWidget(lineEdit_addSinger);
    addSinger_pushbutton_layout->setContentsMargins(0, 0, 0, 0);
    addSinger_pushbutton_layout->setSpacing(10);
    addSinger_layout->addWidget(label_addSinger_tooptip);
    addSinger_layout->addWidget(label_addSinger);
    addSinger_layout->addLayout(addSinger_pushbutton_layout);
    addSinger_layout->addStretch();
    addSinger_layout->setContentsMargins(0, 0, 0, 0);
    addSinger_layout->setSpacing(0);

    match_layout->addWidget(label_match_tooptip);
    match_layout->addWidget(label_match);
    match_layout->addWidget(comboBox_match);
    match_layout->setContentsMargins(0, 0, 0, 0);
    match_layout->setSpacing(0);

    enabled_layout->addWidget(label_enabled_tooptip);
    enabled_layout->addWidget(label_enabled);
    enabled_layout->addWidget(comboBox_enabled);
    enabled_layout->setContentsMargins(0, 0, 0, 0);
    enabled_layout->setSpacing(0);

    original_track_layout->addWidget(label_original_track);
    original_track_layout->addWidget(comboBox_original_track);
    original_track_layout->setContentsMargins(0, 0, 0, 0);
    original_track_layout->setSpacing(8);
    sound_track_layout->addWidget(label_sound_track);
    sound_track_layout->addWidget(comboBox_sound_track);
    sound_track_layout->setContentsMargins(0, 0, 0, 0);
    sound_track_layout->setSpacing(8);
    track_help_layout->addLayout(original_track_layout);
    track_help_layout->addLayout(sound_track_layout);
    track_help_layout->addWidget(PushButton_question);    
    track_help_layout->setContentsMargins(0, 0, 0, 0);
    track_help_layout->setSpacing(10);
    widgetTrack->setLayout(track_help_layout);

    track_layout->addWidget(label_track_tooptip);
    track_layout->addWidget(label_track);
    track_layout->addWidget(widgetTrack);
    track_layout->addStretch();
    track_layout->setContentsMargins(0, 0, 0, 0);
    track_layout->setSpacing(0);


    quality_layout->addWidget(label_quality_tooptip, 0, Qt::AlignLeft);
    quality_layout->addWidget(label_quality, 0, Qt::AlignLeft);
    quality_layout->addWidget(comboBox_quality);
    quality_layout->setContentsMargins(0, 0, 0, 0);
    quality_layout->setSpacing(0);

    effect_layout->addWidget(label_effect_tooptip);
    effect_layout->addWidget(label_effect);
    effect_layout->addWidget(comboBox_effect);
    effect_layout->setContentsMargins(0, 0, 0, 0);
    effect_layout->setSpacing(0);

    info_layout->addWidget(label_info_tooptip);
    info_layout->addWidget(label_info);
    info_layout->addWidget(lineEdit_info);
    info_layout->setContentsMargins(0, 0, 0, 0);
    info_layout->setSpacing(0);

    pitch_layout->addWidget(label_pitch_tooptip);
    pitch_layout->addWidget(label_pitch);
    pitch_layout->addWidget(comboBox_pitch);
    pitch_layout->setContentsMargins(0, 0, 0, 0);
    pitch_layout->setSpacing(0);

    rightLayout->addLayout(addSinger_layout);
    rightLayout->addLayout(match_layout);
    rightLayout->addLayout(enabled_layout);
    rightLayout->addLayout(track_layout);
    rightLayout->addLayout(quality_layout);
    rightLayout->addLayout(effect_layout);
    rightLayout->addLayout(info_layout);
    rightLayout->addLayout(pitch_layout);

    widgetRight->setLayout(rightLayout);

    infoLayout = new QHBoxLayout();
    infoLayout->addWidget(widgetLeft);
    infoLayout->addWidget(widgetCenter);
    infoLayout->addWidget(widgetRight);
    infoLayout->addStretch();
    infoLayout->setContentsMargins(0, 0, 0, 0);
    infoLayout->setSpacing(36);

    attributeAddLayout = new QHBoxLayout();
    attributeLayout = new QHBoxLayout();
    attributeAddLayout->addWidget(comboBox_attribute01);
    attributeAddLayout->addWidget(comboBox_attribute02);
    attributeAddLayout->addWidget(comboBox_attribute03);
    attributeAddLayout->addWidget(comboBox_attribute04);
    attributeAddLayout->addWidget(comboBox_attribute05);
    attributeAddLayout->addWidget(comboBox_attribute06);
    attributeAddLayout->addWidget(PushButton_attribute);
    attributeAddLayout->addStretch();
    attributeAddLayout->setContentsMargins(0, 0, 0, 0);
    attributeAddLayout->setSpacing(10);

    attributeLayout->addWidget(label_attribute_tooptip);
    attributeLayout->addWidget(label_attribute);
    attributeLayout->addLayout(attributeAddLayout);
    attributeLayout->setContentsMargins(0, 0, 0, 0);
    attributeLayout->setSpacing(0);

    vLayout = new QVBoxLayout();
    vLayout->addLayout(infoLayout);
    vLayout->addLayout(attributeLayout);
    vLayout->setContentsMargins(0, 0, 0, 0);
    vLayout->setSpacing(10);

    this->setLayout(vLayout);
}

void SongInfoWidget::initWidgetValue()
{
    label_serial_id->setText("SERIAL_ID");
    label_upload_video->setText("上传视频");
    label_language->setText("歌曲语种");
    label_version->setText("版本类型");
    label_pinyin->setText("名称全拼");
    label_head->setText("名称第一个\n字首字母");
    label_source->setText("歌曲来源");
    label_create_time->setText("发布时间");


    label_name->setText("歌曲名称");
    label_lyric->setText("上传歌词");
    label_type->setText("歌曲分类");
    label_resolution->setText("分 辨 率");
    label_header->setText("名称首拼");
    label_words->setText("名称字数");
    label_prelude->setText("前奏时间");
    label_prelude_unit->setText("S");
    label_rthym->setText("歌曲节奏");


    label_addSinger->setText("添加歌星");
    label_match->setText("是否K歌");
    label_enabled->setText("是否启用");
    label_track->setText("音    轨");
    label_original_track->setText("原唱");
    label_sound_track->setText("伴唱");
    label_quality->setText("音    质");
    label_effect->setText("音    效");
    label_info->setText("备    注");
    label_pitch->setText("音高类型");

    label_attribute->setText("标签属性");

    pushButton_upload_video->setText("上传");
    pushButton_upload_lyric->setText("上传");
    pushButton_addSinger->setText("选择");   
}

void SongInfoWidget::setWidgetSize()
{
    widgetTrack->setFixedWidth(250);    

    label_serial_id->setFixedWidth(80);
    label_upload_video->setFixedWidth(80);
    label_language->setFixedWidth(80);
    label_version->setFixedWidth(80);
    label_pinyin->setFixedWidth(80);
    label_head->setFixedWidth(80);
    label_source->setFixedWidth(80);
    label_create_time->setFixedWidth(80);

    label_name->setFixedWidth(80);
    label_lyric->setFixedWidth(80);
    label_type->setFixedWidth(80);
    label_resolution->setFixedWidth(80);
    label_header->setFixedWidth(80);
    label_words->setFixedWidth(80);
    label_prelude->setFixedWidth(80);
    label_prelude_unit->setFixedWidth(10);
    label_rthym->setFixedWidth(80);

    label_addSinger->setFixedWidth(80);
    label_match->setFixedWidth(80);
    label_enabled->setFixedWidth(80);
    label_track->setFixedWidth(80);
//    label_original_track->setFixedWidth(80);
//    label_sound_track->setFixedWidth(80);
    label_quality->setFixedWidth(80);
    label_effect->setFixedWidth(80);
    label_info->setFixedWidth(80);
    label_pitch->setFixedWidth(80);

    label_attribute->setFixedWidth(80);


    label_serial_id_tooptip->setFixedWidth(8);
    label_upload_video_tooptip->setFixedWidth(8);
    label_language_tooptip->setFixedWidth(8);
    label_version_tooptip->setFixedWidth(8);
    label_pinyin_tooptip->setFixedWidth(8);
    label_head_tooptip->setFixedWidth(8);
    label_source_tooptip->setFixedWidth(8);
    label_create_time_tooptip->setFixedWidth(8);

    label_name_tooptip->setFixedWidth(8);
    label_lyric_tooptip->setFixedWidth(8);
    label_type_tooptip->setFixedWidth(8);
    label_resolution_tooptip->setFixedWidth(8);
    label_header_tooptip->setFixedWidth(8);
    label_words_tooptip->setFixedWidth(8);
    label_prelude_tooptip->setFixedWidth(8);
    label_rthym_tooptip->setFixedWidth(8);

    label_addSinger_tooptip->setFixedWidth(8);
    label_match_tooptip->setFixedWidth(8);
    label_enabled_tooptip->setFixedWidth(8);
    label_track_tooptip->setFixedWidth(8);
    label_quality_tooptip->setFixedWidth(8);
    label_effect_tooptip->setFixedWidth(8);
    label_info_tooptip->setFixedWidth(8);
    label_pitch_tooptip->setFixedWidth(8);

    label_attribute_tooptip->setFixedWidth(8);


    lineEdit_serial_id->setFixedHeight(36);
    lineEdit_serial_id->setFixedWidth(250);
    lineEdit_upload_video->setFixedHeight(36);
    lineEdit_upload_video->setFixedWidth(180);
    lineEdit_pinyin->setFixedHeight(36);
    lineEdit_pinyin->setFixedWidth(250);
    lineEdit_head->setFixedHeight(36);
    lineEdit_head->setFixedWidth(250);
    lineEdit_create_time->setFixedHeight(36);
    lineEdit_create_time->setFixedWidth(250);

    lineEdit_name->setFixedHeight(36);
    lineEdit_name->setFixedWidth(250);
    lineEdit_lyric->setFixedHeight(36);
    lineEdit_lyric->setFixedWidth(180);
    lineEdit_header->setFixedHeight(36);
    lineEdit_header->setFixedWidth(250);
    lineEdit_words->setFixedHeight(36);
    lineEdit_words->setFixedWidth(250);
    lineEdit_prelude->setFixedHeight(36);
    lineEdit_prelude->setFixedWidth(230);
    lineEdit_addSinger->setFixedHeight(36);
    lineEdit_addSinger->setFixedWidth(180);
    lineEdit_info->setFixedHeight(36);
    lineEdit_info->setFixedWidth(250);


    comboBox_language->setFixedHeight(36);
    comboBox_language->setFixedWidth(250);
    comboBox_version->setFixedHeight(36);
    comboBox_version->setFixedWidth(250);
    comboBox_source->setFixedHeight(36);
    comboBox_source->setFixedWidth(250);

    comboBox_type->setFixedHeight(36);
    comboBox_type->setFixedWidth(250);
    comboBox_resolution->setFixedHeight(36);
    comboBox_resolution->setFixedWidth(250);
    comboBox_rthym->setFixedHeight(36);
    comboBox_rthym->setFixedWidth(250);

    comboBox_match->setFixedHeight(36);
    comboBox_match->setFixedWidth(250);
    comboBox_enabled->setFixedHeight(36);
    comboBox_enabled->setFixedWidth(250);
    comboBox_original_track->setFixedHeight(36);
    comboBox_original_track->setFixedWidth(60);
    comboBox_sound_track->setFixedHeight(36);
    comboBox_sound_track->setFixedWidth(60);
    comboBox_quality->setFixedHeight(36);
    comboBox_quality->setFixedWidth(250);
    comboBox_effect->setFixedHeight(36);
    comboBox_effect->setFixedWidth(250);
    comboBox_pitch->setFixedHeight(36);
    comboBox_pitch->setFixedWidth(250);

    comboBox_attribute01->setFixedHeight(36);
    comboBox_attribute01->setFixedWidth(120);
    comboBox_attribute02->setFixedHeight(36);
    comboBox_attribute02->setFixedWidth(120);
    comboBox_attribute03->setFixedHeight(36);
    comboBox_attribute03->setFixedWidth(120);
    comboBox_attribute04->setFixedHeight(36);
    comboBox_attribute04->setFixedWidth(120);
    comboBox_attribute05->setFixedHeight(36);
    comboBox_attribute05->setFixedWidth(120);
    comboBox_attribute06->setFixedHeight(36);
    comboBox_attribute06->setFixedWidth(120);


    pushButton_addSinger->setFixedHeight(36);
    pushButton_addSinger->setFixedWidth(60);
    pushButton_upload_video->setFixedHeight(36);
    pushButton_upload_video->setFixedWidth(60);
    pushButton_upload_lyric->setFixedHeight(36);
    pushButton_upload_lyric->setFixedWidth(60);
    PushButton_question->setFixedHeight(30);
    PushButton_question->setFixedWidth(30);
    PushButton_attribute->setFixedHeight(36);
    PushButton_attribute->setFixedWidth(36);

    QRect rect = lineEdit_create_time->geometry();
    lineEdit_create_time->setTextMargins(0, 0, 20, 0);
    pushButton_calendar->setGeometry(rect.width()-25, 10, 20, 20);
    pushButton_calendar->setCursor(Qt::PointingHandCursor);

    pushButton_calendar->setCheckable(true);
    calendar->setGeometry(this->x() + 180, this->y()+140, 280, 180);
    calendar->setHidden(true);
}

void SongInfoWidget::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);   
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void SongInfoWidget::set_disabled()
{
    lineEdit_serial_id->setEnabled(false);
    lineEdit_upload_video->setEnabled(false);
    lineEdit_pinyin->setEnabled(false);
    lineEdit_head->setEnabled(false);
    lineEdit_create_time->setEnabled(false);

    lineEdit_name->setEnabled(false); //lineEdit_name->setDisabled();
    lineEdit_lyric->setEnabled(false);
    lineEdit_header->setEnabled(false);
    lineEdit_words->setEnabled(false);
    lineEdit_prelude->setEnabled(false);

    lineEdit_addSinger->setEnabled(false);
    lineEdit_info->setEnabled(false);

    comboBox_language->setEnabled(false);
    comboBox_version->setEnabled(false);
    comboBox_source->setEnabled(false);

    comboBox_type->setEnabled(false);
    comboBox_resolution->setEnabled(false);
    comboBox_rthym->setEnabled(false);

    comboBox_match->setEnabled(false);
    comboBox_enabled->setEnabled(false);
    comboBox_original_track->setEnabled(false);
    comboBox_sound_track->setEnabled(false);
    comboBox_quality->setEnabled(false);
    comboBox_effect->setEnabled(false);
    comboBox_pitch->setEnabled(false);

    comboBox_attribute01->setEnabled(false);
    comboBox_attribute02->setEnabled(false);
    comboBox_attribute03->setEnabled(false);
    comboBox_attribute04->setEnabled(false);
    comboBox_attribute05->setEnabled(false);
    comboBox_attribute06->setEnabled(false);


    pushButton_calendar->setHidden(true);
    pushButton_addSinger->setHidden(true);
    pushButton_upload_video->setHidden(true);
    pushButton_upload_lyric->setHidden(true);
    PushButton_question->setHidden(true);
    PushButton_attribute->setHidden(true);
}

void SongInfoWidget::set_enabled()
{
    lineEdit_serial_id->setEnabled(true);
    lineEdit_upload_video->setEnabled(true);
    lineEdit_pinyin->setEnabled(true);
    lineEdit_head->setEnabled(true);
    lineEdit_create_time->setEnabled(true);

    lineEdit_name->setEnabled(true); //lineEdit_name->setDisabled();
    lineEdit_lyric->setEnabled(true);
    lineEdit_header->setEnabled(true);
    lineEdit_words->setEnabled(true);
    lineEdit_prelude->setEnabled(true);

    lineEdit_addSinger->setEnabled(true);
    lineEdit_info->setEnabled(true);

    comboBox_language->setEnabled(true);
    comboBox_version->setEnabled(true);
    comboBox_source->setEnabled(true);

    comboBox_type->setEnabled(true);
    comboBox_resolution->setEnabled(true);
    comboBox_rthym->setEnabled(true);

    comboBox_match->setEnabled(true);
    comboBox_enabled->setEnabled(true);
    comboBox_original_track->setEnabled(true);
    comboBox_sound_track->setEnabled(true);
    comboBox_quality->setEnabled(true);
    comboBox_effect->setEnabled(true);
    comboBox_pitch->setEnabled(true);

    comboBox_attribute01->setEnabled(true);
    comboBox_attribute02->setEnabled(true);
    comboBox_attribute03->setEnabled(true);
    comboBox_attribute04->setEnabled(true);
    comboBox_attribute05->setEnabled(true);
    comboBox_attribute06->setEnabled(true);


    pushButton_calendar->setHidden(false);
    pushButton_addSinger->setHidden(false);
    pushButton_upload_video->setHidden(false);
    pushButton_upload_lyric->setHidden(false);
    PushButton_question->setHidden(false);
    PushButton_attribute->setHidden(false);
}

void SongInfoWidget::isRequired()
{
    label_serial_id_tooptip->setObjectName("TooptipLabel");
    label_upload_video_tooptip->setObjectName("TooptipLabel");
    label_language_tooptip->setObjectName("TooptipLabel");
    label_version_tooptip->setObjectName("TooptipLabel");
    label_pinyin_tooptip->setObjectName("TooptipLabel");
    label_head_tooptip->setObjectName("TooptipLabel");
    label_source_tooptip->setObjectName("TooptipLabel");
    label_create_time_tooptip->setObjectName("TooptipLabel");

    label_name_tooptip->setObjectName("TooptipLabel");
    label_lyric_tooptip->setObjectName("TooptipLabel");
    label_type_tooptip->setObjectName("TooptipLabel");
    label_resolution_tooptip->setObjectName("TooptipLabel");
    label_header_tooptip->setObjectName("TooptipLabel");
    label_words_tooptip->setObjectName("TooptipLabel");
    label_prelude_tooptip->setObjectName("TooptipLabel");
    label_rthym_tooptip->setObjectName("TooptipLabel");

    label_addSinger_tooptip->setObjectName("TooptipLabel");
    label_match_tooptip->setObjectName("TooptipLabel");
    label_enabled_tooptip->setObjectName("TooptipLabel");
    label_track_tooptip->setObjectName("TooptipLabel");
    label_quality_tooptip->setObjectName("TooptipLabel");
    label_effect_tooptip->setObjectName("TooptipLabel");
    label_pitch_tooptip->setObjectName("TooptipLabel");

//    label_attribute_tooptip->setObjectName("TooptipLabel");
}

bool SongInfoWidget::isEmpty()
{
    if ( lineEdit_serial_id->text().isEmpty()
         || lineEdit_upload_video->text().isEmpty()
         || lineEdit_pinyin->text().isEmpty()
         || lineEdit_head->text().isEmpty()
         || lineEdit_create_time->text().isEmpty()
         || lineEdit_name->text().isEmpty()
         || lineEdit_lyric->text().isEmpty()
         || lineEdit_header->text().isEmpty()
         || lineEdit_words->text().isEmpty()
         || lineEdit_prelude->text().isEmpty()
         || lineEdit_addSinger->text().isEmpty()
         )
        return true;

    if(comboBox_language->currentText().isEmpty()
       || comboBox_version->currentText().isEmpty()
       || comboBox_source->currentText().isEmpty()
       || comboBox_type->currentText().isEmpty()
       || comboBox_resolution->currentText().isEmpty()
       || comboBox_rthym->currentText().isEmpty()
       || comboBox_match->currentText().isEmpty()
       || comboBox_enabled->currentText().isEmpty()
       || comboBox_original_track->currentText().isEmpty()
       || comboBox_sound_track->currentText().isEmpty()
       || comboBox_quality->currentText().isEmpty()
       || comboBox_effect->currentText().isEmpty()
       || comboBox_pitch->currentText().isEmpty()
       )
       return true;

    return false;
}

void SongInfoWidget::getMediaValue(Media &_media)
{
    QString tempValue;
    _media.serial_id = lineEdit_serial_id->text();
    _media.path = lineEdit_upload_video->text();
    _media.pinyin = lineEdit_pinyin->text();
    _media.head = lineEdit_head->text();
    _media.create_time = lineEdit_create_time->text();

    _media.name = lineEdit_name->text();
    _media.lyric = lineEdit_lyric->text();
    _media.header = lineEdit_header->text();
    _media.words = lineEdit_words->text();
    _media.prelude = lineEdit_prelude->text();

    _media.singer = lineEdit_addSinger->text();
    _media.info = lineEdit_info->text();



    _media.language = QString::number(language.key(comboBox_language->currentText()));
    _media.version = QString::number(version.key(comboBox_version->currentText()));
    _media.source = QString::number(source.key(comboBox_source->currentText()));

    _media.type = QString::number(type.key(comboBox_type->currentText()));
    _media.resolution = QString::number(resolution.key(comboBox_resolution->currentText()));
    _media.rhythm = QString::number(rthym.key(comboBox_rthym->currentText()));

    _media.match = QString::number(match.key(comboBox_match->currentText()));
    _media.enabled = QString::number(enabled.key(comboBox_enabled->currentText()));
    _media.original_track = QString::number(track.key(comboBox_original_track->currentText()));
    _media.sound_track = QString::number(track.key(comboBox_sound_track->currentText()));
    _media.quality = QString::number(quality.key(comboBox_quality->currentText()));
    _media.effect = QString::number(effect.key(comboBox_effect->currentText()));
    _media.pitch = QString::number(pitch.key(comboBox_pitch->currentText()));

    _media.artist_sid_1 = media.artist_sid_1;
    if(actor.size() >= 1)
        _media.artist_sid_2 = media.artist_sid_2;
    else
        _media.artist_sid_2 = "";

    if(lineEdit_info->text().isEmpty())
        _media.info  = "";
}

void SongInfoWidget::setMediaValue(const Media &_media)
{
    media = _media;
    QString temp;

    lineEdit_serial_id->setText(_media.serial_id);
    lineEdit_upload_video->setText(_media.path);
    temp = _media.language.isEmpty()? "": language.value(_media.language.toInt());
    comboBox_language->insertItem(0, temp);
    temp = _media.version.isEmpty()? "" : temp = version.value(_media.version.toInt());
    comboBox_version->insertItem(0, temp);
    lineEdit_pinyin->setText(_media.pinyin);
    lineEdit_head->setText(_media.head);
    temp = _media.source.isEmpty()? QString(""): source.value(_media.source.toInt());
    comboBox_source->insertItem(0, temp);
    lineEdit_create_time->setText(_media.create_time);

    lineEdit_name->setText(_media.name);
    lineEdit_lyric->setText(_media.lyric);
    temp = _media.type.isEmpty()? "": type.value(_media.type.toInt());
    comboBox_type->insertItem(0, temp);
    temp = _media.resolution.isEmpty()? "": resolution.value(_media.resolution.toInt());
    comboBox_resolution->insertItem(0, temp);
    lineEdit_header->setText(_media.header);
    lineEdit_words->setText(_media.words);
    lineEdit_prelude->setText(_media.prelude);
    temp = _media.rhythm.isEmpty()? "": rthym.value(_media.rhythm.toInt());
    comboBox_rthym->insertItem(0, temp);

    lineEdit_addSinger->setText(_media.singer);
    temp = _media.match.isEmpty()? "": match.value(_media.match.toInt());
    comboBox_match->insertItem(0, temp);
    temp = _media.enabled.isEmpty()? "": enabled.value(_media.enabled.toInt());
    comboBox_enabled->insertItem(0, temp);
    comboBox_original_track->insertItem(0, _media.original_track);
    comboBox_sound_track->insertItem(0, _media.sound_track);
    temp = _media.quality.isEmpty()? "": quality.value(_media.quality.toInt());
    comboBox_quality->insertItem(0, temp);
    temp = _media.effect.isEmpty()? "": effect.value(_media.effect.toInt());
    comboBox_effect->insertItem(0, temp);
    lineEdit_info->setText(_media.info);
    temp = _media.pitch.isEmpty()? "": pitch.value(_media.pitch.toInt());
    comboBox_pitch->insertItem(0, temp);

    //    for (int i=0; i<_media.musicTag.size(); i++)
}

void SongInfoWidget::set_comboBox_Language(QMap<int, QString> &lan)
{
    QStringList ll(lan.values());
    language = lan;
    comboBox_language->clear();
    comboBox_language->addItems(ll);
}

void SongInfoWidget::set_comboBox_type(QMap<int, QString> &typ)
{
    QStringList tt(typ.values());
    type = typ;
    comboBox_type->clear();
    comboBox_type->addItems(tt);
}

void SongInfoWidget::set_comboBox_version(QMap<int, QString>&ver)
{
    QStringList vv(ver.values());
    version = ver ;
    comboBox_version->clear();
    comboBox_version->addItems(vv);
}

void SongInfoWidget::set_comboBox_effect(QMap<int, QString> &eff)
{
    QStringList ee(eff.values());
    effect = eff;
    comboBox_effect->clear();
    comboBox_effect->addItems(ee);
}

void SongInfoWidget::set_comboBox_resolution(QMap<int, QString> &res)
{
    QStringList rr(res.values());
    resolution = res;
    comboBox_resolution->clear();
    comboBox_resolution->addItems(rr);
}

void SongInfoWidget::set_comboBox_quality(QMap<int, QString> &qua)
{
    QStringList qq(qua.values());
    quality = qua;
    comboBox_quality->clear();
    comboBox_quality->addItems(qq);
}

void SongInfoWidget::set_comboBox_source(QMap<int, QString> &sou)
{
    QStringList ss(sou.values());
    source = sou;
    comboBox_source->clear();
    comboBox_source->addItems(ss);
}

void SongInfoWidget::set_comboBox_rthym(QMap<int, QString> &rth)
{
    QStringList aa(rth.values());
    rthym = rth;
    comboBox_rthym->clear();
    comboBox_rthym->addItems(aa);
}

void SongInfoWidget::set_comboBox_pitch(QMap<int, QString> &pit)
{
    QStringList pp(pit.values());
    pitch = pit;
    comboBox_pitch->clear();
    comboBox_pitch->addItems(pp);
}

void SongInfoWidget::set_comboBox_track()
{
    QStringList list;
    list << "0" << "1";

    comboBox_original_track->clear();
    comboBox_sound_track->clear();
    comboBox_original_track->addItems(list);
    comboBox_sound_track->addItems(list);
}

void SongInfoWidget::set_comboBox_Remain()
{
    QStringList matchList, enabledList, trackList;

    matchList = QStringList(match.values());
    enabledList = QStringList(enabled.values());
    trackList = QStringList(track.values());

    comboBox_match->clear();
    comboBox_enabled->clear();
    comboBox_sound_track->clear();
    comboBox_original_track->clear();

    comboBox_match->addItems(matchList);
    comboBox_enabled->addItems(enabledList);
    comboBox_original_track->addItems(trackList);
    comboBox_sound_track->addItems(trackList);
}


void SongInfoWidget::PushButton_question_pressed()
{
    label = new QLabel(widgetRight);
    label->setFixedWidth(250);
    label->setObjectName("HelpLabel");
    QString str = QString(" 打开视频时为原唱，原唱填1，伴唱填0\n 打开视频时为伴唱，原唱填0，伴唱填1");
    label->setText(str);
    QRect rect = comboBox_quality->geometry();
    label->setGeometry(rect.x(), rect.y()-8, 250, rect.height()+8);
    label->show();
}

void SongInfoWidget::PushButton_question_released()
{
    label->deleteLater();
}

void SongInfoWidget::getCalendarDate(bool checked)
{
    if(checked){
        calendar->setHidden(false);
        calendar->setFocus();
    }else{
        calendar->setHidden(true);
    }
}

void SongInfoWidget::setDateTime()
{
    QString date = calendar->selectedDate().toString("yyyy-MM-dd");
    lineEdit_create_time->setText(date);
}

void SongInfoWidget::addSinger()
{
    SingerAddModifyDialog *dialog = new SingerAddModifyDialog();

    connect(dialog, &SingerAddModifyDialog::update_view, this, &SongInfoWidget::setAddSinger);
    dialog->exec();
}

void SongInfoWidget::setAddSinger(QList<Actor> _actor)
{
    actor = _actor;

    if(actor.size() >= 1){

        if(!media.artist_sid_1.isEmpty())
        {

            QString singer = lineEdit_addSinger->text();
            singer.append("_");
            singer.append(actor.at(0).name);

            media.artist_sid_2 = actor.at(0).sid;
            lineEdit_addSinger->setText(singer);
        }
        else
        {
            media.artist_sid_1 = actor.at(0).sid;
            media.artist_sid_2 = "";
            if(actor.size() >= 2)
            {
                media.artist_sid_2 = actor.at(1).sid;
                QString value;
                value.append(actor.at(0).name);
                value.append("_");
                value.append(actor.at(1).name);

                lineEdit_addSinger->setText(value);
            }
            else
            {
                lineEdit_addSinger->setText(actor.at(0).name);
            }

        }
    }
}

void SongInfoWidget::uploadVideo()
{
    QString fileFormat("视频文件(*.mp4)");
    QString document = QProcessEnvironment::systemEnvironment().value("USERPROFILE")+"\\Desktop";
    QString pathStr = QFileDialog::getOpenFileName(this,
                                                tr("上传视频"),
                                                document,
                                                fileFormat
                                                );
    if(pathStr.isEmpty())
        return;

    lineEdit_upload_video->setText(pathStr);
}

void SongInfoWidget::uploadLyric()
{
    QString fileFormat("歌词文件(*.lrc)");
    QString document = QProcessEnvironment::systemEnvironment().value("USERPROFILE")+"\\Desktop";
    QString pathStr = QFileDialog::getOpenFileName(this,
                                                tr("上传歌词"),
                                                document,
                                                fileFormat
                                                );
    if(pathStr.isEmpty())
        return;

    lineEdit_lyric->setText(pathStr);
}

QString SongInfoWidget::uploadV(const QString path)
{
    CurlUpload *curlUpload = new CurlUpload();
    QString retPath =  curlUpload->uploadMediaVideo(path);

    if(!retPath.isEmpty())
        lineEdit_upload_video->setText(retPath);

    delete curlUpload;
    return retPath;
}

QString SongInfoWidget::uploadL(const QString path)
{
    CurlUpload *curlUpload = new CurlUpload();
    QString retPath =  curlUpload->uploadMedialyric(path);

    if(!retPath.isEmpty())
        lineEdit_lyric->setText(retPath);

    QStringList list = retPath.split("/");
    delete curlUpload;
    return list.last();
}
