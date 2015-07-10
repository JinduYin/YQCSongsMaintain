#ifndef SINGERINFODIALOG_H
#define SINGERINFODIALOG_H

#include "dropshadowwidget.h"
#include "singerinfowdiget.h"
#include "defistruct.h"
#include <QWidget>
class QLabel;
class MysqlQuery;
class QHBoxLayout;
class QVBoxLayout;
class SingerInfoDialog : public DropShadowWidget
{
public:
    explicit SingerInfoDialog(QWidget *parent = 0);
    ~SingerInfoDialog();

    void initWidget();
    void initWidgetValue();
    void paintEvent(QPaintEvent *);
    void setTitleString(const QString &title);
    void setSqlPointer(MysqlQuery *sql);
    void selectStyleSheet(bool hidden = false);
    void setValue(const Actor _media);
    void setComboBoxValue(QComboBox *combobox, QList<QString> list);
public slots:
    void updateActorValue();
    void save();
private:
    QHBoxLayout *hLayout;
    QHBoxLayout *updateLayout;
    QHBoxLayout *saveLayout;
    QHBoxLayout *promptLayout;
    QVBoxLayout *infoLayout;
    QVBoxLayout *wbLayout;
    QVBoxLayout *vLayout;

    QWidget *widgetTitle;
    QWidget *widgetCenter;
    QWidget *widgetUpdate;
    QWidget *widgetSave;
    QLabel *label_title;
    QLabel *label;
    QPushButton *pushButton_close;

    SingerInfoWdiget *info;

    QPushButton *pushButton_Yes;
    QPushButton *pushButton_update;
    QPushButton *pushButton_save;

    QLabel *label_prompt;
    QLabel *label_prompt_tooptip;

    MysqlQuery *_sql;
    qint64   sid;
};

#endif // SINGERINFODIALOG_H
