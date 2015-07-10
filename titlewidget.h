#ifndef TITLEWIDGET_H
#define TITLEWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QMouseEvent>
#include <QHBoxLayout>
#include <QSignalMapper>
#include <QVBoxLayout>
#include "pushbutton.h"
#include "dropshadowwidget.h"

class TitleWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TitleWidget(QWidget *parent = 0);

    void setLoginUserName(const QString &user);

private:
    void paintEvent(QPaintEvent *);

signals:
    void showMax();
    void showMin();
    void closeWidget();
    void double_Clicked();

public slots:

private:

    QLabel *logo_label;
    QLabel *title_label;
    QLabel *login_label;
    QPushButton *min_button; //最小化
    QPushButton *max_button; //最大化
    QPushButton *close_button; //关闭

    QList<QPushButton *> button_list;
};

#endif // TITLEWIDGET_H
