#ifndef ADDFMMEDIALIST_H
#define ADDFMMEDIALIST_H

#include <QDialog>
#include <QSqlQuery>
class MysqlQuery;

namespace Ui {
class AddFmMediaList;
}

class AddFmMediaList : public QDialog
{
    Q_OBJECT

public:
    explicit AddFmMediaList(QWidget *parent = 0);
    ~AddFmMediaList();

signals:
    void updateView();

public:
    void initAddFm();
    void initUpdateFm(MysqlQuery *sql, QSqlQuery *lidQuery, QSqlQuery *query);
    void setSqlPointer(MysqlQuery *sql);
    void setQueryPointer(QSqlQuery *lidQuery, QSqlQuery *query);

private:
    void initTableWidget();
    void setTableWidget();
    void setFmMediaList();

private slots:
    void addMenuRight(const QPoint &pos);
    void upMove();
    void downMove();
    void deleItem();
    void on_pushButton_preview_clicked();

private:
    Ui::AddFmMediaList *ui;


    MysqlQuery    *_sql;
    QSqlQuery *_fmQuery;
    QSqlQuery *_fmLidQuery;


    QAction *up;
    QAction *down;
    QAction *dele;
};

#endif // ADDFMMEDIALIST_H
