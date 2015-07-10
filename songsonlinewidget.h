#ifndef SONGSONLINEWIDGET_H
#define SONGSONLINEWIDGET_H

#include <QMap>
#include <QWidget>
#include <QSqlQuery>
class Media;
class QLabel;
class QLineEdit;
class QPushButton;
class SongInfoWidget;
class QVBoxLayout;
class QHBoxLayout;
class QTableView;
class PagingTableView;
class MysqlQuery;

class SongsOnlineWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SongsOnlineWidget(QWidget *parent = 0);
    ~SongsOnlineWidget();

    void readAndSetStyleSheet();
    void initWidget();
    void initWidgetValue();
    void paintEvent(QPaintEvent *);
    void initComboboxValue(MysqlQuery *sql);

signals:

public slots:

private:
    void preview();
    void upload();
    void save();
    void updateView(const Media &media);

private:
    QHBoxLayout *previewLayout;
    QHBoxLayout *uploadLayout;
    QHBoxLayout *titleLayout;

    QHBoxLayout *saveLayout;
    QVBoxLayout *centerLayout;
    QVBoxLayout *infoSavelayout;
    QVBoxLayout *tableViewLayout;
    QVBoxLayout *vLayout;

    QWidget *widgetTitle;
    QWidget *widgetCenter;

    SongInfoWidget *widget_info;

    QLabel *label_title;
    QLabel *label_select;

    QLineEdit *lineEdit_upload;
    QPushButton *pushButton_upload;
    QPushButton *pushButton_preview;
    QPushButton *pushButton_save;

    PagingTableView *tableView_songsOnline;
    MysqlQuery *_sql;
    QSqlQuery query;
    QMap<int, QString> language, type, effect, resolution, quality;
    QMap<int, QString> source, version, rthym, pitch;
    QList< QStringList > rowList;

};


#endif // SONGSONLINEWIDGET_H
