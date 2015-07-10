#ifndef LISTINFOWIDGET_H
#define LISTINFOWIDGET_H

#include <QWidget>
#include "enuminfo.h"
#include "mysqlquery.h"
class QLabel;
class QTableView;
class QComboBox;
class QLineEdit;
class QPushButton;
class QVBoxLayout;
class QHBoxLayout;
class PagingTableView;
class ListInfoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ListInfoWidget(QWidget *parent = 0, MysqlQuery *sql = NULL);
    ~ListInfoWidget();
    void readAndSetStyleSheet();
    void initWidget();
    void paintEvent(QPaintEvent *);
    void setWidgetValue(int itemIndex);

    void initSql(MysqlQuery *sql);
    void initSongInfo(int itemIndex);
    void initSingerInfo(int itemIndex);
    void initListInfo(int itemIndex);

private:
    void setModelData(QMap<int, QString> &values);

signals:

public slots:
    void setSongViewValue(const int &index);
    void setSingerViewValue(const int &index);
    void setListViewValue(const int &index);

    void modifyList(const int &row);
    void deleteList(const int &row);
    void addList(const int &);

    void editFinish();

private:
    QHBoxLayout *title_layout;
    QHBoxLayout *select_layout;

    QVBoxLayout *tableView_layout;
    QVBoxLayout *vLayout;

    QWidget *widgetCenter;
    QLabel *label_title;
    QLabel *label_select;
    QComboBox *combobox_select;
    QLineEdit *edit;
    QLineEdit *tempEdit;
    PagingTableView *tableView_listInfo;

    MysqlQuery *_sql;

    int _itemIndex;
    QMap<int, QString> values;
    QList<QStringList> datas;

    QString src;
    QString dest;
};

#endif // LISTINFOWIDGET_H
