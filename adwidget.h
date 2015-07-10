#ifndef ADWIDGET_H
#define ADWIDGET_H

#include <QWidget>
#include <QSqlQuery>
#include "defistruct.h"
class QLabel;
class QComboBox;
class MediaList;
class MysqlQuery;
class QTableView;
class QPushButton;
class PagingTableView;
class QVBoxLayout;
class QHBoxLayout;
class AdWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AdWidget(QWidget *parent = 0);
    ~AdWidget();

    void readAndSetStyleSheet();
    void initWidget();
    void initWidgetValue();
    void setWidgetSize();
    void paintEvent(QPaintEvent *);

    void initSql(MysqlQuery *sql);
    QString getType();
    void getAdValue(const QSqlQuery &_query, MediaList &_list);

signals:

public slots:
    void setAdValue();
    void combobox_IndexChanged(const int &);

    void moveUp(const int &row);
    void moveDown(const int &row);
    void deleteMusic(const int &row);
    void addMusic();

    void insertMediaList(QList<Media> _media);
    void play(const int &row, const int &);
private:
    QHBoxLayout *title_layout;
    QHBoxLayout *type_layout;

    QVBoxLayout *tableView_layout;
    QVBoxLayout *vLayout;

    QWidget *widgetTitle;
    QWidget *widgetCenter;
    QLabel *label_title;
    QLabel *label_type;
    QPushButton *pushButton_add;
    QComboBox *combobox_type;

    PagingTableView *tableView_Ad;
    MysqlQuery *_sql;
    QSqlQuery query;
};

#endif // ADWIDGET_H
