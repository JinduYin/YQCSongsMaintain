#ifndef SONGSLISTADDMODIFYDIALOG_H
#define SONGSLISTADDMODIFYDIALOG_H

#include "dropshadowwidget.h"
#include "defistruct.h"
#include "mysqlquery.h"
#include <QObject>
#include <QWidget>
#include <QSqlQuery>
class QLabel;
class QPushButton;
class QLineEdit;
class PagingTableView;
class SongsListAddModifyDialog : public DropShadowWidget
{
    Q_OBJECT

public:
    explicit SongsListAddModifyDialog(QWidget *parent = 0);
    ~SongsListAddModifyDialog();
    void paintEvent(QPaintEvent *);

    void initWidget();
    void initWidgetValue();

    void setTitle(const QString &str);
    void initSql(MysqlQuery *sql, QSqlQuery &query);
    void initType(const QString &type, const int &widItem);
    void setReplaceRow(const bool &rep, const int &row);

    void setViewValue(const QString &type);

//    bool saveModityLid();
//    bool saveNewLid();
//    bool saveMusic();

//    void initMediaList();
//    bool saveMediaList();
//    bool saveReplaceMediaList(QString hotnet = NULL);
//    bool saveMediaListHot();
//    bool saveMediaListNet();

signals:
    void update_view(QList< Media > actor);

private slots:
    void serachMusic();
    void deleteMusic(const int &row);
    void addMusicDetail(const int &row);
    void save();

    void play(const int &row, const int &);
    void playAddMusic(const int &row, const int &);

//    void previewImage();
//    void uploadImage();

//    void moveUp(const int &row);
//    void moveDown(const int &row);
//    void replace(const int &row);
//    void replaceViewMusic(const int &row);


//    void play(const int &row, const int &);
//    void playAddMusic(const int &row, const int &);

private:
    void getMusicDetail(QSqlQuery &querySearch, QStringList &tempValue);


private:

    QWidget *widgetTitle;
    QWidget *widgetCenter;
    QWidget *widgetBottom;

    QLabel *label_title;
    QLabel *label_music;
    QLineEdit *lineEdit_search;

    QPushButton *pushButton_close;
    QPushButton *pushButton_save;
    QPushButton *pushButton_search;

    PagingTableView *view_addMusic;
    PagingTableView *view_music;

    MysqlQuery    *_sql;
    QSqlQuery _query;
    QSqlQuery _querySearch;


    QList< Media > media;
    QList< QStringList > rowList;        
    QString _type;
    int _widItem;
};

#endif // SONGSLISTADDMODIFYDIALOG_H
