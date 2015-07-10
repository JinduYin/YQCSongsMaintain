#include "singerinfowdiget.h"
#include "typeindexvalue.h"
#include "curlupload.h"
#include <QFile>
#include <QLabel>
#include <QPainter>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QFileDialog>
#include <QProcessEnvironment>
#include <QHBoxLayout>
#include <QVBoxLayout>
SingerInfoWdiget::SingerInfoWdiget(QWidget *parent)
    : QWidget(parent)
{
    initWidget();
    setWidgetSize();
    readAndSetStyleSheet();
    initWidgetValue();

    isRequired();

    enabled.insert(1, "启用");
    enabled.insert(0, "禁用");

    stars.insert(1,"5.0");
    stars.insert(2,"4.5");
    stars.insert(3,"4.0");
    stars.insert(4,"3.5");
    stars.insert(5,"3.0");
    stars.insert(6,"2.5");
    stars.insert(7,"2.0");
    stars.insert(8,"1.5");
    stars.insert(9,"1.0");
    stars.insert(10,"0.5");
    stars.insert(11,"0.0");

    label_show_image->setScaledContents(true); //图片随label调整大小
    label_show_image->setAlignment(Qt::AlignCenter);

    connect(pushButton_upload, &QPushButton::clicked, this, &SingerInfoWdiget::uploadImage);
    connect(pushButton_upload_online, &QPushButton::clicked, this, &SingerInfoWdiget::uploadImageOnline);
    connect(pushButton_preview_online, &QPushButton::clicked, this, &SingerInfoWdiget::previewOnline);

}

SingerInfoWdiget::~SingerInfoWdiget()
{

}

void SingerInfoWdiget::readAndSetStyleSheet()
{
    QFile qss(":/qss/songinfo.qss");
    qss.open(QFile::ReadOnly);
    this->setStyleSheet(qss.readAll());
    qss.close();

    this->setObjectName("Widget");

    label_count->setObjectName("SingerInfoLabel");
    label_info->setObjectName("SingerInfoLabel");

    lineEdit_count->setObjectName("LineEdit");
    lineEdit_head->setObjectName("LineEdit");
    lineEdit_header->setObjectName("LineEdit");
    lineEdit_image->setObjectName("LineEdit");
    lineEdit_image_online->setObjectName("LineEdit");
    lineEdit_info->setObjectName("LineEdit");
    lineEdit_info_online->setObjectName("LineEdit");
    lineEdit_name->setObjectName("LineEdit");
    lineEdit_pinyin->setObjectName("LineEdit");
    lineEdit_serial_id->setObjectName("LineEdit");
    lineEdit_words->setObjectName("LineEdit");

    comboBox_enabled->setObjectName("Combobox");
    comboBox_nation->setObjectName("Combobox");
    comboBox_sex->setObjectName("Combobox");
    comboBox_stars->setObjectName("Combobox");

    pushButton_preview_online->setObjectName("Button");
    pushButton_upload->setObjectName("Button");
    pushButton_upload_online->setObjectName("Button");   
}

void SingerInfoWdiget::initWidget()
{
    widgetLeft = new QWidget(this);
    widgetCenter = new QWidget(this);
    widgetRight = new QWidget(this);
    widgetBottom = new QWidget(this);
    widgetBottom_online = new QWidget(this);

    label_serial_id = new QLabel(widgetLeft);
    label_sex = new QLabel(widgetLeft);
    label_stars = new QLabel(widgetLeft);
    label_pinyin = new QLabel(widgetLeft);
    label_head = new QLabel(widgetLeft);    

    label_name = new QLabel(widgetCenter);
    label_nation = new QLabel(widgetCenter);
    label_enabled = new QLabel(widgetCenter);
    label_header = new QLabel(widgetCenter);
    label_words = new QLabel(widgetCenter);

    label_image = new QLabel(widgetRight);
    label_show_image = new QLabel(widgetRight);

    label_count = new QLabel(this);
    label_info = new QLabel(this);
    label_info_online = new QLabel(this);

    ///星号提示
    label_serial_id_tooptip = new QLabel(widgetLeft);
    label_sex_tooptip = new QLabel(widgetLeft);
    label_stars_tooptip = new QLabel(widgetLeft);
    label_pinyin_tooptip = new QLabel(widgetLeft);
    label_head_tooptip = new QLabel(widgetLeft);
    label_count_tooptip = new QLabel(this);

    label_name_tooptip = new QLabel(widgetCenter);
    label_nation_tooptip = new QLabel(widgetCenter);
    label_enabled_tooptip = new QLabel(widgetCenter);
    label_header_tooptip = new QLabel(widgetCenter);
    label_words_tooptip = new QLabel(widgetCenter);
    label_info_tooptip = new QLabel(this);
    label_info_online_tooptip = new QLabel(this);
    label_image_tooptip = new QLabel(widgetRight);   

    lineEdit_serial_id = new QLineEdit(widgetLeft);
    lineEdit_pinyin = new QLineEdit(widgetLeft);
    lineEdit_head = new QLineEdit(widgetLeft);

    lineEdit_name = new QLineEdit(widgetCenter);
    lineEdit_header = new QLineEdit(widgetCenter);
    lineEdit_words = new QLineEdit(widgetCenter);

    lineEdit_count = new QLineEdit(this);
    lineEdit_info = new QLineEdit(this);
    lineEdit_image = new QLineEdit(widgetBottom);

    lineEdit_info_online = new QLineEdit(widgetBottom_online);
    lineEdit_image_online = new QLineEdit(widgetBottom_online);

    pushButton_upload = new QPushButton(widgetBottom);
    pushButton_upload_online = new QPushButton(widgetBottom_online);
    pushButton_preview_online = new QPushButton(widgetBottom_online);

    comboBox_sex = new QComboBox(widgetLeft);
    comboBox_stars = new QComboBox(widgetLeft);

    comboBox_nation = new QComboBox(widgetCenter);
    comboBox_enabled = new QComboBox(widgetCenter);

    serial_id_layout = new QHBoxLayout();
    sex_layout = new QHBoxLayout();
    stars_layout = new QHBoxLayout();
    pinyin_layout = new QHBoxLayout();
    head_layout = new QHBoxLayout();
    left_layout = new QVBoxLayout();

    serial_id_layout->addWidget(label_serial_id_tooptip);
    serial_id_layout->addWidget(label_serial_id);
    serial_id_layout->addWidget(lineEdit_serial_id);
    serial_id_layout->setContentsMargins(0, 0, 0, 0);
    serial_id_layout->setSpacing(0);

    sex_layout->addWidget(label_sex_tooptip);
    sex_layout->addWidget(label_sex);
    sex_layout->addWidget(comboBox_sex);
    sex_layout->setContentsMargins(0, 0, 0, 0);
    sex_layout->setSpacing(0);

    stars_layout->addWidget(label_stars_tooptip);
    stars_layout->addWidget(label_stars);
    stars_layout->addWidget(comboBox_stars);
    stars_layout->setContentsMargins(0, 0, 0, 0);
    stars_layout->setSpacing(0);

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

    left_layout->addLayout(serial_id_layout);
    left_layout->addLayout(sex_layout);
    left_layout->addLayout(stars_layout);
    left_layout->addLayout(pinyin_layout);
    left_layout->addLayout(head_layout);
    left_layout->setContentsMargins(0, 0, 0, 0);
    left_layout->setSpacing(10);

    name_layout = new QHBoxLayout();
    nation_layout = new QHBoxLayout();
    enabled_layout = new QHBoxLayout();
    header_layout = new QHBoxLayout();
    words_layout = new QHBoxLayout();
    center_layout = new QVBoxLayout();

    name_layout->addWidget(label_name_tooptip);
    name_layout->addWidget(label_name);
    name_layout->addWidget(lineEdit_name);
    name_layout->setContentsMargins(0, 0, 0, 0);
    name_layout->setSpacing(0);

    nation_layout->addWidget(label_nation_tooptip);
    nation_layout->addWidget(label_nation);
    nation_layout->addWidget(comboBox_nation);
    nation_layout->setContentsMargins(0, 0, 0, 0);
    nation_layout->setSpacing(0);

    enabled_layout->addWidget(label_enabled_tooptip);
    enabled_layout->addWidget(label_enabled);
    enabled_layout->addWidget(comboBox_enabled);
    enabled_layout->setContentsMargins(0, 0, 0, 0);
    enabled_layout->setSpacing(0);

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

    center_layout->addLayout(name_layout);
    center_layout->addLayout(nation_layout);
    center_layout->addLayout(enabled_layout);
    center_layout->addLayout(header_layout);
    center_layout->addLayout(words_layout);
    center_layout->setContentsMargins(0, 0, 0, 0);
    center_layout->setSpacing(10);

    info_layout = new QHBoxLayout();
    info_online_layout = new QHBoxLayout();
    count_layout = new QHBoxLayout();

    info_layout->addWidget(label_info_tooptip);
    info_layout->addWidget(label_info);
    info_layout->addWidget(lineEdit_info);
    info_layout->setContentsMargins(8, 0, 0, 0);
    info_layout->setSpacing(0);

    count_layout->addWidget(label_count_tooptip);
    count_layout->addWidget(label_count);
    count_layout->addWidget(lineEdit_count);
    count_layout->setContentsMargins(0, 0, 0, 0);
    count_layout->setSpacing(0);

    info_online_layout->addWidget(label_info_online_tooptip);
    info_online_layout->addWidget(label_info_online);
    info_online_layout->addWidget(lineEdit_info_online);
    info_online_layout->setContentsMargins(0, 0, 0, 0);
    info_online_layout->setSpacing(0);

    upload_layout = new QHBoxLayout();
    bottom_layout = new QHBoxLayout();
    upload_online_layout = new QHBoxLayout();
    bottom_online_layout = new QHBoxLayout();

    upload_layout->addWidget(lineEdit_image);
    upload_layout->addWidget(pushButton_upload);
    upload_layout->addStretch();
    upload_layout->setContentsMargins(0, 0, 0, 0);
    upload_layout->setSpacing(10);

    bottom_layout->addLayout(count_layout);
    bottom_layout->addLayout(info_layout);
    bottom_layout->addLayout(upload_layout);
    bottom_layout->addStretch();
    bottom_layout->setContentsMargins(0, 0, 0, 0);
    bottom_layout->setSpacing(42);
    widgetBottom->setLayout(bottom_layout);

    upload_online_layout->addWidget(lineEdit_image_online);
    upload_online_layout->addWidget(pushButton_preview_online);
    upload_online_layout->addWidget(pushButton_upload_online);   
    upload_online_layout->setContentsMargins(0, 0, 0, 0);
    upload_online_layout->setSpacing(8);

    bottom_online_layout->addLayout(info_online_layout);
    bottom_online_layout->addLayout(upload_online_layout);
    bottom_online_layout->addStretch();
    bottom_online_layout->setContentsMargins(0, 0, 0, 0);
    bottom_online_layout->setSpacing(42);
    widgetBottom_online->setLayout(bottom_online_layout);

    image_tooltip_layout = new QHBoxLayout();
    right_layout = new QVBoxLayout();
    image_tooltip_layout->addWidget(label_image_tooptip);
    image_tooltip_layout->addWidget(label_image, 0, Qt::AlignLeft);
    image_tooltip_layout->setContentsMargins(0, 0, 0, 0);
    image_tooltip_layout->setSpacing(0);

    right_layout->addLayout(image_tooltip_layout);
    right_layout->addWidget(label_show_image, 0, Qt::AlignLeft);
    right_layout->addStretch();
    right_layout->setContentsMargins(0, 0, 0, 0);
    right_layout->setSpacing(10);


    singerInfo_layout = new QHBoxLayout();
    singerInfo_layout->addLayout(left_layout);
    singerInfo_layout->addLayout(center_layout);
    singerInfo_layout->addLayout(right_layout);
    singerInfo_layout->addStretch();
    singerInfo_layout->setContentsMargins(0, 0, 0, 0);
    singerInfo_layout->setSpacing(42);

    vLayout = new QVBoxLayout();
    vLayout->addLayout(singerInfo_layout);
    vLayout->addWidget(widgetBottom);
    vLayout->addWidget(widgetBottom_online);
    vLayout->setContentsMargins(0, 0, 0, 0);
    vLayout->setSpacing(10);

    this->setLayout(vLayout);
}

void SingerInfoWdiget::initWidgetValue()
{
    label_serial_id->setText("SERIAL_ID");
    label_sex->setText("歌星性别");
    label_stars->setText("歌星评分");
    label_pinyin->setText("名称全拼");
    label_head->setText("名称第一个\n字首字母");

    label_name->setText("歌星名称");
    label_nation->setText("歌星区域");
    label_enabled->setText("是否启用");
    label_header->setText("名称首字母");
    label_words->setText("名称字数");
    label_image->setText("歌星头像");

    label_count->setText("歌曲数量");
    label_info->setText("备    注");
    label_info_online->setText("备    注");

    pushButton_upload->setText("浏览");
    pushButton_preview_online->setText("浏览");
    pushButton_upload_online->setText("上传");
}

void SingerInfoWdiget::setWidgetSize()
{
    label_serial_id->setFixedWidth(80);
    label_sex->setFixedWidth(80);
    label_stars->setFixedWidth(80);
    label_pinyin->setFixedWidth(80);
    label_head->setFixedWidth(80);

    label_name->setFixedWidth(80);
    label_nation->setFixedWidth(80);
    label_enabled->setFixedWidth(80);
    label_header->setFixedWidth(80);
    label_words->setFixedWidth(80);

    label_image->setFixedWidth(80);
    label_show_image->setFixedWidth(164);
    label_show_image->setFixedHeight(164);

    label_count->setFixedWidth(80);
    label_info->setFixedWidth(80);
    label_info_online->setFixedWidth(80);    
    label_count_tooptip->setFixedWidth(8);
    label_info_tooptip->setFixedWidth(8);
    label_info_online_tooptip->setFixedWidth(8);

    label_serial_id_tooptip->setFixedWidth(8);
    label_sex_tooptip->setFixedWidth(8);
    label_stars_tooptip->setFixedWidth(8);
    label_pinyin_tooptip->setFixedWidth(8);
    label_head_tooptip->setFixedWidth(8);

    label_name_tooptip->setFixedWidth(8);
    label_nation_tooptip->setFixedWidth(8);
    label_enabled_tooptip->setFixedWidth(8);
    label_header_tooptip->setFixedWidth(8);
    label_words_tooptip->setFixedWidth(8);

    label_image_tooptip->setFixedWidth(8);


    lineEdit_serial_id->setFixedWidth(250);
    lineEdit_serial_id->setFixedHeight(36);
    lineEdit_pinyin->setFixedWidth(250);
    lineEdit_pinyin->setFixedHeight(36);
    lineEdit_head->setFixedWidth(250);
    lineEdit_head->setFixedHeight(36);

    lineEdit_name->setFixedWidth(250);
    lineEdit_name->setFixedHeight(36);
    lineEdit_header->setFixedWidth(250);
    lineEdit_header->setFixedHeight(36);
    lineEdit_words->setFixedWidth(250);
    lineEdit_words->setFixedHeight(36);

    lineEdit_count->setFixedWidth(250);
    lineEdit_count->setFixedHeight(36);
    lineEdit_info->setFixedWidth(250);
    lineEdit_info->setFixedHeight(36);
    lineEdit_image->setFixedWidth(250);
    lineEdit_image->setFixedHeight(36);

    lineEdit_info_online->setFixedWidth(620+9);
    lineEdit_info_online->setFixedHeight(36);
    lineEdit_image_online->setFixedWidth(192);
    lineEdit_image_online->setFixedHeight(36);


    pushButton_upload->setFixedWidth(60);
    pushButton_upload->setFixedHeight(36);
    pushButton_upload_online->setFixedWidth(60);
    pushButton_upload_online->setFixedHeight(36);
    pushButton_preview_online->setFixedWidth(60);
    pushButton_preview_online->setFixedHeight(36);

    comboBox_sex->setFixedWidth(250);
    comboBox_sex->setFixedHeight(36);
    comboBox_stars->setFixedWidth(250);
    comboBox_stars->setFixedHeight(36);

    comboBox_nation->setFixedWidth(250);
    comboBox_nation->setFixedHeight(36);
    comboBox_enabled->setFixedWidth(250);
    comboBox_enabled->setFixedHeight(36);
}

void SingerInfoWdiget::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void SingerInfoWdiget::isSingerOnline()
{
    widgetBottom->setHidden(true);
    widgetBottom_online->setHidden(false);
}

void SingerInfoWdiget::isPreviewAndModify()
{
    widgetBottom->setHidden(false);
    widgetBottom_online->setHidden(true);
}

void SingerInfoWdiget::isRequired()
{
    label_serial_id_tooptip->setObjectName("TooptipLabel");
    label_sex_tooptip->setObjectName("TooptipLabel");
    label_stars_tooptip->setObjectName("TooptipLabel");
    label_pinyin_tooptip->setObjectName("TooptipLabel");
    label_head_tooptip->setObjectName("TooptipLabel");

    label_name_tooptip->setObjectName("TooptipLabel");
    label_nation_tooptip->setObjectName("TooptipLabel");
    label_enabled_tooptip->setObjectName("TooptipLabel");
    label_header_tooptip->setObjectName("TooptipLabel");
    label_words_tooptip->setObjectName("TooptipLabel");
    label_image_tooptip->setObjectName("TooptipLabel");
}

bool SingerInfoWdiget::isEmpty()
{
    if ( lineEdit_serial_id->text().isEmpty()
         || lineEdit_pinyin->text().isEmpty()
         || lineEdit_head->text().isEmpty()
         || lineEdit_name->text().isEmpty()
         || lineEdit_header->text().isEmpty()
         || lineEdit_words->text().isEmpty()
         )
        return true;

    if(comboBox_sex->currentText().isEmpty()
       || comboBox_stars->currentText().isEmpty()
       || comboBox_nation->currentText().isEmpty()
       || comboBox_enabled->currentText().isEmpty()

       )
       return true;

    return false;
}

void SingerInfoWdiget::set_disabled()
{
    lineEdit_serial_id->setEnabled(false);
    lineEdit_pinyin->setEnabled(false);
    lineEdit_head->setEnabled(false);
    lineEdit_count->setEnabled(false);

    lineEdit_name->setEnabled(false); //lineEdit_name->setDisabled();
    lineEdit_header->setEnabled(false);
    lineEdit_words->setEnabled(false);
    lineEdit_info->setEnabled(false);


    comboBox_sex->setEnabled(false);
    comboBox_stars->setEnabled(false);
    comboBox_nation->setEnabled(false);
    comboBox_enabled->setEnabled(false);

    pushButton_upload->setHidden(true);
}

void SingerInfoWdiget::set_enabled()
{
    lineEdit_serial_id->setEnabled(true);
    lineEdit_pinyin->setEnabled(true);
    lineEdit_head->setEnabled(true);
    lineEdit_count->setEnabled(true);

    lineEdit_name->setEnabled(true); //lineEdit_name->setDisabled();
    lineEdit_header->setEnabled(true);
    lineEdit_words->setEnabled(true);
    lineEdit_info->setEnabled(true);


    comboBox_sex->setEnabled(true);
    comboBox_stars->setEnabled(true);
    comboBox_nation->setEnabled(true);
    comboBox_enabled->setEnabled(true);

    pushButton_upload->setHidden(false);
}

void SingerInfoWdiget::getActorValue(Actor &_actor)
{
    _actor.serial_id = lineEdit_serial_id->text();
    _actor.pinyin = lineEdit_pinyin->text();
    _actor.head = lineEdit_head->text();
    _actor.count = lineEdit_count->text();

    _actor.name = lineEdit_name->text();
    _actor.header = lineEdit_header->text();
    _actor.words = lineEdit_words->text();
    _actor.info = lineEdit_info->text();

    _actor.sex = QString::number(comboBox_sex->currentIndex());
    _actor.nation = QString::number(comboBox_nation->currentIndex());
    _actor.enabled = QString::number(comboBox_enabled->currentIndex());

    _actor.stars = QString::number(comboBox_stars->currentIndex());
    //    _actor.stars = comboBox_stars->currentText();
}

void SingerInfoWdiget::getActorOnlineValue(Actor &_actor)
{
    _actor.serial_id = lineEdit_serial_id->text();
    _actor.pinyin = lineEdit_pinyin->text();
    _actor.head = lineEdit_head->text();
    _actor.count = lineEdit_count->text();

    _actor.name = lineEdit_name->text();
    _actor.header = lineEdit_header->text();
    _actor.words = lineEdit_words->text();
    _actor.info = lineEdit_info->text();

    _actor.sex = QString::number(sex.key(comboBox_sex->currentText()));
    _actor.nation = QString::number(nation.key(comboBox_nation->currentText()));
    _actor.enabled = QString::number(enabled.key(comboBox_enabled->currentText()));

    _actor.stars = comboBox_stars->currentText();
    _actor.image = lineEdit_image_online->text();
}

void SingerInfoWdiget::setActorValue(const Actor &_actor)
{
    actor = _actor;
    TypeIndexValue value;
    lineEdit_serial_id->setText(_actor.serial_id);
    comboBox_sex->insertItem(0, value.sex.value(_actor.sex.toInt()));
    comboBox_stars->insertItem(0, _actor.stars);
    lineEdit_pinyin->setText(_actor.pinyin);
    lineEdit_head->setText(_actor.head);
    lineEdit_count->setText(_actor.count);

    lineEdit_name->setText(_actor.name);
    comboBox_nation->insertItem(0, value.nation.value(_actor.nation.toInt()));
    comboBox_enabled->insertItem(0, value.enabled.value(_actor.enabled.toInt()));
    lineEdit_header->setText(_actor.header);
    lineEdit_words->setText(_actor.words);
    lineEdit_info->setText(_actor.info);

    QFile file(_actor.image);
    if(!file.exists()){
        return;
    }

    if(!_actor.image.isEmpty()){

        QImage image;
        image.load(_actor.image);
        label_show_image->setPixmap(QPixmap::fromImage(image));
        QStringList strList = _actor.image.split("/");
        lineEdit_image->setText(strList.last());
        pushButton_upload->setText("修改");
    }
}

QString SingerInfoWdiget::getImagePath()
{
    return lineEdit_image->text();
}

void SingerInfoWdiget::set_comboBox_sex(QMap<int, QString> &_sex)
{
    QStringList ss(_sex.values());
    sex = _sex;
    comboBox_sex->clear();
    comboBox_sex->addItems(ss);
}

void SingerInfoWdiget::set_comboBox_nation(QMap<int, QString> &_nat)
{
    QStringList nn(_nat.values());
    nation = _nat;
    comboBox_nation->clear();
    comboBox_nation->addItems(nn);
}

void SingerInfoWdiget::set_comboBox_Remain()
{
    QStringList ss(stars.values());
    comboBox_stars->clear();
    comboBox_stars->addItems(ss);

    QStringList ee(enabled.values());
    comboBox_enabled->clear();
    comboBox_enabled->addItems(ee);
}

void SingerInfoWdiget::setImageOnlineRetPath(const QString &path)
{
    lineEdit_image_online->setText(path);
}

void SingerInfoWdiget::uploadImage()
{
    QString fileFormat("图片文件(*.jpg)");
    QString document = QProcessEnvironment::systemEnvironment().value("USERPROFILE")+"\\Desktop";
    QString pathStr = QFileDialog::getOpenFileName(this,
                                                tr("上传头像"),
                                                document,
                                                fileFormat
                                                );
    if(pathStr.isEmpty())
        return;

    QImage image;
    image.load(pathStr);
    label_show_image->setPixmap(QPixmap::fromImage(image));
    lineEdit_image->setText(pathStr);
}

void SingerInfoWdiget::uploadImageOnline()
{
    QString path = lineEdit_image_online->text();
    QString retPath;
    if(!path.isEmpty())
    {
        CurlUpload *curlUpload = new CurlUpload();
        retPath = curlUpload->uploadActorImage(path);
        lineEdit_image_online->setText(retPath);
    }
}

void SingerInfoWdiget::previewOnline()
{
    QString fileFormat("图片文件(*.jpg)");
    QString document = QProcessEnvironment::systemEnvironment().value("USERPROFILE")+"\\Desktop";
    QString pathStr = QFileDialog::getOpenFileName(this,
                                                tr("上传头像"),
                                                document,
                                                fileFormat
                                                );
    if(pathStr.isEmpty())
        return;

    QImage image;
    image.load(pathStr);
    label_show_image->setPixmap(QPixmap::fromImage(image));
    lineEdit_image_online->setText(pathStr);
}
