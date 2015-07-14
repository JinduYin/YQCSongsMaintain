#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QSqlTableModel>
#include <QTableView>
#include <QWidget>
#include <QDesktopWidget>
#include <QTranslator>
#include <QStackedWidget>
#include <QListView>
#include <QSettings>
#include "dropshadowwidget.h"
#include "titlewidget.h"
#include "liblistview.h"
#include "libinfowidget.h"
#include "songsquerywideget.h"
#include "singerquerywidget.h"
#include "songsonlinewidget.h"
#include "singeronlinewidget.h"
#include "songslistwidget.h"
#include "fmwidget.h"
#include "adwidget.h"
#include "blackwidget.h"
#include "listinfowidget.h"

class MainWidget : public DropShadowWidget
{
    Q_OBJECT

public:

    MainWidget(QWidget *parent = 0);
    ~MainWidget();

     void initArgument();

protected:

    virtual void paintEvent(QPaintEvent *event);
private slots:
    void showMax();
    void mouseDoubleClickEvent(QMouseEvent *event);
    void turnPage(int current_row);

private:
    void initLib();
    void initSongQuery();
    void initSingerQuery();
    void initSingblack();
    void initSingerBlack();

public:
    static bool isIntOfStr(const QString &str);

private:
    QRect location;    
    LibListView *listView;
    QStackedWidget *stacked_widget;
    TitleWidget *title_widget; //标题栏
    QSettings *readConfig;
    MysqlQuery    *_sql;
    int currentRow;

    LibInfoWidget *lib_widget;
    SongsQueryWideget *song_query;
    SingerQueryWidget *singer_query;
    SongsOnlineWidget *song_online;
    SingerOnlineWidget *singer_online;
    SongsListWidget *song_list;
    SongsListWidget *song_listHotNet;
    FMWidget *fm;
    AdWidget *ad;
    BlackWidget *songs_black;
    BlackWidget *singer_black;
    ListInfoWidget *songs_Info;
    ListInfoWidget *singer_Info;
    ListInfoWidget *list_Info;    

    int desktopWidth;
    int desktopHeight;
};

#endif // MAINWIDGET_H
