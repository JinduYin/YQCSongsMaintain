#ifndef SONGSQUERYWIDEGET_H
#define SONGSQUERYWIDEGET_H

#include <QMap>
#include <QWidget>
#include <QSqlQuery>
#include "defistruct.h"

class QVBoxLayout;
class QHBoxLayout;
class QSpacerItem;
class QGridLayout;

class QLabel;
class QLineEdit;
class QComboBox;
class QTableView;
class QPushButton;
class MysqlQuery;
class QSqlQuery;
class PagingTableView;
class QCalendarWidget;

class SongsQueryWideget : public QWidget
{
    Q_OBJECT
public:
    explicit SongsQueryWideget(QWidget *parent = 0);
    ~SongsQueryWideget();

    void readAndSetStyleSheet();
    void initWidget();
    void initWidgetValue();
    void paintEvent(QPaintEvent *);
public slots:
    void setMediaValue();
    void setSongInfo(const int &row);
    void setMatchMusic(const int &row, const int &isMatch);
    void play(const int &row, const int &);
public:
    void getQueryCondition(MediaPagingQuery &argu);
    void getValue(QSqlQuery &_query, Media &_media);
    void initSql(MysqlQuery *sql);
    void initCombobox();
    void set_comboBox_value(QComboBox *combobox, QMap<int, QString> &val);
//    void set_comboBox_Language(QList<QString> &lan);
//    void set_comboBox_type(QList<QString> &typ);
//    void set_comboBox_resolution(QList<QString> &res);
//    void set_comboBox_quality(QList<QString> &qua);
//    void set_comboBox_source(QList<QString> &sou);
//    void set_comboBox_version(QList<QString> &ver);
//    void set_comboBox_rthym(QList<QString> &rth);
//    void set_comboBox_pitch(QList<QString> &pit);


private:
    MediaPagingQuery argu;    

signals:

public slots:    
    void export_excel_clicked();
    void search_singer_clicked();
    void search_song_clicked();
    void calendar_start_clicked(bool checked = false);
    void calendar_end_clicked(bool checked = false);
    void setStartDateTime();
    void setEndDateTime();
    void combobox_currentIndexChanged(const QString &);
private:
   QHBoxLayout *searchSongLayout;
   QHBoxLayout *searchSingergLayout;
   QHBoxLayout *searchLayout;
   QHBoxLayout *titleLayout;

   QHBoxLayout *languageLayout;
   QHBoxLayout *typeLayout;
   QHBoxLayout *resolutionLayout;
   QHBoxLayout *qualityLayout;
   QHBoxLayout *sourceLayout;
   QHBoxLayout *versionLayout;
   QHBoxLayout *rthymLayout;
   QHBoxLayout *pitchLayout;
   QHBoxLayout *startTimeLayout;
   QHBoxLayout *endTimeLayout;
   QHBoxLayout *createTimeLayout;

   QVBoxLayout *centerLayout;
   QGridLayout *conditionLayout;

   QVBoxLayout *tableViewLayout;
   QVBoxLayout *vLayout;

   QWidget *widgetTitle;
   QWidget *widgetCenter;

   QLabel *label_title;
   QLabel *label_select;
   QLabel *label_Language;
   QLabel *label_type;
   QLabel *label_resolution;
   QLabel *label_quality;
   QLabel *label_source;
   QLabel *label_version;
   QLabel *label_rthym;
   QLabel *label_pitch;
   QLabel *label_startTime;
   QLabel *label_endTime;
   QLabel *label_zhi;
   QLabel *label_searchSong;
   QLabel *label_searchSinger;
   QLabel *label_result;


   QPushButton *pushButton_searchSong;
   QPushButton *pushButton_searchSinger;
   QPushButton *pushButton_startCalendar;
   QPushButton *pushButton_endCalendar;
   QPushButton *pushButton_export_excel;

   QComboBox *comboBox_Language;
   QComboBox *comboBox_type;
   QComboBox *comboBox_resolution;
   QComboBox *comboBox_quality;
   QComboBox *comboBox_source;
   QComboBox *comboBox_version;
   QComboBox *comboBox_rthym;
   QComboBox *comboBox_pitch;

   QLineEdit *lineEdit_searchSong;
   QLineEdit *lineEdit_searchSinger;
   QLineEdit *lineEdit_createTimeStart;
   QLineEdit *lineEdit_createTimeEnd;
   PagingTableView *tableView_songsQuery;
//   PagingTableWidget *widget_media;


   QCalendarWidget *calendarStart;
   QCalendarWidget *calendarEnd;
   MysqlQuery *_sql;
   QSqlQuery query;   
   QMap<int, QString> language, type, resolution, quality, effect;
   QMap<int, QString> source, version, rthym, pitch;
};

#endif // SONGSQUERYWIDEGET_H
