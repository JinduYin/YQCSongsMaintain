#ifndef BLACKWIDGET_H
#define BLACKWIDGET_H

#include <QWidget>
#include <enuminfo.h>
#include <QSqlQuery>
#include "defistruct.h"
#include "curlupload.h"
class QLabel;
class QCheckBox;
class QTableView;
class QPushButton;
class PagingTableView;
class QVBoxLayout;
class QHBoxLayout;
class TableView;

class MysqlQuery;

class BlackWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BlackWidget(QWidget *parent = 0, int itemIndex = 0);
    ~BlackWidget();
    void readAndSetStyleSheet();
    void initWidget();
    void paintEvent(QPaintEvent *);
    void setWidgetValue(int  itemIndex);

    void initSqlQuery(MysqlQuery *sql);
    void initBlack_Media();
    void initBlack_Actor();
    void initBlack_Total();
    void show_black();
    void setBlackColumnWidth_Media(TableView *widget);
    void setBlackColumnWidth_Actor(QTableView *widget);   
signals:    

public slots:
    void addBlackRightMenu();
    void cancelBlack(const int &row);
    void cancelBlackMush();    
public:
    PagingTableView *tableView;
private:
    QHBoxLayout *title_layout;
    QVBoxLayout *tableView_layout;
    QVBoxLayout *vLayout;

    QWidget *widgetTitle;
    QLabel *label_title;

    QPushButton *pushButton_cancel;

    int _itemIndex;
    MysqlQuery    *_sql;
    QSqlQuery query;     

    QPushButton *pushButton_checkBox;
public:

    CurlUpload *curlDownlaod;
    QString runPath;
};

#endif // BLACKWIDGET_H
