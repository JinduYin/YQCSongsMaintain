#ifndef SONGSLISTWIDGET_H
#define SONGSLISTWIDGET_H

#include <QMap>
#include <QWidget>
#include <QSqlQuery>
#include "defistruct.h"
class MediaList;
class QLabel;
class QComboBox;
class QCheckBox;
class QLineEdit;
class QTableView;
class QPushButton;
class QCalendarWidget;
class MysqlQuery;
class PagingTableView;
class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class SongsListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SongsListWidget(QWidget *parent = 0, bool _hotnet = false);
    ~SongsListWidget();

    void readAndSetStyleSheet();
    void initWidget();
    void initWidgetValue();
    void setWidgetSize();
    void paintEvent(QPaintEvent *);

    void initList(const QString type, const int &item, MysqlQuery *sql);
    void initListNet(const int &item, MysqlQuery *sql);
    void initListHot(const int &item, MysqlQuery *sql);


public slots:
    void setViewValue();
    void setHotNetTypes(const QMap<int, QString> &types);
    void setHotNetViewValue();
    void updateViewValue();
    void updateHotNetViewValue();

    void createTimeStateChanged(int state);
    void languageStateChanged(int state);
    void typeStateChanged(int state);


    void moveUp(const int &row);
    void moveDown(const int &row);
    void deleteMusic(const int &row);

    void moveUpHN(const int &row);
    void moveDownHN(const int &row);
    void deleteMusicHN(const int &row);

    void addMusic();
    void createList();    

    void setHotNetValues(QStringList &values, QString &key);
    void comboboxCurrentChange(const QString &);
    void play(const int &row, const int &);
    void replace(const int &row);

    void replaceMediaList(QList<Media> _media);
    void insertMediaList(QList<Media> _media);
    void insertMediaListNet(QList<Media> _media);
    void insertMediaListHot(QList<Media> _media);

signals:

public slots:
    void setTypeHidden(bool checked = false);
    void setFilterHidden(bool checked = false);

    void setStartCalendarShow(bool checked = false);
    void setEndCalendarShow(bool checked = false);
    void setStartDate();
    void setEndDate();

private:
     void getMediaListValue(const QSqlQuery &_query, MediaList &_list);

     void getTimeCondition(QStringList &time);
     void getLanguageCondition(QStringList &language);
     void getTypeCondition(QStringList &type);

     int getLimitNum();
     void setTitleValue();

private:
    QHBoxLayout *filter_add_layout;
    QHBoxLayout *title_layout;

    QHBoxLayout *startEndTime_layout;
    QHBoxLayout *createTime_noLimit_layout;
    QHBoxLayout *createTime_layout;

    QHBoxLayout *language_noLimit_layout;
    QHBoxLayout *language_layout;

    QHBoxLayout *type_noLimit_layout;
    QHBoxLayout *type_layout;

    QHBoxLayout *num_layout;

    QHBoxLayout *type_hidden_layout01;
    QHBoxLayout *type_hidden_layout02;
    QHBoxLayout *type_hidden_layout03;
    QVBoxLayout *vHidden_layout;
//    QGridLayout *vHidden_layout;
    QVBoxLayout *info_layout;
    QVBoxLayout *vCenter_layout;

    QVBoxLayout *tableViewLayout;
    QVBoxLayout *vLayout;

    QWidget *widgetTitle;
    QWidget *widgetCenter;
    QWidget *widgetTypeHidden;

    QLabel *label_title;
    QLabel *label_filter;
    QLabel *label_createTime;
    QLabel *label_createTime_center;
    QLabel *label_language;
    QLabel *label_type;
    QLabel *label_num;
    QLabel *label_listType;

    QLineEdit *lineEdit_startTime;
    QLineEdit *lineEdit_endTime;

    QPushButton *pushButton_filter;
    QPushButton *pushBUtton_add;
    QPushButton *pushButton_startCalendar;
    QPushButton *pushButton_endCalendar;
    QPushButton *pushButton_hidden;
    QPushButton *pushButton_save;

    QComboBox *comboBox_num;
    QComboBox *combobox_listType;

    QCheckBox *checkBox_time_nolimit;
    QCheckBox *checkBox_language_nolimit;
    QCheckBox *checkBox_language_chinese;
    QCheckBox *checkBox_language_cantonese;
    QCheckBox *checkBox_language_hokkien;
    QCheckBox *checkBox_language_english;
    QCheckBox *checkBox_language_japan;
    QCheckBox *checkBox_language_korean;
    QCheckBox *checkBox_language_other;

    ///1
    QCheckBox *checkBox_type_nolimit;
    QCheckBox *checkBox_type_romance;
    QCheckBox *checkBox_type_love;
    QCheckBox *checkBox_type_nation;
    QCheckBox *checkBox_type_military;
    QCheckBox *checkBox_type_hot;
    QCheckBox *checkBox_type_child;
    ///2
    QCheckBox *checkBox_type_opera;
    QCheckBox *checkBox_type_old;
    QCheckBox *checkBox_type_paino;
    QCheckBox *checkBox_type_birthday;
    QCheckBox *checkBox_type_cvoice;
    QCheckBox *checkBox_type_cstrong;
    QCheckBox *checkBox_type_cfsong;
    ///3
    QCheckBox *checkBox_type_imsing;
    QCheckBox *checkBox_type_cdream;
    QCheckBox *checkBox_type_cgsong;
    QCheckBox *checkBox_type_starpair;
    QCheckBox *checkBox_type_dj;
    QCheckBox *checkBox_type_movie;
    QCheckBox *checkBox_type_affection;
    ///4
    QCheckBox *checkBox_type_friend;
    QCheckBox *checkBox_type_broken;
    QCheckBox *checkBox_type_network;
    QCheckBox *checkBox_type_ancient;
    QCheckBox *checkBox_type_school;
    QCheckBox *checkBox_type_motivational;
    QCheckBox *checkBox_type_fashion;

    PagingTableView *tableView_songsList;
    MysqlQuery *_sql;
    QSqlQuery query;
    QString _type;
    int _widItem;

    QCalendarWidget *calendar_start;
    QCalendarWidget *calendar_end;

    QMap<int, QString> types;
    bool hotnet;
    int replaceRow;

    QList<MediaList> medias;
};

#endif // SONGSLISTWIDGET_H
