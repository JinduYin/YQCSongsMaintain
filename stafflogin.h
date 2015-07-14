#ifndef STAFFLOGIN_H
#define STAFFLOGIN_H

#include <QDialog>
#include <QSqlDatabase>
#include "dropshadowwidget.h"

class MysqlQuery;
class QCryptographicHash;

namespace Ui {
class StaffLogin;
}

class StaffLogin : public QDialog
{
    Q_OBJECT

public:
    explicit StaffLogin(QWidget *parent = 0);
    ~StaffLogin();

    void paintEvent(QPaintEvent *evnet);

signals:
    void loginSuccess(QString username);

public:
    bool loginVerification(const QString username, const QString pwd);
    QString returnSHA1String(const QString str);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_close_clicked();
private:
    void readAndSetStyleSheet();
    void closeEvent(QCloseEvent *event);
private:
    MysqlQuery *loginSql;
    QSqlDatabase db;
    QCryptographicHash *hash;

private:
    Ui::StaffLogin *ui;
};

#endif // STAFFLOGIN_H
