#ifndef FMADDMODIFYDIALOG_H
#define FMADDMODIFYDIALOG_H

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
class FmAddModifyDialog : public DropShadowWidget
{
    Q_OBJECT

public:    
    explicit FmAddModifyDialog(QWidget *parent = 0);
    ~FmAddModifyDialog();
    void paintEvent(QPaintEvent *);

    void initWidget();
    void initWidgetValue();

    void setTitle(const QString &str);
    void initSql(MysqlQuery *sql, QSqlQuery &query);
    void initType(const QString &type);
    void setReplaceRow(const bool &rep, const int &row);
    void setFmState(const int &state);
    void setType_delegate(const int &item);
    void setFmViewValue();

    void setAdViewValue(const QString &type);

    bool saveModityLid();
    bool saveNewLid();
    bool saveMusic();

    void initMediaList();
    bool saveMediaList();
    bool saveReplaceMediaList(QString hotnet = NULL);
    bool saveMediaListHot();
    bool saveMediaListNet();

    void setSavePushbuttonHidden(bool hidden = false);

signals:
    void update_view();

private slots:
    void close_dialog();
    void addMusic(bool checked = false);

    void previewImage();
    void uploadImage();

    void deleteMusic(const int &row);
    void moveUp(const int &row);
    void moveDown(const int &row);
    void replace(const int &row);
    void replaceViewMusic(const int &row);

    void serachMusic();    
    void addMusicDetail(const int &row);
    void save();    

    void play(const int &row, const int &);
    void playAddMusic(const int &row, const int &);

private:
    void getMusicDetail(QSqlQuery &querySearch, QStringList &tempValue);
    void getMediaListValue(const QSqlQuery &_que, MediaList &_list);



private:

    QWidget *widgetTitle;
    QWidget *widgetImage;
    QWidget *widgetAddMusic;

    QLabel *label_title;
    QLabel *label_listName;
    QLabel *label_listImage;
    QLabel *label_music;
    QLabel *label_image;

    QLineEdit *lineEdit_listName;
    QLineEdit *lineEdit_listImage;
    QLineEdit *lineEdit_search;

    QPushButton *pushButton_close;
    QPushButton *pushButton_preview;
    QPushButton *pushButton_upload;
    QPushButton *pushButton_addMusic;
    QPushButton *pushButton_save;
    QPushButton *pushButton_search;

    PagingTableView *view_addMusic;
    PagingTableView *view_music;

    MysqlQuery    *_sql;
    QSqlQuery _query;
    QSqlQuery _queryList;
    QSqlQuery _querySearch;
    int lid;
    QString imagePath;

    QList< QStringList > rowList;
    QList< QString > paths;

    int fmState;
    int _widItem;
    int replaceRow;

    bool replaceFalg;

    QString _type;
    SongList song_list;
};

#endif // FMADDMODIFYDIALOG_H
