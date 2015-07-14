#include "stafflogin.h"
#include "ui_stafflogin.h"
#include "mysqlquery.h"

#include <QSqlQuery>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QCloseEvent>
#include <QCryptographicHash>
#include <QPalette>
#include <QDebug>

#define STAFFNAME_COLUMN 3
#define STAFFPWD_COLUMN  4

StaffLogin::StaffLogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StaffLogin)
{   
    ui->setupUi(this);
    this->setFixedSize(380, 444);
    setWindowFlags(Qt::FramelessWindowHint);
//    this->setStyleSheet("background-image:url(:/login/images/login_bg.png);");
    readAndSetStyleSheet();


    ui->lineEdit_password->setEchoMode(QLineEdit::Password);
    ui->lineEdit_userName->setPlaceholderText("工号……");
    ui->lineEdit_password->setPlaceholderText("密码……");
    ui->pushButton->setFocus();

//    loginSql = new MysqlQuery();
//    if (!loginSql->openMysql("yqcdb")){
//        loginSql->closeMysql("yqcdb");
//        this->close();
//    }
}

StaffLogin::~StaffLogin()
{
    delete ui;
}

void StaffLogin::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

QString StaffLogin::returnSHA1String(const QString str)
{
//    hash = new QCryptographicHash(QCryptographicHash::Sha1);
//    QByteArray temphash = hash->hash(str.toLatin1(), QCryptographicHash::Sha1);
//    QString md5pwd = temphash.toHex();
//    md5pwd = md5pwd.toUpper();

//    return md5pwd;
}

bool StaffLogin::loginVerification(const QString username, const QString pwd)
{
    QSqlQuery query(db);
    loginSql->queryStaff(query);
    while(query.next()){
        QString staffName = query.value(STAFFNAME_COLUMN).toString();
        QString staffPwd = query.value(STAFFPWD_COLUMN).toString();

        if (staffName.compare(username) == 0
            && staffPwd.compare(pwd) == 0){
            return true;
        }
    }

    return false;
}

void StaffLogin::on_pushButton_clicked()
{
    if (ui->lineEdit_userName->text().isEmpty()
        || ui->lineEdit_password->text().isEmpty()){
        QMessageBox::warning(this, "登录提示", "工号或密码不能为空！");
        return;
    }

    QString inputname = ui->lineEdit_userName->text();
    QString sha1pwd = returnSHA1String(ui->lineEdit_password->text());

    if (loginVerification(inputname, sha1pwd)){
        emit loginSuccess(inputname);
        loginSql->closeMysql("yqcdb");
        this->close();
    }
    else
        QMessageBox::warning(this, "登录失败提示", "工号或密码错误！");

}

void StaffLogin::on_pushButton_close_clicked()
{
    emit loginSuccess("");
    this->close();
}

void StaffLogin::readAndSetStyleSheet()
{
    QFile qss(":/qss/title.qss");
    qss.open(QFile::ReadOnly);
    this->setStyleSheet(qss.readAll());
    qss.close();


    this->setObjectName("login");
    ui->lineEdit_password->setObjectName("LineEdit");
    ui->lineEdit_userName->setObjectName("LineEdit");
    ui->pushButton->setObjectName("Button");
    ui->pushButton_close->setObjectName("Button");

    ui->pushButton->setFixedSize(90, 36);
    ui->pushButton_close->setFixedSize(90, 36);
    ui->lineEdit_password->setFixedSize(280, 36);
    ui->lineEdit_userName->setFixedSize(280, 36);
}

void StaffLogin::closeEvent(QCloseEvent *event)
{
    loginSql->closeMysql("yqcdb");  
}
