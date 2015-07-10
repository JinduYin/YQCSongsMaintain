#ifndef SONGINFODIALOG_H
#define SONGINFODIALOG_H

#include "dropshadowwidget.h"
#include "songinfowidget.h"
#include "defistruct.h"
#include <QWidget>
class QLabel;
class MysqlQuery;
class QHBoxLayout;
class QVBoxLayout;
class SongInfoDialog : public DropShadowWidget
{
public:
    explicit SongInfoDialog(QWidget *parent = 0);
    ~SongInfoDialog();

    void initWidget();
    void initWidgetValue();
    void paintEvent(QPaintEvent *);    
    void setTitleString(const QString &title);
    void setSqlPointer(MysqlQuery *sql);
    void selectStyleSheet(bool hidden = false);
    void setValue(const Media _media);
    void setComboBoxValue(QComboBox *combobox, QList<QString> list);
public slots:
    void updateMediaValue();
    void save();
private:
    QHBoxLayout *hLayout;
    QHBoxLayout *previewLayout;
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

    QLabel *label_videoPreview;
    QPushButton *pushButton_videoPreview;

    QPushButton *pushButton_Yes;
    QPushButton *pushButton_update;
    QPushButton *pushButton_save;

    QLabel *label_prompt;
    QLabel *label_prompt_tooptip;

    MysqlQuery *_sql;
    qint64   mid;
public:
    SongInfoWidget *info;
};

#endif // SONGINFODIALOG_H
