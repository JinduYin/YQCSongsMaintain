#ifndef SINGERQUERYWIDGET_H
#define SINGERQUERYWIDGET_H

#include "defistruct.h"
#include <QWidget>
#include <QSqlQuery>
class QVBoxLayout;
class QHBoxLayout;
class QLabel;
class MysqlQuery;
class QSqlQuery;
class QLineEdit;
class QComboBox;
class QTableView;
class QPushButton;
class PagingTableView;
class SingerQueryWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SingerQueryWidget(QWidget *parent = 0);
    ~SingerQueryWidget();

    void readAndSetStyleSheet();
    void initWidget();
    void initWidgetValue();
    void paintEvent(QPaintEvent *);

public slots:
    void setActorValue();
    void setActorInfo(const int &row);
    void deleteActor(const int &row);

public:
    void getQueryCondition(ActorPagingQuery &argu);
    void getValue(QSqlQuery &_query, Actor &_actor);
    void initSql(MysqlQuery *sql);
    void initCombobox();
    void set_comboBox_sex(QStringList &sex);
    void set_comboBox_nation(QStringList &nat);
    void set_comboBox_stars(QStringList &sta);
    void set_comboBox_enabled(QStringList &ena);

signals:

public slots:
    void export_excel_clicked();

    void combobox_currentIndexChanged(const QString &);

private:
    QHBoxLayout *searchSingerLayout;
    QHBoxLayout *searchLayout;
    QHBoxLayout *titleLayout;

    QHBoxLayout *sexLayout;
    QHBoxLayout *nationLayout;
    QHBoxLayout *starsLayout;
    QHBoxLayout *enabledLayout;
    QHBoxLayout *conditionLayout;
    QVBoxLayout *centerLayout;
    QVBoxLayout *tableViewLayout;
    QVBoxLayout *vLayout;

    QWidget *widgetTitle;
    QWidget *widgetCenter;

    QLineEdit *lineEdit_search;
    QPushButton *pushButton_search;
    QPushButton *pushButton_export_excel;

    QLabel *label_search;
    QLabel *label_title;
    QLabel *label_select;
    QLabel *label_sex;
    QLabel *label_nation;
    QLabel *label_stars;
    QLabel *label_enabled;
    QLabel *label_result;

    QComboBox *comboBox_sex;
    QComboBox *comboBox_nation;
    QComboBox *comboBox_stars;
    QComboBox *comboBox_enabled;

    PagingTableView *tableView_singerQuery;
//   PagingTableWidget *widget_actor;

    MysqlQuery *_sql;
    QSqlQuery query;
};

#endif // SINGERQUERYWIDGET_H
