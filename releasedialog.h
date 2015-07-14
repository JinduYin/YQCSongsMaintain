#ifndef RELEASEWIDGET_H
#define RELEASEWIDGET_H

#include "dropshadowwidget.h"
#include <QObject>
#include <QWidget>
#include <QMap>
#include <QDateTime>
#include "zip.h"
class QLabel;
class QDateEdit;
class QPushButton;
class QLineEdit;
class QCalendarWidget;
class QProgressBar;
class ReleaseDialog : public DropShadowWidget
{
    Q_OBJECT

public:
    explicit ReleaseDialog(QWidget *parent = 0);
    ~ReleaseDialog();
    void paintEvent(QPaintEvent *);

    void initWidget();
    void initWidgetValue();

    void setTitle(const QString &str);



private slots:

    void release();

    void calendar_start_clicked(bool checked = false);
    void calendar_end_clicked(bool checked = false);
    void setStartDateTime();
    void setEndDateTime();

private:
    void getDateTime(QDateTime &start, QDateTime &end);
    QString getReadFilePath(QDateTime &start, QDateTime &end);
    void readJsonFile(const QString &path);
    void downloadFiles(const QString json);

    void downloadImageFile(const QString &type, const QString &name);
    void downloadVideoLyric(const QString &type, const QString &path);

    QStringList getCurrentDirFiles(const QString &path);
    bool ZipAddFile(zipFile zf, QString lpszFileNameInZip, QString lpszFilePath, QString password, bool bUtf8 = false);
    bool setFilePath();

private:

    QWidget *widgetTitle;
    QWidget *widgetCenter;

    QLabel *label_title;
    QPushButton *pb_close;
    QPushButton *pb_release;
    QDateEdit *start_time;
    QDateEdit *end_time;
    QDateTime currentDate;

    QLineEdit *lineedit_name;
    QLineEdit *lineedit_pwd;
    QLineEdit *lineedit_start;
    QLineEdit *lineedit_end;
    QPushButton *pushbutton_start;
    QPushButton *pushbutton_end;
    QCalendarWidget *calendarStart;
    QCalendarWidget *calendarEnd;

    QString releasePath;
    QString jsonPath;
    QString avatarPath;
    QString fmPath;
    QString mp4Path;
    QString lyricPath;

    QProgressBar *bar;
};

#endif // RELEASEWIDGET_H
