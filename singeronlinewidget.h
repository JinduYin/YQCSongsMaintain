#ifndef SINGERONLINEWIDGET_H
#define SINGERONLINEWIDGET_H

#include <QMap>
#include <QSqlQuery>
#include <QWidget>
class Actor;
class QLabel;
class QLineEdit;
class QPushButton;
class SingerInfoWdiget;
class QVBoxLayout;
class QHBoxLayout;
class QTableView;
class MysqlQuery;
class PagingTableView;
class SingerOnlineWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SingerOnlineWidget(QWidget *parent = 0);
    ~SingerOnlineWidget();

    void readAndSetStyleSheet();
    void initWidget();
    void initWidgetValue();
    void paintEvent(QPaintEvent *);

    void initComboboxValue(MysqlQuery *sql);
    void updateView(Actor actor);
signals:

private slots:

    void upload();
    void preview();
    void save();

private:
    QHBoxLayout *previewLayout;
    QHBoxLayout *uploadLayout;
    QHBoxLayout *titleLayout;

    QHBoxLayout *saveLayout;
    QVBoxLayout *infoSavelayout;
    QVBoxLayout *centerLayout;

    QVBoxLayout *tableViewLayout;
    QVBoxLayout *vLayout;

    QWidget *widgetTitle;
    QWidget *widgetCenter;

    SingerInfoWdiget *widget_info;

    QLabel *label_title;
    QLabel *label_addSinger;

    QLineEdit *lineEdit_upload;
    QPushButton *pushButton_upload;
    QPushButton *pushButton_preview;
    QPushButton *pushButton_save;

    QMap<int, QString> sex, nation;
    PagingTableView *tableView_singerOnline;
    QList< QStringList > rowList;
    MysqlQuery *_sql;
    QSqlQuery query;
};

#endif // SINGERONLINEWIDGET_H
