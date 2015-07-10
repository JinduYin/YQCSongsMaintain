#ifndef FMINFOWIDGET_H
#define FMINFOWIDGET_H

#include <QWidget>
#include <QSqlQuery>
class QLabel;
class QTableView;
class QPushButton;
class MysqlQuery;
class PagingTableView;
class QVBoxLayout;
class QHBoxLayout;
class FmInfoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FmInfoWidget(QWidget *parent = 0);
    ~FmInfoWidget();

    void readAndSetStyleSheet();
    void initWidget();
    void initWidgetValue();
    void setWidgetSize();
    void paintEvent(QPaintEvent *);

    void initSql(MysqlQuery *sql);
    void setFmName(const QString &fmname);
    void setImage(const QString &path);
    void setTotal(const int &total);
    void setTotalRows(const int &total);
    void setTableValue(QSqlQuery &query);
    QRect getRightButtonGeometry();
    void clear();

    void setImage(const QPixmap &pixmap);
signals:
    void  modifyFm();
    void  deleteFm();

public slots:
    void play(const int &row, const int &);

private:
    QVBoxLayout *image_layout;
    QVBoxLayout *imageHeader_layout;
    QHBoxLayout *imageTable_layout;
    QHBoxLayout *fmName_layout;
    QHBoxLayout *fmModify_layout;
    QHBoxLayout *top_layout;

    QVBoxLayout *vLayout;

    QLabel *label_fmName;
    QLabel *label_total;
    QLabel *label_image_header;
    QLabel *label_image;

    QPushButton *pushButton_modify;
    QPushButton *pushButton_delete;

    PagingTableView *tableView_fm;
    MysqlQuery *_sql;
    QSqlQuery _query;
};

#endif // FMINFOWIDGET_H
