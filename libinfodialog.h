#ifndef LIBINFODIALOG_H
#define LIBINFODIALOG_H

#include "dropshadowwidget.h"
#include "defistruct.h"
#include <QWidget>
#include <QSqlQuery>
class QLabel;
class QPushButton;
class PagingTableView;
class MysqlQuery;
class QHBoxLayout;
class QVBoxLayout;
class LibInfoDialog : public DropShadowWidget
{
    Q_OBJECT
public:
    explicit LibInfoDialog(bool isMedia = true, QWidget *parent = 0);
    ~LibInfoDialog();

    void paintEvent(QPaintEvent *);

    void setTitleString(const QString &title); 
    void showInfoActor(MysqlQuery *sql, ActorPagingQuery queryArgu);
    void showInfoMedia(MysqlQuery *sql, MediaPagingQuery queryArgu);
    void initActorOrMedia();

    void play(const int &row, const int &);
signals:

public slots:
    void showQueryValue();

private:
    QHBoxLayout *hLayout;
    QVBoxLayout *vLayout;

    QWidget *widgetTitle;
    QLabel *label_title;
    QPushButton *pushButton_close;

public:
    PagingTableView *view;
    MysqlQuery *_sql;
    QSqlQuery query;
    ActorPagingQuery _queryArgu_actor;
    MediaPagingQuery _queryArgu_media;
    bool _isMedia; ///
};

#endif // LIBINFODIALOG_H
