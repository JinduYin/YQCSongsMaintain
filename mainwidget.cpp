#include "mainwidget.h"
//#include "util.h"
#include "enuminfo.h"
#include "mysqlquery.h"
#include "pagingtableview.h"
#include "stafflogin.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QLineEdit>
#include <QDebug>


#define DATABASE_NAME "yiqiding_ktv" //yiqiding_ktv
#define DEFAULT_ROWHEIGHT 50
#define DEFAULT_MINNUM   10
#define DEFAULT_ROWCOUNT 20  //每页默认行数
#define DEFAULT_FMNUM  3
#define DEFAULT_ROWNUMOFPAGE 10

MainWidget::MainWidget(QWidget *parent)
    : DropShadowWidget(parent)
{
    initArgument();
    setFixedWidth(1440);
    setFixedHeight(860);
    setWindowFlags(Qt::FramelessWindowHint);
    location = this->geometry();

    desktopWidth = QApplication::desktop()->width();
    desktopHeight = QApplication::desktop()->height();

    QFile qss(":/qss/main.qss");
    qss.open(QFile::ReadOnly);
    this->setStyleSheet(qss.readAll());
    qss.close();

    listView = new LibListView();
    stacked_widget = new QStackedWidget();
    title_widget = new TitleWidget();

    this->setObjectName("MainWidget");
    stacked_widget->setObjectName("StackedWidget");

    QHBoxLayout *bottom_layout = new QHBoxLayout();
    bottom_layout->addWidget(listView, 0, Qt::AlignTop);
    bottom_layout->addWidget(stacked_widget);
    bottom_layout->setSpacing(8);
    bottom_layout->setContentsMargins(0, 0, 0, 0);

    QVBoxLayout *main_layout = new QVBoxLayout();
    main_layout->addWidget(title_widget);
    main_layout->addLayout(bottom_layout);
    main_layout->setSpacing(12);
    main_layout->setContentsMargins(8, 12, 8, 8);
    setLayout(main_layout);

    connect(title_widget, &TitleWidget::showMin, this, &MainWidget::showMinimized);
    connect(title_widget, &TitleWidget::showMax, this, &MainWidget::showMax);
    connect(title_widget, &TitleWidget::closeWidget, this, &MainWidget::close);
    connect(title_widget, &TitleWidget::double_Clicked, this, &MainWidget::showMax);
    connect(listView, &LibListView::currentPage, this, &MainWidget::turnPage);


    lib_widget = new LibInfoWidget(stacked_widget);
    song_query = new SongsQueryWideget(stacked_widget);
    singer_query = new SingerQueryWidget(stacked_widget);
    song_online = new SongsOnlineWidget(stacked_widget);
    singer_online = new SingerOnlineWidget(stacked_widget);
    song_list = new SongsListWidget(stacked_widget);
    song_listHotNet = new SongsListWidget(stacked_widget, true);
    fm = new FMWidget(stacked_widget);
    ad = new AdWidget(stacked_widget);
    songs_black = new BlackWidget(stacked_widget, stacked_mediablack);
    singer_black = new BlackWidget(stacked_widget, stacked_actorblack);
    songs_Info = new ListInfoWidget(stacked_widget, _sql);
    singer_Info = new ListInfoWidget(stacked_widget, _sql);
    list_Info = new ListInfoWidget(stacked_widget, _sql);

    initLib();

    initSingblack();
    initSingerBlack();

    stacked_widget->insertWidget(stacked_total, lib_widget);
    stacked_widget->insertWidget(stacked_mediaquery, song_query);
    stacked_widget->insertWidget(stacked_actorquery, singer_query);
    stacked_widget->insertWidget(stacked_mediaonline, song_online);
    stacked_widget->insertWidget(stacked_actoronline, singer_online);
    stacked_widget->insertWidget(stacked_medialist, song_list);
    stacked_widget->insertWidget(stacked_medialistHN, song_listHotNet);
    stacked_widget->insertWidget(stacked_FMlist, fm);
    stacked_widget->insertWidget(stacked_adlist, ad);
    stacked_widget->insertWidget(stacked_mediablack, songs_black);
    stacked_widget->insertWidget(stacked_actorblack, singer_black);
    stacked_widget->insertWidget(stacked_setmediainfo, songs_Info);
    stacked_widget->insertWidget(stacked_setactorinfo, singer_Info);
    stacked_widget->insertWidget(stacked_setlistinfo, list_Info);
}

MainWidget::~MainWidget()
{

}

void MainWidget::initArgument()
{
    readConfig = new QSettings("SongsMaintain.conf", QSettings::IniFormat);
    readConfig->setIniCodec("UTF-8");

    _sql = new MysqlQuery();
    _sql->openMysql(DATABASE_NAME);

//    for(int i=0; i<5; i++){
//        songsLibCheckFlag[i] = false;
//    }
//    songsLibOnlineFlag = false;
//    songsListFlag = false;
//    blackFlag = false;

//    currentRow = 0;

//    fmCurrentPage = 0;
//    fmTotalPage = 0;
//    fmTotalRows = 0;
//    fmListFlag = -1;

//    mediaCurPage = 0;
//    mediaCount = DEFAULT_ROWCOUNT;
}

void MainWidget::showMax()
{
    static bool is_max=false;
    if(is_max){
        this->setGeometry(location);
    }else{
        //获取当前界面的位置
        location = this->geometry();
        this->setGeometry(QApplication::desktop()->availableGeometry());        
    }
    is_max = !is_max;
}

void MainWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    QRect rect = title_widget->geometry();
    if(event->x() > rect.x() &&
       event->y() > rect.y() &&
       event->x() < rect.width()&&
       event->y() < rect.height())
    {
        showMax();
    }else
        event->ignore();
}

void MainWidget::turnPage(int current_row)
{
    if(current_row == -1)
        return;

    int stacked_page = -1;
    if ( current_row == widItem_LibTotal ){
//        lib_widget.initQueryCondition();
        stacked_page = stacked_total;
    }else if(current_row == widItem_songs){
        stacked_page = stacked_mediaquery;
        initSongQuery();
    }else if(current_row == widItem_singer){
        stacked_page = stacked_actorquery;
        initSingerQuery();
    }else if(current_row == widItem_songsOnline){

        stacked_page = stacked_mediaonline;
        song_online->initComboboxValue(_sql);
    }else if(current_row == widItem_singerOnline){

        stacked_page = stacked_actoronline;
        singer_online->initComboboxValue(_sql);
    }else if(current_row == widItem_listNew){
        stacked_page = stacked_medialist;
        song_list->initList("new", widItem_listNew,  _sql);
    }else if(current_row == widItem_listChinese){
        stacked_page = stacked_medialist;
        song_list->initList("chinese", widItem_listChinese, _sql);
    }else if(current_row == widItem_listHot){

        stacked_page = stacked_medialistHN;
        song_listHotNet->initListHot(widItem_listHot, _sql);
    }else if(current_row == widItem_listNet){

        stacked_page = stacked_medialistHN;
        song_listHotNet->initListNet(widItem_listNet, _sql);
    }else if(current_row == widItem_listHi){
        stacked_page = stacked_medialist;
        song_list->initList("hi" , widItem_listHi, _sql);
    }else if(current_row == widItem_listbillboard ){
        stacked_page = stacked_medialist;
        song_list->initList("billboard", widItem_listbillboard, _sql);
    }else if(current_row == widItem_FM){
        stacked_page = stacked_FMlist;
        fm->initSql(_sql);
        fm->setFmValue();
    }else if(current_row == widItem_AD){
        stacked_page = stacked_adlist;
        ad->initSql(_sql);
        ad->setAdValue();
    } else if(current_row == widItem_blackMusic){        
        stacked_page = stacked_mediablack;
        songs_black->show_black();
    }else if(current_row == widItem_blackSinger){
        singer_black->show_black();
        stacked_page = stacked_actorblack;

    }else if( current_row == widItem_songsInfo){
        stacked_page = stacked_setmediainfo;
        songs_Info->initSongInfo(stacked_setmediainfo);
    }else if( current_row == widItem_singerInfo){
        stacked_page = stacked_setactorinfo;
        singer_Info->initSingerInfo(stacked_setactorinfo);
    }else if( current_row == widItem_listInfo){
        stacked_page = stacked_setlistinfo;
        list_Info->initListInfo(stacked_setlistinfo);
    }

    stacked_widget->setCurrentIndex(stacked_page);
}

void MainWidget::initLib()
{
    lib_widget->initSqlPointer(_sql);
    lib_widget->initQueryCondition();
}

void MainWidget::initSongQuery()
{
    song_query->initSql(_sql);
    song_query->setMediaValue();
}

void MainWidget::initSingerQuery()
{
    singer_query->initSql(_sql);
    singer_query->setActorValue();
}

void MainWidget::initSingblack()
{
    songs_black->initSqlQuery(_sql);
    songs_black->initBlack_Media();        
}

void MainWidget::initSingerBlack()
{
    singer_black->initSqlQuery(_sql);
    singer_black->initBlack_Actor();
}

bool MainWidget::isIntOfStr(const QString &str)
{
    for (int i=0; i<str.size(); i++)
    {
        if(str.at(i) < '0' || str.at(i) > '9')
            return false;
    }
    return true;
}

void MainWidget::paintEvent(QPaintEvent *event)
{    
    DropShadowWidget::paintEvent(event);
    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::white);
    painter.drawRect(QRect(0, 0, this->width(), this->height()));

    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

    //    qDebug() << "width : " << stacked_widget->width() << " height : " << stacked_widget->height();
}



