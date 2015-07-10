#include "songsquerywideget.h"
#include "pagingtableview.h"
#include "mysqlquery.h"
#include "tablemodel.h"
#include "songinfodialog.h"
#include <QFile>
#include <QLabel>
#include <QPainter>
#include <QLineEdit>
#include <QComboBox>
#include <QTableView>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QCalendarWidget>
#include <QDebug>

SongsQueryWideget::SongsQueryWideget(QWidget *parent)
    : QWidget(parent),
      _sql(NULL)
{    
    initWidget();
    readAndSetStyleSheet();
    initWidgetValue();    

    connect(pushButton_export_excel, &QPushButton::clicked, this, &SongsQueryWideget::export_excel_clicked);
    connect(pushButton_searchSinger, &QPushButton::clicked, this, &SongsQueryWideget::search_singer_clicked);
    connect(pushButton_searchSong, &QPushButton::clicked, this, &SongsQueryWideget::search_song_clicked);
    connect(pushButton_startCalendar, &QPushButton::clicked, this, &SongsQueryWideget::calendar_start_clicked);
    connect(pushButton_endCalendar, &QPushButton::clicked, this, &SongsQueryWideget::calendar_end_clicked);

    connect(calendarStart, &QCalendarWidget::selectionChanged, this, &SongsQueryWideget::setStartDateTime);
    connect(calendarEnd, &QCalendarWidget::selectionChanged, this, &SongsQueryWideget::setEndDateTime);

    connect(tableView_songsQuery, &PagingTableView::updateView, this, &SongsQueryWideget::setMediaValue);
    connect(tableView_songsQuery, &PagingTableView::currentRow, this, &SongsQueryWideget::setSongInfo);
    connect(tableView_songsQuery, &PagingTableView::matchMusic, this, &SongsQueryWideget::setMatchMusic);
    connect(tableView_songsQuery, &PagingTableView::play, this, &SongsQueryWideget::play);

    connect(comboBox_Language, SIGNAL(currentIndexChanged(QString)), this, SLOT(combobox_currentIndexChanged(QString)));
    connect(comboBox_type, SIGNAL(currentIndexChanged(QString)), this, SLOT(combobox_currentIndexChanged(QString)));
    connect(comboBox_resolution, SIGNAL(currentIndexChanged(QString)), this, SLOT(combobox_currentIndexChanged(QString)));
    connect(comboBox_quality, SIGNAL(currentIndexChanged(QString)), this, SLOT(combobox_currentIndexChanged(QString)));
    connect(comboBox_source, SIGNAL(currentIndexChanged(QString)), this, SLOT(combobox_currentIndexChanged(QString)));
    connect(comboBox_version, SIGNAL(currentIndexChanged(QString)), this, SLOT(combobox_currentIndexChanged(QString)));
    connect(comboBox_rthym, SIGNAL(currentIndexChanged(QString)), this, SLOT(combobox_currentIndexChanged(QString)));
    connect(comboBox_pitch, SIGNAL(currentIndexChanged(QString)), this, SLOT(combobox_currentIndexChanged(QString)));
}

SongsQueryWideget::~SongsQueryWideget()
{

}

void SongsQueryWideget::readAndSetStyleSheet()
{
    QFile qss(":/qss/songquery.qss");
    qss.open(QFile::ReadOnly);
    this->setStyleSheet(qss.readAll());
    qss.close();

    this->setObjectName("Widget");
    widgetTitle->setObjectName("TopWidget");
    widgetCenter->setObjectName("CenterWidget");
    label_title->setObjectName("TitleLabel");
    label_select->setObjectName("SelectLabel");
    label_result->setObjectName("ResultLabel");

    label_searchSinger->setObjectName("Label");
    label_searchSong->setObjectName("Label");

    label_Language->setObjectName("Label");
    label_type->setObjectName("Label");
    label_resolution->setObjectName("Label");
    label_quality->setObjectName("Label");
    label_source->setObjectName("Label");
    label_version->setObjectName("Label");
    label_rthym->setObjectName("Label");
    label_pitch->setObjectName("Label");
    label_startTime->setObjectName("Label");
    label_endTime->setObjectName("Label");

    pushButton_export_excel->setObjectName("Button");
    pushButton_searchSinger->setObjectName("SerachButton");
    pushButton_searchSong->setObjectName("SerachButton");
    pushButton_startCalendar->setObjectName("CalendarButton");
    pushButton_endCalendar->setObjectName("CalendarButton");

    lineEdit_createTimeEnd->setObjectName("TimeEdit");
    lineEdit_createTimeStart->setObjectName("TimeEdit");
    lineEdit_searchSinger->setObjectName("SerachEdit");
    lineEdit_searchSong->setObjectName("SerachEdit");

    comboBox_Language->setObjectName("Combobox");
    comboBox_type->setObjectName("Combobox");
    comboBox_resolution->setObjectName("Combobox");
    comboBox_quality->setObjectName("Combobox");
    comboBox_source->setObjectName("Combobox");
    comboBox_version->setObjectName("Combobox");
    comboBox_rthym->setObjectName("Combobox");
    comboBox_pitch->setObjectName("Combobox");

    calendarStart->setObjectName("calendar");
    calendarEnd->setObjectName("calendar");
}

void SongsQueryWideget::initWidget()
{
    widgetTitle = new QWidget(this);
    widgetCenter = new QWidget(this);

    calendarStart = new QCalendarWidget();
    calendarStart->resize(280, 180);
    calendarEnd = new QCalendarWidget();
    calendarEnd->resize(280, 180);
//    calendarStart->setWindowFlags(Qt::FramelessWindowHint);
//    calendarEnd->setWindowFlags(Qt::FramelessWindowHint);

    label_title = new QLabel(widgetTitle);
    label_select = new QLabel(widgetCenter);
    label_Language = new QLabel(widgetCenter);
    label_type = new QLabel(widgetCenter);
    label_resolution = new QLabel(widgetCenter);
    label_quality = new QLabel(widgetCenter);
    label_source = new QLabel(widgetCenter);
    label_version = new QLabel(widgetCenter);
    label_rthym = new QLabel(widgetCenter);
    label_pitch = new QLabel(widgetCenter);
    label_startTime = new QLabel(widgetCenter);
    label_endTime = new QLabel(widgetCenter);
    label_zhi = new QLabel(widgetCenter);
    label_searchSong = new QLabel(widgetCenter);
    label_searchSinger = new QLabel(widgetCenter);
    label_result = new QLabel(widgetCenter);

    comboBox_Language = new QComboBox(widgetCenter);
    comboBox_type = new QComboBox(widgetCenter);
    comboBox_resolution = new QComboBox(widgetCenter);
    comboBox_quality = new QComboBox(widgetCenter);
    comboBox_source = new QComboBox(widgetCenter);
    comboBox_version = new QComboBox(widgetCenter);
    comboBox_rthym = new QComboBox(widgetCenter);
    comboBox_pitch = new QComboBox(widgetCenter);

    lineEdit_searchSong = new QLineEdit(widgetTitle);
    lineEdit_searchSinger = new QLineEdit(widgetTitle);
    lineEdit_createTimeStart = new QLineEdit(widgetCenter);
    lineEdit_createTimeEnd = new QLineEdit(widgetCenter);
    tableView_songsQuery = new PagingTableView(this);

    pushButton_searchSong = new QPushButton(lineEdit_searchSong);
    pushButton_searchSinger = new QPushButton(lineEdit_searchSinger);
    pushButton_startCalendar = new QPushButton(lineEdit_createTimeStart);
    pushButton_endCalendar = new QPushButton(lineEdit_createTimeEnd);
    pushButton_export_excel = new QPushButton(widgetTitle);

    widgetCenter->setFixedHeight(150);
    pushButton_export_excel->setFixedHeight(36);
    pushButton_export_excel->setFixedWidth(90);
    lineEdit_searchSinger->setFixedWidth(260);
    lineEdit_searchSong->setFixedWidth(260);
    lineEdit_searchSinger->setFixedHeight(36);
    lineEdit_searchSong->setFixedHeight(36);

    comboBox_Language->setFixedHeight(36);
    comboBox_Language->setFixedWidth(110);
    comboBox_type->setFixedHeight(36);
    comboBox_type->setFixedWidth(110);
    comboBox_resolution->setFixedHeight(36);
    comboBox_resolution->setFixedWidth(110);
    comboBox_quality->setFixedHeight(36);
    comboBox_quality->setFixedWidth(110);
    comboBox_source->setFixedHeight(36);
    comboBox_source->setFixedWidth(110);
    comboBox_version->setFixedHeight(36);
    comboBox_version->setFixedWidth(110);
    comboBox_rthym->setFixedHeight(36);
    comboBox_rthym->setFixedWidth(110);
    comboBox_pitch->setFixedHeight(36);
    comboBox_pitch->setFixedWidth(110);

    lineEdit_createTimeEnd->setFixedWidth(150);
    lineEdit_createTimeEnd->setFixedHeight(36);
    lineEdit_createTimeStart->setFixedWidth(150);
    lineEdit_createTimeStart->setFixedHeight(36);

    titleLayout = new QHBoxLayout();
    searchSongLayout = new QHBoxLayout();
    searchSingergLayout = new QHBoxLayout();
    searchLayout = new QHBoxLayout();

    searchSingergLayout->addWidget(label_searchSinger);
    searchSingergLayout->addWidget(lineEdit_searchSinger);
    searchSingergLayout->setContentsMargins(0, 0, 0, 0);
    searchSingergLayout->setSpacing(6);

    searchSongLayout->addWidget(label_searchSong);
    searchSongLayout->addWidget(lineEdit_searchSong);
    searchSongLayout->setContentsMargins(0, 0, 0, 0);
    searchSongLayout->setSpacing(6);


    searchLayout->addLayout(searchSingergLayout);
    searchLayout->addLayout(searchSongLayout);
    searchLayout->addWidget(pushButton_export_excel);
    searchLayout->setContentsMargins(0, 0, 0, 0);
    searchLayout->setSpacing(20);

    titleLayout->addWidget(label_title);
    titleLayout->addStretch();
    titleLayout->addLayout(searchLayout);
    titleLayout->setContentsMargins(20, 10, 12, 10);
    widgetTitle->setLayout(titleLayout);
    widgetTitle->setFixedHeight(60);

    languageLayout = new QHBoxLayout();
    typeLayout = new QHBoxLayout();
    resolutionLayout = new QHBoxLayout();
    qualityLayout = new QHBoxLayout();
    sourceLayout = new QHBoxLayout();
    versionLayout = new QHBoxLayout();
    rthymLayout = new QHBoxLayout();
    pitchLayout = new QHBoxLayout();
    startTimeLayout = new QHBoxLayout();
    endTimeLayout = new QHBoxLayout();
    createTimeLayout = new QHBoxLayout();
    conditionLayout = new QGridLayout();
    centerLayout = new QVBoxLayout();

    languageLayout->addWidget(label_Language);
    languageLayout->addWidget(comboBox_Language);
    languageLayout->setContentsMargins(0, 0, 0, 0);
    languageLayout->setSpacing(8);

    typeLayout->addWidget(label_type);
    typeLayout->addWidget(comboBox_type);
    typeLayout->setContentsMargins(0, 0, 0, 0);
    typeLayout->setSpacing(8);

    resolutionLayout->addWidget(label_resolution);
    resolutionLayout->addWidget(comboBox_resolution);
    resolutionLayout->setContentsMargins(0, 0, 0, 0);
    resolutionLayout->setSpacing(8);

    qualityLayout->addWidget(label_quality);
    qualityLayout->addWidget(comboBox_quality);
    qualityLayout->setContentsMargins(0, 0, 0, 0);
    qualityLayout->setSpacing(8);

    sourceLayout->addWidget(label_source);
    sourceLayout->addWidget(comboBox_source);
    sourceLayout->setContentsMargins(0, 0, 0, 0);
    sourceLayout->setSpacing(8);

    versionLayout->addWidget(label_version);
    versionLayout->addWidget(comboBox_version);
    versionLayout->setContentsMargins(0, 0, 0, 0);
    versionLayout->setSpacing(8);

    rthymLayout->addWidget(label_rthym);
    rthymLayout->addWidget(comboBox_rthym);
    rthymLayout->setContentsMargins(0, 0, 0, 0);
    rthymLayout->setSpacing(8);

    pitchLayout->addWidget(label_pitch);
    pitchLayout->addWidget(comboBox_pitch);
    rthymLayout->setContentsMargins(0, 0, 0, 0);
    rthymLayout->setSpacing(8);

    startTimeLayout->addWidget(label_startTime);
    startTimeLayout->addWidget(lineEdit_createTimeStart);
    startTimeLayout->setContentsMargins(0, 0, 0, 0);
    startTimeLayout->setSpacing(8);

    endTimeLayout->addWidget(label_endTime);
    endTimeLayout->addWidget(lineEdit_createTimeEnd);
    endTimeLayout->setContentsMargins(0, 0, 0, 0);
    endTimeLayout->setSpacing(10);

    createTimeLayout->addLayout(startTimeLayout);
    createTimeLayout->addLayout(endTimeLayout);
    createTimeLayout->setContentsMargins(0, 0, 0, 0);
    createTimeLayout->setSpacing(10);

    conditionLayout->addLayout(languageLayout, 0, 0);
    conditionLayout->addLayout(typeLayout, 0, 1);
    conditionLayout->addLayout(resolutionLayout, 0, 2);
    conditionLayout->addLayout(qualityLayout, 0, 3);
    conditionLayout->addLayout(sourceLayout, 0, 4);
    conditionLayout->addLayout(versionLayout, 1, 0);
    conditionLayout->addLayout(rthymLayout, 1, 1);
    conditionLayout->addLayout(pitchLayout, 1, 2);
    conditionLayout->addLayout(createTimeLayout, 1, 3, 1, 2);
    conditionLayout->setContentsMargins(26, 0, 0, 0);
    conditionLayout->setHorizontalSpacing(52);
    conditionLayout->setVerticalSpacing(14);

    centerLayout->addWidget(label_select);
    centerLayout->addLayout(conditionLayout);
    centerLayout->setContentsMargins(20, 15, 36, 20);

    widgetCenter->setLayout(centerLayout);

    tableViewLayout = new QVBoxLayout();
    tableViewLayout->addWidget(label_result);
    tableViewLayout->addWidget(tableView_songsQuery);
    tableViewLayout->setContentsMargins(20, 15, 12, 9);
    tableViewLayout->setSpacing(10);

    vLayout = new QVBoxLayout();
    vLayout->addWidget(widgetTitle);
    vLayout->addWidget(widgetCenter);
    vLayout->addLayout(tableViewLayout);
    vLayout->setContentsMargins(0, 0, 0, 0);
    vLayout->setSpacing(0);

    this->setLayout(vLayout);
}

void SongsQueryWideget::initWidgetValue()
{
    label_title->setText("歌曲查询");
    label_select->setText("筛选条件");
    label_Language->setText("歌曲语种");
    label_type->setText("歌曲分类");
    label_resolution->setText("歌曲分辨率");
    label_quality->setText("歌曲质量");
    label_source->setText("歌曲来源");
    label_version->setText("版本类型");
    label_rthym->setText("歌曲节奏");
    label_pitch->setText("高音类型   ");
    label_startTime->setText("上线时间");
    label_endTime->setText("至");
    label_result->setText("搜索结果");
    label_searchSong->setText("歌曲搜索");
    label_searchSinger->setText("歌星搜索");

    lineEdit_searchSong->setPlaceholderText("歌曲名称");
    lineEdit_searchSinger->setPlaceholderText("歌星名称");

    pushButton_export_excel->setText("导出总表");    
    tableView_songsQuery->setQueryMediaDelegate();

    QRect singerRect = lineEdit_searchSinger->geometry();
    QRect songRect = lineEdit_searchSong->geometry();
    lineEdit_searchSinger->setTextMargins(0, 0, 20, 0);
    pushButton_searchSinger->setGeometry(singerRect.width()-20, 10, 14, 14);
    pushButton_searchSinger->setCursor(Qt::PointingHandCursor);
    lineEdit_searchSong->setTextMargins(0, 0, 20, 0);
    pushButton_searchSong->setGeometry(songRect.width()-20, 10, 14, 14);
    pushButton_searchSong->setCursor(Qt::PointingHandCursor);

    QRect sCalendar = lineEdit_createTimeStart->geometry();
    QRect eCalendar = lineEdit_createTimeEnd->geometry();
    lineEdit_createTimeStart->setTextMargins(0, 0, 20, 0);
    pushButton_startCalendar->setGeometry(sCalendar.width()-25, 10, 20, 20);
    pushButton_startCalendar->setCursor(Qt::PointingHandCursor);
    lineEdit_createTimeEnd->setTextMargins(0, 0, 20, 0);
    pushButton_endCalendar->setGeometry(eCalendar.width()-25, 10, 20, 20);
    pushButton_endCalendar->setCursor(Qt::PointingHandCursor);



    pushButton_startCalendar->setCheckable(true);
    pushButton_endCalendar->setCheckable(true);

    calendarStart->setHidden(true);
    calendarEnd->setHidden(true);
}

void SongsQueryWideget::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void SongsQueryWideget::setMediaValue()
{
    MediaPagingQuery argu;
    getQueryCondition(argu);

    qint64 total = 0;
    _sql->queryCountMedia_M(argu, total);
    tableView_songsQuery->setTotal_Rows_Pages(total);

    query.clear();
    tableView_songsQuery->tableView->clear();

    _sql->queryMedia(argu, tableView_songsQuery->limitArgu, query);
    tableView_songsQuery->showUploadData(query, true);
}

void SongsQueryWideget::getQueryCondition(MediaPagingQuery &argu)
{
    argu.language = comboBox_Language->currentText();
    argu.type = comboBox_type->currentText();
    argu.resolution = comboBox_resolution->currentText();
    argu.quality = comboBox_quality->currentText();
    argu.source = comboBox_source->currentText();
    argu.version = comboBox_version->currentText();
    argu.rthym = comboBox_rthym->currentText();
    argu.pitch = comboBox_pitch->currentText();

    argu.enabled = "";
    argu.match = "";

    argu._language = comboBox_Language->currentIndex();
    argu._type = comboBox_type->currentIndex();
    argu._resolution = comboBox_resolution->currentIndex();
    argu._quality = comboBox_quality->currentIndex();
    argu._source = comboBox_source->currentIndex();
    argu._version = comboBox_version->currentIndex();
    argu._rthym = comboBox_rthym->currentIndex();
    argu._pitch = comboBox_pitch->currentIndex();

    argu._enabled = 0;
    argu._match = 0;
}

void SongsQueryWideget::setSongInfo(const int &row)
{
    SongInfoDialog *dialog = new SongInfoDialog();

    query.seek(row);
    qint64 serial = query.value("_serial_id").toLongLong();
    QSqlQuery _query;
    Media _media;
    if(!_sql->queryMediaOfSerialId(serial, _query))
        return;   

    dialog->info->language = language;
    dialog->info->type = type;
    dialog->info->resolution = resolution;
    dialog->info->quality = quality;
    dialog->info->effect = effect;
    dialog->info->source = source;
    dialog->info->version = version;
    dialog->info->rthym = rthym;
    dialog->info->pitch = pitch;

    getValue(_query, _media);
    dialog->setValue(_media);

    dialog->exec();
}

void SongsQueryWideget::setMatchMusic(const int &row, const int &isMatch)
{
    query.seek(row);

    qint64 mid = query.value("_mid").toLongLong();
    _sql->updateMatchMusic(mid, isMatch);
}

void SongsQueryWideget::play(const int &row, const int &)
{
    query.seek(row);
    QString path = query.value("_path").toString();   
    tableView_songsQuery->palyVideo(path);
}

void SongsQueryWideget::getValue(QSqlQuery &_query, Media &_media)
{
    _query.first();
    _media.mid = _query.value("mid").toString();
    _media.serial_id = _query.value("serial_id").toString();
    _media.name = _query.value("name").toString();
    _media.language = _query.value("language").isNull()?"": _query.value("language").toString();
    _media.type = _query.value("type").isNull()?"":_query.value("type").toString();

    _media.singer = _query.value("singer").toString();
    _media.artist_sid_1 = _query.value("artist_sid_1").toString();
    _media.artist_sid_2 = _query.value("artist_sid_2").toString();
    _media.pinyin = _query.value("pinyin").toString();
    _media.header = _query.value("header").toString();

    _media.head = _query.value("head").toString();
    _media.words = _query.value("words").toString();
    _media.path = _query.value("path").toString();
    _media.lyric = _query.value("lyric").toString();
    _media.original_track = _query.value("original_track").toString();

    _media.sound_track = _query.value("sound_track").toString();
    _media.start_volume_1 = _query.value("start_volume_1").toString();
    _media.start_volume_2 = _query.value("start_volume_2").toString();
    _media.prelude = _query.value("prelude").isNull()?"":_query.value("prelude").toString();
    _media.effect = _query.value("effect").isNull()?"":_query.value("effect").toString();

    _media.version = _query.value("version").isNull()?"":_query.value("version").toString();
    _media.create_time = _query.value("create_time").toString();
    _media.stars = _query.value("stars").isNull()?"":_query.value("stars").toString();
    _media.hot = _query.value("hot").toString();
    _media.count = _query.value("count").toString();

    _media.enabled = _query.value("enabled").isNull()?"":_query.value("enabled").toString();
    _media.black = _query.value("black").isNull()?"":_query.value("black").toString();
    _media.match = _query.value("match").isNull()?"":_query.value("match").toString();
    _media.update_time = _query.value("update_time").toString();
    _media.resolution = _query.value("resolution").isNull()?"":_query.value("resolution").toString();

    _media.quality = _query.value("quality").isNull()?"":_query.value("quality").toString();
    _media.source = _query.value("source").isNull()?"":_query.value("source").toString();
    _media.rhythm = _query.value("rhythm").isNull()?"":_query.value("rhythm").toString();
    _media.pitch = _query.value("pitch").isNull()?"":_query.value("pitch").toString();
    _media.info = _query.value("info").toString();

}

void SongsQueryWideget::initSql(MysqlQuery *sql)
{
    _sql = sql;
    initCombobox();
}

void SongsQueryWideget::initCombobox()
{        
    _sql->getMediaLanguage(language);
    _sql->getMediaType(type);
    _sql->getMediaResolution(resolution);
    _sql->getMediaQuality(quality);
    _sql->getMediaEffect(effect);
    _sql->getMediaSource(source);
    _sql->getMediaVersion(version);
    _sql->getMediaRthym(rthym);
    _sql->getMediaPitch(pitch);

    set_comboBox_value(comboBox_Language, language);
    set_comboBox_value(comboBox_type, type);
    set_comboBox_value(comboBox_resolution, resolution);
    set_comboBox_value(comboBox_quality, quality);

    set_comboBox_value(comboBox_source, source);
    set_comboBox_value(comboBox_version, version);
    set_comboBox_value(comboBox_rthym, rthym);
    set_comboBox_value(comboBox_pitch, pitch);
}

void SongsQueryWideget::set_comboBox_value(QComboBox *combobox, QMap<int, QString> &val)
{
    QList<QString> tempVal = val.values();
    tempVal.insert(0, "全部");
    QStringList value(tempVal);
    combobox->clear();
    combobox->addItems(value);
}

void SongsQueryWideget::export_excel_clicked()
{
    QMessageBox::aboutQt(this, "导出总表");
}

void SongsQueryWideget::search_singer_clicked()
{
    QMessageBox::aboutQt(this, "歌星搜索");
}

void SongsQueryWideget::search_song_clicked()
{
    QMessageBox::aboutQt(this, "歌曲搜索");
}

void SongsQueryWideget::calendar_start_clicked(bool checked)
{
    QRect rect = calendarStart->geometry();
    QPoint point = QCursor::pos();

    rect.setX(point.x());
    rect.setY(point.y());

    calendarStart->setGeometry(point.x() - 230, point.y() + 50, 280, 180);

    if(checked){
        calendarStart->setHidden(false);
        calendarStart->setFocus();
    }else{
        calendarStart->setHidden(true);
    }
}

void SongsQueryWideget::calendar_end_clicked(bool checked)
{
    QRect rect = calendarStart->geometry();
    QPoint point = QCursor::pos();

    rect.setX(point.x());
    rect.setY(point.y());

    calendarEnd->setGeometry(point.x() - 230, point.y() + 50, 280, 180);

    if(checked){
        calendarEnd->setHidden(false);
        calendarEnd->setFocus();
    }else{
        calendarEnd->setHidden(true);
    }
}

void SongsQueryWideget::setStartDateTime()
{
    QString date = calendarStart->selectedDate().toString("yyyy-MM-dd");
    lineEdit_createTimeStart->setText(date);
}

void SongsQueryWideget::setEndDateTime()
{
    QString date = calendarEnd->selectedDate().toString("yyyy-MM-dd");
    lineEdit_createTimeEnd->setText(date);
}

void SongsQueryWideget::combobox_currentIndexChanged(const QString &)
{
    tableView_songsQuery->limitArgu.currentpage = 0;
    tableView_songsQuery->current_page = 0;
    tableView_songsQuery->limitArgu.tagPage = -1;
    setMediaValue();
}

