#ifndef FMWIDGET_H
#define FMWIDGET_H

#include "defistruct.h"
#include <QWidget>
#include <QSqlQuery>
class QMenu;
class QLabel;
class QComboBox;
class QCheckBox;
class QLineEdit;
class QTableView;
class QPushButton;
class QNetworkReply;
class FmInfoWidget;
class MysqlQuery;
class FmAddModifyDialog;
class QVBoxLayout;
class QHBoxLayout;
class FMWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FMWidget(QWidget *parent = 0);
    ~FMWidget();

    void readAndSetStyleSheet();
    void initMenuAction();
    void initWidget();
    void initWidgetValue();
    void setWidgetSize();
    void paintEvent(QPaintEvent *);

    void initSql(MysqlQuery *sql);
public slots:
    void setFmValue();
    void show_FM();
public:
    int getOffset();
    void getFmvalue(const QSqlQuery &query, SongList &value);
    void setFmImage(const QString &title, const int &_index);
signals:

public slots:
    void up_page();
    void next_page();
    void first_page();
    void last_page();
    void jump_page(const int page);
    void jumpEditFinish();


    void on_fm01_customContextMenuRequested(const QPoint &pos);
    void on_fm02_customContextMenuRequested(const QPoint &pos);
    void fmMoveUpList();
    void fmMoveDownList();

    void newFmList();
    void modifyFmList();
    void deleteFmList();

//    void replyFinished(QNetworkReply *reply);?

private:
    QHBoxLayout *upload_layout;
    QHBoxLayout *newFM_layout;
    QHBoxLayout *title_layout;

    QVBoxLayout *fmTop_layout;
    QVBoxLayout *fm_layout;
    QVBoxLayout *vLayout;

    FmInfoWidget *fm01;
    FmInfoWidget *fm02;

    QWidget *widgetTitle;
    QWidget *widgetCenter;
    QWidget *widgetBottom;///翻页按键区

    QLabel *label_title;
    QLabel *label_center; //歌单中间隔离


    QLineEdit *lineEdit_upload;
    QPushButton *pushButton_upload;
    QPushButton *pushButton_newFM;


    QLabel *label_totalNum;
    QLabel *label_showPage;

    QLineEdit *lineEdit_jump;

    QPushButton *pushButton_upPage;
    QPushButton *pushButton_nextPage;
    QPushButton *pushButton_firstPage;
    QPushButton *pushButton_lastpage;
    QPushButton *pushButton_jumpPage;

    PagingQueryLimitArgu limitArgu;
    MysqlQuery *_sql;
    QSqlQuery query;
    QSqlQuery queryList;
    int index;

    QMenu   *fmMenu01;
    QMenu   *fmMenu02;
    QAction *fmMoveUp;
    QAction *fmMoveDown;

};

#endif // FMWIDGET_H
