#ifndef SINGERADDMODIFYDIALOG_H
#define SINGERADDMODIFYDIALOG_H

#include "dropshadowwidget.h"
#include "defistruct.h"
#include "mysqlquery.h"
#include <QObject>
#include <QWidget>
#include <QSqlQuery>
class Actor;
class QLabel;
class QPushButton;
class QLineEdit;
class PagingTableView;
class SingerAddModifyDialog : public DropShadowWidget
{
    Q_OBJECT

public:
    explicit SingerAddModifyDialog(QWidget *parent = 0);
    ~SingerAddModifyDialog();
    void paintEvent(QPaintEvent *);

    void initWidget();
    void initWidgetValue();

    void setTitle(const QString &str);
    void initSql(MysqlQuery *sql, QSqlQuery &query);

signals:
    void update_view(QList< Actor > actor);

private slots:
    void deleteMusic(const int &row);
    void serachMusic();
    void addMusicDetail(const int &row);
    void save();

private:
    void getSingerDetail(QSqlQuery &querySearch, QStringList &tempValue);

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


    QList< QStringList > rowList;
    QList< QString > paths;
    QList< Actor > actor;
};

#endif // SINGERADDMODIFYDIALOG_H
