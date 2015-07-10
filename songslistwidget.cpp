#include "songslistwidget.h"
#include "pagingtableview.h"
#include "mysqlquery.h"
#include "tablemodel.h"
#include "fmaddmodifydialog.h"
#include "songslistaddmodifydialog.h"
#include "enuminfo.h"
#include <QFile>
#include <QLabel>
#include <QPainter>
#include <QLineEdit>
#include <QCheckBox>
#include <QComboBox>
#include <QPushButton>
#include <QDateTime>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QCalendarWidget>
#include <QDebug>
SongsListWidget::SongsListWidget(QWidget *parent, bool _hotnet)
    : QWidget(parent),
      _sql(NULL),
      hotnet(_hotnet)
{
    initWidget();
    readAndSetStyleSheet();
    initWidgetValue();
    setWidgetSize();

    replaceRow = -1;
    _widItem = -1;
    pushButton_filter->setHidden(true);
    label_listType->setHidden(true);
    combobox_listType->setHidden(true);
    tableView_songsList->setMediaListDelegate();

    widgetTypeHidden->setHidden(true);
    connect(pushButton_hidden, &QPushButton::clicked, this, &SongsListWidget::setTypeHidden);
    connect(pushButton_filter, &QPushButton::clicked, this, &SongsListWidget::setFilterHidden);

    connect(pushButton_startCalendar, &QPushButton::clicked, this, &SongsListWidget::setStartCalendarShow);
    connect(pushButton_endCalendar, &QPushButton::clicked, this, &SongsListWidget::setEndCalendarShow);
    connect(calendar_start, &QCalendarWidget::selectionChanged, this, &SongsListWidget::setStartDate);
    connect(calendar_end, &QCalendarWidget::selectionChanged, this, &SongsListWidget::setEndDate);

    connect(tableView_songsList, &PagingTableView::updateView, this, &SongsListWidget::updateViewValue);


    connect(checkBox_time_nolimit, &QCheckBox::stateChanged, this, &SongsListWidget::createTimeStateChanged);
    connect(checkBox_language_nolimit, &QCheckBox::stateChanged, this, &SongsListWidget::languageStateChanged);
    connect(checkBox_type_nolimit, &QCheckBox::stateChanged, this, &SongsListWidget::typeStateChanged);

    connect(pushBUtton_add, &QPushButton::clicked, this, &SongsListWidget::addMusic);
    connect(pushButton_save, &QPushButton::clicked, this, &SongsListWidget::createList);
    connect(tableView_songsList, &PagingTableView::play, this, &SongsListWidget::play);
    connect(tableView_songsList, &PagingTableView::replace, this, &SongsListWidget::replace);

    if(!hotnet){

        connect(tableView_songsList, &PagingTableView::moveUp, this, &SongsListWidget::moveUp);
        connect(tableView_songsList, &PagingTableView::moveDown, this, &SongsListWidget::moveDown);
        connect(tableView_songsList, &PagingTableView::currentRow, this, &SongsListWidget::deleteMusic);
    }else{
        connect(tableView_songsList, &PagingTableView::moveUp, this, &SongsListWidget::moveUpHN);
        connect(tableView_songsList, &PagingTableView::moveDown, this, &SongsListWidget::moveDownHN);
        connect(tableView_songsList, &PagingTableView::currentRow, this, &SongsListWidget::deleteMusicHN);
        connect(combobox_listType, SIGNAL(currentIndexChanged(QString)), this, SLOT(comboboxCurrentChange(QString)));
    }

}

SongsListWidget::~SongsListWidget()
{

}

void SongsListWidget::readAndSetStyleSheet()
{
    QFile qss(":/qss/songquery.qss");
    qss.open(QFile::ReadOnly);
    this->setStyleSheet(qss.readAll());
    qss.close();

    this->setObjectName("Widget");
    widgetTitle->setObjectName("TopWidget");
    widgetCenter->setObjectName("CenterWidget");
    label_title->setObjectName("TitleLabel");
    label_filter->setObjectName("SelectLabel");

    comboBox_num->setObjectName("Combobox");
    combobox_listType->setObjectName("Combobox");

    pushButton_save->setObjectName("Button");
    pushButton_filter->setObjectName("Button");
    pushBUtton_add->setObjectName("Button");
    pushButton_hidden->setObjectName("HiddenButton");
    pushButton_startCalendar->setObjectName("CalendarButton");
    pushButton_endCalendar->setObjectName("CalendarButton");

    lineEdit_endTime->setObjectName("LineEdit");
    lineEdit_startTime->setObjectName("LineEdit");

    label_createTime->setObjectName("Label");
    label_createTime_center->setObjectName("Label");
    label_language->setObjectName("Label");
    label_type->setObjectName("Label");
    label_num->setObjectName("Label");
    label_listType->setObjectName("Label");

    checkBox_time_nolimit->setObjectName("CheckBox");
    checkBox_language_nolimit->setObjectName("CheckBox");
    checkBox_language_chinese->setObjectName("CheckBox");
    checkBox_language_cantonese->setObjectName("CheckBox");
    checkBox_language_hokkien->setObjectName("CheckBox");
    checkBox_language_english->setObjectName("CheckBox");
    checkBox_language_japan->setObjectName("CheckBox");
    checkBox_language_korean->setObjectName("CheckBox");
    checkBox_language_other->setObjectName("CheckBox");

    checkBox_type_nolimit->setObjectName("CheckBox");
    checkBox_type_romance->setObjectName("CheckBox");
    checkBox_type_love->setObjectName("CheckBox");
    checkBox_type_nation->setObjectName("CheckBox");
    checkBox_type_military->setObjectName("CheckBox");
    checkBox_type_hot->setObjectName("CheckBox");
    checkBox_type_child->setObjectName("CheckBox");

    checkBox_type_opera->setObjectName("CheckBox");
    checkBox_type_old->setObjectName("CheckBox");
    checkBox_type_paino->setObjectName("CheckBox");
    checkBox_type_birthday->setObjectName("CheckBox");
    checkBox_type_cvoice->setObjectName("CheckBox");
    checkBox_type_cstrong->setObjectName("CheckBox");
    checkBox_type_cstrong->setObjectName("CheckBox");

    checkBox_type_imsing->setObjectName("CheckBox");
    checkBox_type_cdream->setObjectName("CheckBox");
    checkBox_type_cgsong->setObjectName("CheckBox");
    checkBox_type_starpair->setObjectName("CheckBox");
    checkBox_type_dj->setObjectName("CheckBox");
    checkBox_type_movie->setObjectName("CheckBox");
    checkBox_type_affection->setObjectName("CheckBox");

    checkBox_type_friend->setObjectName("CheckBox");
    checkBox_type_broken->setObjectName("CheckBox");
    checkBox_type_network->setObjectName("CheckBox");
    checkBox_type_ancient->setObjectName("CheckBox");
    checkBox_type_school->setObjectName("CheckBox");
    checkBox_type_motivational->setObjectName("CheckBox");
    checkBox_type_fashion->setObjectName("CheckBox");
}

void SongsListWidget::initWidget()
{
    widgetTitle = new QWidget(this);
    widgetCenter = new QWidget(this);
    widgetTypeHidden = new QWidget(widgetCenter);

    calendar_start = new QCalendarWidget(this);
    calendar_end = new QCalendarWidget(this);

    label_title = new QLabel(widgetTitle);
    label_filter = new QLabel(widgetCenter);
    label_createTime = new QLabel(widgetCenter);
    label_createTime_center = new QLabel(widgetCenter);
    label_language = new QLabel(widgetCenter);
    label_type = new QLabel(widgetCenter);
    label_num = new QLabel(widgetCenter);
    label_num = new QLabel(widgetCenter);
    label_listType = new QLabel(widgetCenter);

    lineEdit_startTime = new QLineEdit(widgetCenter);
    lineEdit_endTime = new QLineEdit(widgetCenter);

    pushButton_filter = new QPushButton(widgetTitle);
    pushBUtton_add = new QPushButton(widgetTitle);
    pushButton_startCalendar = new QPushButton(lineEdit_startTime);
    pushButton_endCalendar = new QPushButton(lineEdit_endTime);
    pushButton_hidden = new QPushButton(widgetCenter);
    pushButton_save = new QPushButton(widgetCenter);
    comboBox_num = new QComboBox(widgetCenter);
    combobox_listType = new QComboBox(widgetCenter);
    pushButton_hidden->setCheckable(true);
    pushButton_hidden->setFixedWidth(14);
    pushButton_hidden->setFixedHeight(14);
    pushButton_filter->setCheckable(true);


    checkBox_time_nolimit = new QCheckBox(widgetCenter);
    checkBox_language_nolimit = new QCheckBox(widgetCenter);
    checkBox_language_chinese = new QCheckBox(widgetCenter);
    checkBox_language_cantonese = new QCheckBox(widgetCenter);
    checkBox_language_hokkien = new QCheckBox(widgetCenter);
    checkBox_language_english = new QCheckBox(widgetCenter);
    checkBox_language_japan = new QCheckBox(widgetCenter);
    checkBox_language_korean = new QCheckBox(widgetCenter);
    checkBox_language_other = new QCheckBox(widgetCenter);

    ///1
    checkBox_type_nolimit = new QCheckBox(widgetCenter);
    checkBox_type_romance = new QCheckBox(widgetCenter);
    checkBox_type_love = new QCheckBox(widgetCenter);
    checkBox_type_nation = new QCheckBox(widgetCenter);
    checkBox_type_military = new QCheckBox(widgetCenter);
    checkBox_type_hot = new QCheckBox(widgetCenter);
    checkBox_type_child = new QCheckBox(widgetCenter);
    ///2
    checkBox_type_opera = new QCheckBox(widgetTypeHidden);
    checkBox_type_old = new QCheckBox(widgetTypeHidden);
    checkBox_type_paino = new QCheckBox(widgetTypeHidden);
    checkBox_type_birthday = new QCheckBox(widgetTypeHidden);
    checkBox_type_cvoice = new QCheckBox(widgetTypeHidden);
    checkBox_type_cstrong = new QCheckBox(widgetTypeHidden);
    checkBox_type_cfsong = new QCheckBox(widgetTypeHidden);
    ///3
    checkBox_type_imsing = new QCheckBox(widgetTypeHidden);
    checkBox_type_cdream = new QCheckBox(widgetTypeHidden);
    checkBox_type_cgsong = new QCheckBox(widgetTypeHidden);
    checkBox_type_starpair = new QCheckBox(widgetTypeHidden);
    checkBox_type_dj = new QCheckBox(widgetTypeHidden);
    checkBox_type_movie = new QCheckBox(widgetTypeHidden);
    checkBox_type_affection = new QCheckBox(widgetTypeHidden);
    ///4
    checkBox_type_friend = new QCheckBox(widgetTypeHidden);
    checkBox_type_broken = new QCheckBox(widgetTypeHidden);
    checkBox_type_network = new QCheckBox(widgetTypeHidden);
    checkBox_type_ancient = new QCheckBox(widgetTypeHidden);
    checkBox_type_school = new QCheckBox(widgetTypeHidden);
    checkBox_type_motivational = new QCheckBox(widgetTypeHidden);
    checkBox_type_fashion = new QCheckBox(widgetTypeHidden);


    filter_add_layout = new QHBoxLayout();
    title_layout = new QHBoxLayout();

    filter_add_layout->addWidget(pushButton_filter);
    filter_add_layout->addWidget(pushBUtton_add);
//    filter_add_layout->addWidget(pushButton_save);
    filter_add_layout->setContentsMargins(0, 0, 0, 0);
    filter_add_layout->setSpacing(20);

    title_layout->addWidget(label_title);
    title_layout->addStretch();
    title_layout->addLayout(filter_add_layout);
    title_layout->setContentsMargins(20, 0, 24, 0);
    title_layout->setSpacing(0);

    widgetTitle->setLayout(title_layout);

    startEndTime_layout = new QHBoxLayout();
    createTime_noLimit_layout = new QHBoxLayout();
    createTime_layout = new QHBoxLayout();

    startEndTime_layout->addWidget(lineEdit_startTime);
    startEndTime_layout->addWidget(label_createTime_center);
    startEndTime_layout->addWidget(lineEdit_endTime);
    startEndTime_layout->addStretch();
    startEndTime_layout->setContentsMargins(0, 0, 0, 0);
    startEndTime_layout->setSpacing(10);

    createTime_noLimit_layout->addWidget(checkBox_time_nolimit);
    createTime_noLimit_layout->addLayout(startEndTime_layout);
    createTime_noLimit_layout->setContentsMargins(0, 0, 0, 0);
    createTime_noLimit_layout->setSpacing(30);

    createTime_layout->addWidget(label_createTime);
    createTime_layout->addLayout(createTime_noLimit_layout);
    createTime_layout->addStretch();
    createTime_layout->setContentsMargins(0, 0, 0, 0);
    createTime_layout->setSpacing(10);

    language_noLimit_layout = new QHBoxLayout();
    language_layout = new QHBoxLayout();

    language_noLimit_layout->addWidget(checkBox_language_nolimit);
    language_noLimit_layout->addWidget(checkBox_language_chinese);
    language_noLimit_layout->addWidget(checkBox_language_cantonese);
    language_noLimit_layout->addWidget(checkBox_language_hokkien);
    language_noLimit_layout->addWidget(checkBox_language_english);
    language_noLimit_layout->addWidget(checkBox_language_japan);
    language_noLimit_layout->addWidget(checkBox_language_korean);
    language_noLimit_layout->addWidget(checkBox_language_other);
    language_noLimit_layout->setContentsMargins(0, 0, 0, 0);
    language_noLimit_layout->setSpacing(30);

    language_layout->addWidget(label_language);
    language_layout->addLayout(language_noLimit_layout);
    language_layout->addStretch();
    language_layout->setContentsMargins(0, 0, 0, 0);
    language_layout->setSpacing(10);

    type_noLimit_layout = new QHBoxLayout();
    type_layout = new QHBoxLayout();
    type_noLimit_layout->addWidget(checkBox_type_nolimit);
    type_noLimit_layout->addWidget(checkBox_type_romance);
    type_noLimit_layout->addWidget(checkBox_type_love);
    type_noLimit_layout->addWidget(checkBox_type_nation);
    type_noLimit_layout->addWidget(checkBox_type_military);
    type_noLimit_layout->addWidget(checkBox_type_hot);
    type_noLimit_layout->addWidget(checkBox_type_child);
    type_noLimit_layout->addWidget(pushButton_hidden);
    type_noLimit_layout->setContentsMargins(0, 0, 0, 0);
    type_noLimit_layout->setSpacing(30);

    type_layout->addWidget(label_type);
    type_layout->addLayout(type_noLimit_layout);
    type_layout->addStretch();
    type_layout->setContentsMargins(0, 0, 0, 0);
    type_layout->setSpacing(10);

    num_layout = new QHBoxLayout();
    num_layout->addWidget(label_num);
    num_layout->addWidget(comboBox_num);
    num_layout->addWidget(pushButton_save);
    num_layout->addStretch();
    num_layout->setContentsMargins(0, 0, 0, 0);
    num_layout->setSpacing(10);

    type_hidden_layout01 = new QHBoxLayout();
    type_hidden_layout02 = new QHBoxLayout();
    type_hidden_layout03 = new QHBoxLayout();

    type_hidden_layout01->addWidget(checkBox_type_opera);
    type_hidden_layout01->addWidget(checkBox_type_old);
    type_hidden_layout01->addWidget(checkBox_type_paino);
    type_hidden_layout01->addWidget(checkBox_type_birthday);
    type_hidden_layout01->addWidget(checkBox_type_cvoice);
    type_hidden_layout01->addWidget(checkBox_type_cstrong);
    type_hidden_layout01->addWidget(checkBox_type_cfsong);
    type_hidden_layout01->addStretch();
    type_hidden_layout01->setContentsMargins(0, 0, 0, 0);
    type_hidden_layout01->setSpacing(30);

    type_hidden_layout02->addWidget(checkBox_type_imsing);
    type_hidden_layout02->addWidget(checkBox_type_cdream);
    type_hidden_layout02->addWidget(checkBox_type_cgsong);
    type_hidden_layout02->addWidget(checkBox_type_starpair);
    type_hidden_layout02->addWidget(checkBox_type_dj);
    type_hidden_layout02->addWidget(checkBox_type_movie);
    type_hidden_layout02->addWidget(checkBox_type_affection);
    type_hidden_layout02->addStretch();
    type_hidden_layout02->setContentsMargins(0, 0, 0, 0);
    type_hidden_layout02->setSpacing(30);

    type_hidden_layout03->addWidget(checkBox_type_friend);
    type_hidden_layout03->addWidget(checkBox_type_broken);
    type_hidden_layout03->addWidget(checkBox_type_network);
    type_hidden_layout03->addWidget(checkBox_type_ancient);
    type_hidden_layout03->addWidget(checkBox_type_school);
    type_hidden_layout03->addWidget(checkBox_type_motivational);
    type_hidden_layout03->addWidget(checkBox_type_fashion);
    type_hidden_layout03->addStretch();
    type_hidden_layout03->setContentsMargins(0, 0, 0, 0);
    type_hidden_layout03->setSpacing(30);

    vHidden_layout = new QVBoxLayout();
    vHidden_layout->addLayout(type_hidden_layout01);
    vHidden_layout->addLayout(type_hidden_layout02);
    vHidden_layout->addLayout(type_hidden_layout03);
    vHidden_layout->setContentsMargins(70+88+30, 0, 0, 0);
    vHidden_layout->setSpacing(10);

//    vHidden_layout = new QGridLayout();

//    vHidden_layout->addWidget(checkBox_type_opera, 0, 0);
//    vHidden_layout->addWidget(checkBox_type_old, 0, 1);
//    vHidden_layout->addWidget(checkBox_type_paino, 0, 2);
//    vHidden_layout->addWidget(checkBox_type_birthday, 0, 3);
//    vHidden_layout->addWidget(checkBox_type_cvoice, 0, 4);
//    vHidden_layout->addWidget(checkBox_type_cstrong, 0, 5);
//    vHidden_layout->addWidget(checkBox_type_cfsong, 0, 6);

//    vHidden_layout->addWidget(checkBox_type_imsing, 1, 0);
//    vHidden_layout->addWidget(checkBox_type_cdream, 1, 1);
//    vHidden_layout->addWidget(checkBox_type_cgsong, 1, 2);
//    vHidden_layout->addWidget(checkBox_type_starpair, 1, 3);
//    vHidden_layout->addWidget(checkBox_type_dj, 1, 4);
//    vHidden_layout->addWidget(checkBox_type_movie, 1, 5);
//    vHidden_layout->addWidget(checkBox_type_affection, 1, 6);

//    vHidden_layout->addWidget(checkBox_type_friend, 2, 0);
//    vHidden_layout->addWidget(checkBox_type_broken, 2, 1);
//    vHidden_layout->addWidget(checkBox_type_network, 2, 2);
//    vHidden_layout->addWidget(checkBox_type_ancient, 2, 3);
//    vHidden_layout->addWidget(checkBox_type_school, 2, 4);
//    vHidden_layout->addWidget(checkBox_type_motivational, 2, 5);
//    vHidden_layout->addWidget(checkBox_type_fashion, 2, 6);

    widgetTypeHidden->setLayout(vHidden_layout);

    info_layout = new QVBoxLayout();
    vCenter_layout = new QVBoxLayout();

    QHBoxLayout *listTypeLayout = new QHBoxLayout();
    listTypeLayout->addWidget(label_listType);
    listTypeLayout->addWidget(combobox_listType);
    listTypeLayout->addStretch();
    listTypeLayout->setContentsMargins(0, 0, 0, 0);
    listTypeLayout->setSpacing(10);

    info_layout->addLayout(listTypeLayout);
    info_layout->addLayout(createTime_layout);
    info_layout->addLayout(language_layout);
    info_layout->addLayout(type_layout);
    info_layout->addWidget(widgetTypeHidden);
    info_layout->addLayout(num_layout);
    info_layout->setContentsMargins(26, 0, 0, 0);
    info_layout->setSpacing(10);

    vCenter_layout->addWidget(label_filter);
    vCenter_layout->addLayout(info_layout);
    vCenter_layout->setContentsMargins(20, 0, 0, 10);
    vCenter_layout->setSpacing(0);

    widgetCenter->setLayout(vCenter_layout);


    tableView_songsList = new PagingTableView(this);
    tableViewLayout = new QVBoxLayout();
    tableViewLayout->addWidget(tableView_songsList);
    tableViewLayout->setContentsMargins(20, 15, 12, 9);
    tableViewLayout->setSpacing(0);

    vLayout = new QVBoxLayout();
    vLayout->addWidget(widgetTitle);
    vLayout->addWidget(widgetCenter);
    vLayout->addLayout(tableViewLayout);
    vLayout->setContentsMargins(0, 0, 0, 0);
    vLayout->setSpacing(0);

    this->setLayout(vLayout);
}

void SongsListWidget::initWidgetValue()
{
    label_title->setText("新歌榜");
    label_filter->setText("筛选条件");
    label_createTime->setText("上线时间");
    label_createTime_center->setText("至");
    label_language->setText("语种选择");
    label_type->setText("分类选择");
    label_num->setText("生成数量");
    label_listType->setText("歌榜分类");

    pushButton_filter->setText("筛选条件");
    pushBUtton_add->setText("手动添加");
    pushButton_save->setText("生成排行榜");

    QStringList num_list;
    num_list << "全部" << "前100" << "前200" << "前300";
    comboBox_num->addItems(num_list);
    comboBox_num->setCurrentIndex(1);

    checkBox_time_nolimit->setText("不限");
    checkBox_language_nolimit->setText("不限");
    checkBox_language_chinese->setText("国语");
    checkBox_language_cantonese->setText("粤语");
    checkBox_language_hokkien->setText("闽南语");
    checkBox_language_english->setText("英语");
    checkBox_language_japan->setText("日语");
    checkBox_language_korean->setText("韩语");
    checkBox_language_other->setText("其他");

    checkBox_type_nolimit->setText("不限");
    checkBox_type_romance->setText("甜蜜恋曲");
    checkBox_type_love->setText("情歌对唱");
    checkBox_type_nation->setText("民族歌曲");
    checkBox_type_military->setText("军旅歌曲");
    checkBox_type_hot->setText("劲爆舞曲");
    checkBox_type_child->setText("儿童歌曲");

    checkBox_type_opera->setText("戏曲片段");
    checkBox_type_old->setText("怀旧金曲");
    checkBox_type_paino->setText("乐曲钢琴");
    checkBox_type_birthday->setText("生日庆典");
    checkBox_type_cvoice->setText("中国好声音");
    checkBox_type_cstrong->setText("中国最强音");
    checkBox_type_cfsong->setText("我为歌狂");

    checkBox_type_imsing->setText("我是歌手");
    checkBox_type_cdream->setText("中国梦之声");
    checkBox_type_cgsong->setText("中国好歌曲");
    checkBox_type_starpair->setText("梦想星搭挡");
    checkBox_type_dj->setText("Dj舞曲");
    checkBox_type_movie->setText("影视类");
    checkBox_type_affection->setText("亲情类");

    checkBox_type_friend->setText("友情类");
    checkBox_type_broken->setText("苦情歌");
    checkBox_type_network->setText("网络神曲");
    checkBox_type_ancient->setText("古风");
    checkBox_type_school->setText("校园民谣");
    checkBox_type_motivational->setText("励志");
    checkBox_type_fashion->setText("励志");

    QDateTime date = QDateTime::currentDateTime();
    lineEdit_endTime->setText(date.toString("yyyy-MM-dd"));
    date = date.addDays(-1);
    lineEdit_startTime->setText(date.toString("yyyy-MM-dd"));
}

void SongsListWidget::setWidgetSize()
{
    widgetTitle->setFixedHeight(60);

    comboBox_num->setFixedWidth(150);
    comboBox_num->setFixedHeight(36);

    combobox_listType->setFixedSize(150, 36);
    label_listType->setFixedSize(60, 36);

    label_filter->setFixedHeight(36);
    label_createTime->setFixedHeight(36);
    label_createTime->setFixedWidth(60);
    label_createTime_center->setFixedHeight(36);

    label_language->setFixedHeight(36);
    label_language->setFixedWidth(60);
    label_type->setFixedHeight(36);
    label_type->setFixedWidth(60);
    label_num->setFixedHeight(36);
    label_num->setFixedWidth(60);

    lineEdit_startTime->setFixedWidth(150);
    lineEdit_startTime->setFixedHeight(36);
    lineEdit_endTime->setFixedWidth(150);
    lineEdit_endTime->setFixedHeight(36);

    pushButton_filter->setFixedHeight(36);
    pushButton_filter->setFixedWidth(90);
    pushBUtton_add->setFixedHeight(36);
    pushBUtton_add->setFixedWidth(90);
    pushButton_save->setFixedHeight(36);
    pushButton_save->setFixedWidth(90);


    QRect sCalendar = lineEdit_startTime->geometry();
    QRect eCalendar = lineEdit_endTime->geometry();
    lineEdit_startTime->setTextMargins(0, 0, 20, 0);
    pushButton_startCalendar->setGeometry(sCalendar.width()-25, 10, 20, 20);
    pushButton_startCalendar->setCursor(Qt::PointingHandCursor);
    lineEdit_endTime->setTextMargins(0, 0, 20, 0);
    pushButton_endCalendar->setGeometry(eCalendar.width()-25, 10, 20, 20);
    pushButton_endCalendar->setCursor(Qt::PointingHandCursor);

    pushButton_startCalendar->setCheckable(true);
    pushButton_endCalendar->setCheckable(true);
    calendar_start->resize(280, 180);
    calendar_end->resize(280, 180);
    calendar_start->setHidden(true);
    calendar_end->setHidden(true);

//    calendar_start->setGeometry(this->x() + 200, this->y() + 135, 280, 180);
//    calendar_end->setGeometry(this->x() + 350, this->y() + 135, 280, 180);

    checkBox_time_nolimit->setFixedWidth(88);
    checkBox_language_nolimit->setFixedWidth(88);
    checkBox_language_chinese->setFixedWidth(88);
    checkBox_language_cantonese->setFixedWidth(88);
    checkBox_language_hokkien->setFixedWidth(88);
    checkBox_language_english->setFixedWidth(88);
    checkBox_language_japan->setFixedWidth(88);
    checkBox_language_korean->setFixedWidth(88);
    checkBox_language_other->setFixedWidth(88);

    checkBox_type_nolimit->setFixedSize(88, 30);
    checkBox_type_romance->setFixedWidth(88);
    checkBox_type_love->setFixedWidth(88);
    checkBox_type_nation->setFixedWidth(88);
    checkBox_type_military->setFixedWidth(88);
    checkBox_type_hot->setFixedWidth(88);
    checkBox_type_child->setFixedWidth(88);

    checkBox_type_opera->setFixedSize(88, 30);
    checkBox_type_old->setFixedWidth(88);
    checkBox_type_paino->setFixedWidth(88);
    checkBox_type_birthday->setFixedWidth(88);
    checkBox_type_cvoice->setFixedWidth(88);
    checkBox_type_cstrong->setFixedWidth(88);
    checkBox_type_cstrong->setFixedWidth(88);

    checkBox_type_imsing->setFixedSize(88, 30);
    checkBox_type_cdream->setFixedWidth(88);
    checkBox_type_cgsong->setFixedWidth(88);
    checkBox_type_starpair->setFixedWidth(88);
    checkBox_type_dj->setFixedWidth(88);
    checkBox_type_movie->setFixedWidth(88);
    checkBox_type_affection->setFixedWidth(88);

    checkBox_type_friend->setFixedSize(88, 30);
    checkBox_type_broken->setFixedWidth(88);
    checkBox_type_network->setFixedWidth(88);
    checkBox_type_ancient->setFixedWidth(88);
    checkBox_type_school->setFixedWidth(88);
    checkBox_type_motivational->setFixedWidth(88);
    checkBox_type_fashion->setFixedWidth(88);
}

void SongsListWidget::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void SongsListWidget::setTypeHidden(bool checked)
{
    if(checked)
        widgetTypeHidden->setHidden(false);
    else
        widgetTypeHidden->setHidden(true);
}

void SongsListWidget::setFilterHidden(bool checked)
{
    if(checked)
        widgetCenter->setHidden(true);
    else
        widgetCenter->setHidden(false);
}


void SongsListWidget::initList(const QString type, const int &item, MysqlQuery *sql)
{   
    combobox_listType->setHidden(true);
    label_listType->setHidden(true);
    calendar_start->setGeometry(this->x() + 200, this->y() + 135, 280, 180);
    calendar_end->setGeometry(this->x() + 350, this->y() + 135, 280, 180);
    _sql = sql;
    _type = type;
    _widItem = item;
    setViewValue();
}

void SongsListWidget::initListNet(const int &item, MysqlQuery *sql)
{    
    combobox_listType->setHidden(false);
    label_listType->setHidden(false);
    calendar_start->setGeometry(this->x() + 200, this->y() + 180, 280, 180);
    calendar_end->setGeometry(this->x() + 350, this->y() + 180, 280, 180);
    _sql = sql;
    _widItem = item;

    if(!types.isEmpty())
        types.clear();
    _sql->getMediaListHotNetType(types, false);
    setHotNetTypes(types);
    setViewValue();
}

void SongsListWidget::initListHot(const int &item, MysqlQuery *sql)
{    
    combobox_listType->setHidden(false);
    label_listType->setHidden(false);
    calendar_start->setGeometry(this->x() + 200, this->y() + 180, 280, 180);
    calendar_end->setGeometry(this->x() + 350, this->y() + 180, 280, 180);
    _sql = sql;
    _widItem = item;

    if(!types.isEmpty())
        types.clear();
    _sql->getMediaListHotNetType(types, true);
    setHotNetTypes(types);
    setViewValue();
}

void SongsListWidget::setViewValue()
{    
    setTitleValue();
    tableView_songsList->initPagingQueryLimitArgu();    

    qint64 total = 0;
    if(_widItem == widItem_listHot){

        setHotNetViewValue();
    }else if(_widItem == widItem_listNet){

        setHotNetViewValue();
    }else{
        _sql->queryCountListMedia(_type, total);
        tableView_songsList->setTotal_Rows_Pages(total);
        updateViewValue();
    }

}

void SongsListWidget::setHotNetTypes(const QMap<int, QString> &types)
{
    QList<QString> _types = types.values();
    combobox_listType->clear();
    combobox_listType->addItems(_types);
}

void SongsListWidget::setHotNetViewValue()
{
    qint64 total = 0;
    int index = types.key(combobox_listType->currentText());
    QString type = QString::number(index);
    _type = type;
    if(_widItem == widItem_listHot)
        _sql->queryCountListHot(type, total);
    else
        _sql->queryCOuntListNet(type, total);

    tableView_songsList->setTotal_Rows_Pages(total);
    updateHotNetViewValue();
}

void SongsListWidget::updateViewValue()
{
    query.clear();
    tableView_songsList->tableView->clear();

    if(!_sql->queryMediaList(_type, tableView_songsList->limitArgu,  query)) return;
    tableView_songsList->showUploadMediaListData(query);
}

void SongsListWidget::updateHotNetViewValue() /////
{
    query.clear();
    tableView_songsList->tableView->clear();

    if(_widItem == widItem_listHot){
        if(!_sql->queryMediaListHot(_type, tableView_songsList->limitArgu,  query))
            return;
    }else{
        if(!_sql->queryMediaListNet(_type, tableView_songsList->limitArgu,  query))
            return;
    }
    tableView_songsList->showUploadMediaListData(query);
}

void SongsListWidget::createTimeStateChanged(int state)
{
    if(state){

        lineEdit_startTime->setEnabled(false);
        lineEdit_endTime->setEnabled(false);
        label_createTime_center->setEnabled(false);

    }else{

        lineEdit_startTime->setEnabled(true);
        lineEdit_endTime->setEnabled(true);
        label_createTime_center->setEnabled(true);
    }
}

void SongsListWidget::languageStateChanged(int state)
{
    if(state){
        checkBox_language_cantonese->setEnabled(false);
        checkBox_language_chinese->setEnabled(false);
        checkBox_language_english->setEnabled(false);
        checkBox_language_hokkien->setEnabled(false);
        checkBox_language_japan->setEnabled(false);
        checkBox_language_korean->setEnabled(false);
        checkBox_language_other->setEnabled(false);
    }else{
        checkBox_language_cantonese->setEnabled(true);
        checkBox_language_chinese->setEnabled(true);
        checkBox_language_english->setEnabled(true);
        checkBox_language_hokkien->setEnabled(true);
        checkBox_language_japan->setEnabled(true);
        checkBox_language_korean->setEnabled(true);
        checkBox_language_other->setEnabled(true);
    }
}

void SongsListWidget::typeStateChanged(int state)
{
    if(state){

        checkBox_type_romance->setEnabled(false);
        checkBox_type_love->setEnabled(false);
        checkBox_type_nation->setEnabled(false);
        checkBox_type_military->setEnabled(false);
        checkBox_type_hot->setEnabled(false);
        checkBox_type_child->setEnabled(false);

        widgetTypeHidden->setEnabled(false);
    }else{

        checkBox_type_romance->setEnabled(true);
        checkBox_type_love->setEnabled(true);
        checkBox_type_nation->setEnabled(true);
        checkBox_type_military->setEnabled(true);
        checkBox_type_hot->setEnabled(true);
        checkBox_type_child->setEnabled(true);

        widgetTypeHidden->setEnabled(true);
    }
}

void SongsListWidget::setStartCalendarShow(bool checked)
{
    if(checked){
        calendar_start->setHidden(false);
        calendar_start->setFocus();
    }else{
        calendar_start->setHidden(true);
    }
}

void SongsListWidget::setEndCalendarShow(bool checked)
{
    if(checked){
        calendar_end->setHidden(false);
        calendar_end->setFocus();
    }else{
        calendar_end->setHidden(true);
    }
}

void SongsListWidget::setStartDate()
{
    QString date = calendar_start->selectedDate().toString("yyyy-MM-dd");
    lineEdit_startTime->setText(date);
}

void SongsListWidget::setEndDate()
{
    QString date = calendar_end->selectedDate().toString("yyyy-MM-dd");
    lineEdit_endTime->setText(date);
}

void SongsListWidget::getMediaListValue(const QSqlQuery &_query, MediaList &_list)
{
    _list.type =  _type; //_query.value("_type").toString();
    _list.index = _query.value("_index").toString();
    _list.mid = _query.value("_mid").toString();
    _list.serial_id = _query.value("_serial_id").toString();
}

void SongsListWidget::moveUp(const int &row)
{
    if(row  <= 0)
        return;

    query.seek(row);

    MediaList ad, adPre;
    getMediaListValue(query, ad);

    if(!query.previous())
        return;
    getMediaListValue(query, adPre);

    if(_sql->updateMediaList(ad, adPre)){
       if(_sql->updateMediaList(adPre, ad));
       else
           _sql->updateMediaList(ad, adPre);
    }

    setViewValue();
}

void SongsListWidget::moveDown(const int &row)
{
    if(row >= query.size() - 1)
        return;
    query.seek(row);

    MediaList ad, adNext;
    getMediaListValue(query, ad);

    if(!query.next())
        return;
    getMediaListValue(query, adNext);

    if(_sql->updateMediaList(ad, adNext)){
        if(_sql->updateMediaList(adNext, ad));
        else
            _sql->updateMediaList(ad, adNext);
    }

    setViewValue();
}

void SongsListWidget::deleteMusic(const int &row)
{
    query.seek(row);
    MediaList ad;
    getMediaListValue(query, ad);

    if(_sql->deleteMedialist(ad))
        setViewValue();
}

void SongsListWidget::moveUpHN(const int &row)
{
    if(row  <= 0)
        return;

    query.seek(row);

    MediaList ad, adPre;
    getMediaListValue(query, ad);

    if(!query.previous())
        return;
    getMediaListValue(query, adPre);

    QString hn;
    if(_widItem == widItem_listHot)
        hn = "hot";
    else
        hn = "net";

    if(_sql->updateMediaList(ad, adPre, hn)){
       if(_sql->updateMediaList(adPre, ad, hn));
       else
           _sql->updateMediaList(ad, adPre, hn);
    }

    setViewValue();
}

void SongsListWidget::moveDownHN(const int &row)
{
    if(row >= query.size() - 1)
        return;
    query.seek(row);

    MediaList ad, adNext;
    getMediaListValue(query, ad);

    if(!query.next())
        return;
    getMediaListValue(query, adNext);

    QString hn;
    if(_widItem == widItem_listHot)
        hn = "hot";
    else
        hn = "net";

    if(_sql->updateMediaList(ad, adNext, hn)){
        if(_sql->updateMediaList(adNext, ad, hn));
        else
            _sql->updateMediaList(ad, adNext, hn);
    }

    setViewValue();
}

void SongsListWidget::deleteMusicHN(const int &row)
{
    query.seek(row);
    MediaList ad;
    getMediaListValue(query, ad);

    if(_widItem == widItem_listHot){
        _sql->deleteMediaList_hotnet(ad, "hot");
    }else{
        _sql->deleteMediaList_hotnet(ad, "net");
    }
    setViewValue();
}

void SongsListWidget::addMusic()
{
//    FmAddModifyDialog *list = new FmAddModifyDialog();
//    connect(list, SIGNAL(update_view()), this, SLOT(setViewValue()));
//    list->setTitle("添加歌曲");
//    list->setType_delegate(_widItem);
//    list->initMediaList();
//    list->initSql(_sql, query);
//    list->initType(_type);
////    list->setAdViewValue(_type);

//    list->exec();

    SongsListAddModifyDialog *dialog = new SongsListAddModifyDialog();
    connect(dialog, SIGNAL(update_view(QList<Media>)),
            this, SLOT(insertMediaList(QList<Media>)));
    dialog->setTitle("添加歌曲");
    dialog->initSql(_sql, query);
    dialog->initType(_type, _widItem);
    dialog->exec();
}

void SongsListWidget::createList()
{
    tableView_songsList->initPagingQueryLimitArgu();
    QStringList time;
    QStringList language;
    QStringList type;

    getTimeCondition(time);
    getLanguageCondition(language);
    getTypeCondition(type);

    QList<QStringList> condition;
    condition.insert(0, time);
    condition.insert(1, language);
    condition.insert(2, type);

    int limitNum = getLimitNum();

    query.clear();
    tableView_songsList->tableView->clear();
//    int total = 0;
//    _sql->queryCount_createList(condition, limitNum, total);
//    tableView_songsList->setTotal_Rows_Pages(total);
    if(!_sql->queryMediaList_createList(condition, query, limitNum))
        return;

    QStringList values;
    QMap<int, QString> hotnet;
    if(_widItem == widItem_listHot){

        hotnet.clear();
        _sql->getMediaListHot(hotnet);
        int key = hotnet.key(combobox_listType->currentText());
        QString keyStr = QString::number(key);
        setHotNetValues(values, keyStr);
        _sql->insertMediaList_hotnet("hot", key, values);

        setHotNetViewValue();
    }else if(_widItem == widItem_listNet){

        hotnet.clear();
        _sql->getMediaListNet(hotnet);
        int key = hotnet.key(combobox_listType->currentText());
        QString keyStr = QString::number(key);
        setHotNetValues(values, keyStr);
        _sql->insertMediaList_hotnet("net", key, values);

        setHotNetViewValue();
    }else{

        QString keyStr = QString("'%1'").arg(_type);
        setHotNetValues(values, keyStr);
        _sql->insertMediaList(_type, values, medias);
        setViewValue();
    }

}

void SongsListWidget::setHotNetValues(QStringList &values, QString &key)
{
    if(!values.isEmpty())
        values.clear();

    if(!medias.isEmpty())
        medias.clear();

    int i=0;
    while(query.next()){
        QString tempVa;
        tempVa.append(key);
        tempVa.append(",");
        tempVa.append(QString::number(i));
        tempVa.append(",");
        tempVa.append(QString::number(query.value("_mid").toInt()));

        MediaList media;
        media.index = QString::number(i);
        media.mid = query.value("_mid").toString();
        media.serial_id = query.value("_serial_id").toString();
        media.type = key;

        medias.append(media);
        values.append(tempVa);
        i++;
    }
}

void SongsListWidget::comboboxCurrentChange(const QString &)
{
    setHotNetViewValue();
}

void SongsListWidget::play(const int &row, const int &)
{
    query.seek(row);
    QString path = query.value("_path").toString();
    qDebug() << "path : " << path;
    if(!path.isEmpty())
        tableView_songsList->palyVideo(path);
}

void SongsListWidget::replace(const int &row)
{
//    FmAddModifyDialog *replace_list = new FmAddModifyDialog();
//    connect(replace_list, SIGNAL(update_view()), this, SLOT(setViewValue()));
//    replace_list->setTitle("替换歌曲");
//    replace_list->setType_delegate(_widItem);
//    replace_list->initMediaList();
//    replace_list->initSql(_sql, query);
//    replace_list->initType(_type);
//    replace_list->setReplaceRow(true, row);

//    replace_list->exec();

    replaceRow = row;
    SongsListAddModifyDialog *dialog = new SongsListAddModifyDialog();
    connect(dialog, SIGNAL(update_view(QList<Media>)),
            this, SLOT(replaceMediaList(QList<Media>)));
    dialog->setTitle("替换歌曲");
    dialog->initSql(_sql, query);
    dialog->initType(_type, _widItem);
    dialog->exec();
}

void SongsListWidget::replaceMediaList(QList<Media> _media)
{
    QString hotnet;
    if(_widItem == widItem_listNet)
    {
        hotnet = "net";
    }else if(_widItem == widItem_listHot)
    {
        hotnet = "hot";
    }else
    {
        hotnet = "";
    }

    query.seek(replaceRow);
    int srcMid, srcIndex, destMid;
    srcMid = query.value("_mid").toInt();
    srcIndex = query.value("_index").toInt();

    if(_media.isEmpty())
        return;

    QString mid = _media.at(0).mid;
    destMid = mid.toInt();
    QString serial_id = _media.at(0).serial_id;

    _sql->replaceMediaList(srcMid, srcIndex, destMid, _type, serial_id, hotnet);

    setViewValue();
}

void SongsListWidget::insertMediaList(QList<Media> _media)
{
    if(_widItem == widItem_listNet)
    {
        insertMediaListNet(_media);
    }else if(_widItem == widItem_listHot)
    {
        insertMediaListHot(_media);
    }else{

        QList<MediaList> addM;
        QStringList list;
        qint64 maxIndex;
        _sql->getMaxMediaListIndex(maxIndex);
        for(int i=0; i<_media.size(); i++){
            maxIndex++;
            MediaList media;
            QString tempStr;
            tempStr.append(QString("'%1'").arg(_type));
            tempStr.append(", ");
            tempStr.append(QString::number(maxIndex));
            tempStr.append(", ");
            tempStr.append(_media.at(i).mid);

            list.append(tempStr);

            ///json使用
            media.index = QString::number(maxIndex);
            media.type = _type;
            media.serial_id = _media.at(i).serial_id;

            addM.append(media);
        }

        _sql->addMediaList(_type, list, addM);
        setViewValue();
    }

}

void SongsListWidget::insertMediaListNet(QList<Media> _media)
{
    QStringList list;
    qint64 maxIndex = -1;
    _sql->getMaxMediaListIndex_hotnet("net", maxIndex);
    if(maxIndex == -1)
        return;

    for(int i=0; i<_media.size(); i++){
        maxIndex++;
        QString tempStr;
        tempStr.append(_type);
        tempStr.append(", ");
        tempStr.append(QString::number(maxIndex));
        tempStr.append(", ");
        tempStr.append(_media.at(i).mid);

        list.append(tempStr);
    }
    _sql->addMediaList_hotnet("net", _type, list);
    setViewValue();
}

void SongsListWidget::insertMediaListHot(QList<Media> _media)
{
    QStringList list;
    qint64 maxIndex = -1;
    if(_sql->getMaxMediaListIndex_hotnet("hot", maxIndex))
    {
        if(maxIndex == -1)
            return;

        for(int i=0; i<_media.size(); i++){
            maxIndex++;
            QString tempStr;
            tempStr.append(_type);
            tempStr.append(", ");
            tempStr.append(QString::number(maxIndex));
            tempStr.append(", ");
            tempStr.append(_media.at(i).mid);

            list.append(tempStr);
        }

        _sql->addMediaList_hotnet("hot", _type, list);
        setViewValue();
    }
}

void SongsListWidget::getTimeCondition(QStringList &time)
{
    if(checkBox_time_nolimit->isChecked()
       || lineEdit_startTime->text().isEmpty()
       || lineEdit_endTime->text().isEmpty())
        return;    

    time.append(lineEdit_startTime->text());
    time.append(lineEdit_endTime->text());
}

void SongsListWidget::getLanguageCondition(QStringList &language)
{
    if(checkBox_language_nolimit->isChecked())
        return;

    QStringList lan;
    if(checkBox_language_cantonese->isChecked())
        lan.append(checkBox_language_cantonese->text());
    if(checkBox_language_chinese->isChecked())
        lan.append(checkBox_language_chinese->text());
    if(checkBox_language_english->isChecked())
        lan.append(checkBox_language_english->text());
    if(checkBox_language_hokkien->isChecked())
        lan.append(checkBox_language_hokkien->text());
    if(checkBox_language_japan->isChecked())
        lan.append(checkBox_language_japan->text());
    if(checkBox_language_korean->isChecked())
        lan.append(checkBox_language_korean->text());
    if(checkBox_language_other->isChecked())
        lan.append(checkBox_language_other->text());

    QMap<int, QString> mediaLanguage;
    if(lan.size() > 0)
        _sql->getMediaLanguage(mediaLanguage);

    for(int i=0; i<lan.size(); i++){
        int key = mediaLanguage.key(lan.at(i));
        if(key == 0)
            continue;

        language.append(QString::number(key));
    }
}

void SongsListWidget::getTypeCondition(QStringList &type)
{
    if(checkBox_type_nolimit->isChecked()){
        return;
    }

    ///1
    QStringList typ;
    if(checkBox_type_nolimit->isChecked())
        typ.append(checkBox_type_nolimit->text());
    if(checkBox_type_romance->isChecked())
        typ.append(checkBox_type_romance->text());
    if(checkBox_type_love->isChecked())
        typ.append(checkBox_type_love->text());
    if(checkBox_type_nation->isChecked())
        typ.append(checkBox_type_nation->text());
    if(checkBox_type_military->isChecked())
        typ.append(checkBox_type_military->text());
    if(checkBox_type_hot->isChecked())
        typ.append(checkBox_type_hot->text());
    if(checkBox_type_child->isChecked())
        typ.append(checkBox_type_child->text());

    ///2
    if(checkBox_type_opera->isChecked())
        typ.append(checkBox_type_opera->text());
    if(checkBox_type_old->isChecked())
        typ.append(checkBox_type_old->text());
    if(checkBox_type_paino->isChecked())
        typ.append(checkBox_type_paino->text());
    if(checkBox_type_birthday->isChecked())
        typ.append(checkBox_type_birthday->text());
    if(checkBox_type_cvoice->isChecked())
        typ.append(checkBox_type_cvoice->text());
    if(checkBox_type_cstrong->isChecked())
        typ.append(checkBox_type_cstrong->text());
    if(checkBox_type_cfsong->isChecked())
        typ.append(checkBox_type_cfsong->text());

    ///3
    if(checkBox_type_imsing->isChecked())
        typ.append(checkBox_type_imsing->text());
    if(checkBox_type_cdream->isChecked())
        typ.append(checkBox_type_cdream->text());
    if(checkBox_type_cgsong->isChecked())
        typ.append(checkBox_type_cgsong->text());
    if(checkBox_type_starpair->isChecked())
        typ.append(checkBox_type_starpair->text());
    if(checkBox_type_dj->isChecked())
        typ.append(checkBox_type_dj->text());
    if(checkBox_type_movie->isChecked())
        typ.append(checkBox_type_movie->text());
    if(checkBox_type_affection->isChecked())
        typ.append(checkBox_type_affection->text());

    ///4
    if(checkBox_type_friend->isChecked())
        typ.append(checkBox_type_friend->text());
    if(checkBox_type_broken->isChecked())
        typ.append(checkBox_type_broken->text());
    if(checkBox_type_network->isChecked())
        typ.append(checkBox_type_network->text());
    if(checkBox_type_ancient->isChecked())
        typ.append(checkBox_type_ancient->text());
    if(checkBox_type_school->isChecked())
        typ.append(checkBox_type_school->text());
    if(checkBox_type_motivational->isChecked())
        typ.append(checkBox_type_motivational->text());
    if(checkBox_type_fashion->isChecked())
        typ.append(checkBox_type_fashion->text());

    QMap<int, QString> mediaType;
    if(typ.size() > 0)
        _sql->getMediaType(mediaType);

    for(int i=0; i<typ.size(); i++){
        int key = mediaType.key(typ.at(i));
        if(key == 0)
            continue;

        type.append(QString::number(key));
    }
}

int SongsListWidget::getLimitNum()
{
    int limitNum = 0;
    int comboboxIndex = comboBox_num->currentIndex();
    if(comboboxIndex == 0)
        limitNum = 0;
    if(comboboxIndex == 1)
        limitNum = 100;
    if(comboboxIndex == 2)
        limitNum = 200;
    if(comboboxIndex == 3)
        limitNum = 300;

    return limitNum;
}

void SongsListWidget::setTitleValue()
{
    if(_widItem == widItem_listNet)
        label_title->setText("网络排行榜");
    else if(_widItem == widItem_listHot)
        label_title->setText("选秀热歌榜");
    else if(_widItem == widItem_listNew)
        label_title->setText("新歌榜");
    else if(_widItem == widItem_listChinese)
        label_title->setText("华语音乐榜");
    else if(_widItem == widItem_listHi)
        label_title->setText("神曲嗨歌榜");
    else if(_widItem == widItem_listbillboard)
        label_title->setText("欧美音乐榜");
}
