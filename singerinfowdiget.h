#ifndef SINGERINFOWDIGET_H
#define SINGERINFOWDIGET_H

#include "defistruct.h"
#include <QWidget>
#include <QMap>
class QLabel;
class QLineEdit;
class QComboBox;
class QPushButton;
class QVBoxLayout;
class QHBoxLayout;
class SingerInfoWdiget : public QWidget
{
    Q_OBJECT
public:
    explicit SingerInfoWdiget(QWidget *parent = 0);
    ~SingerInfoWdiget();

    void readAndSetStyleSheet();
    void initWidget();
    void initWidgetValue();
    void setWidgetSize();
    void paintEvent(QPaintEvent *);

    void isSingerOnline();
    void isPreviewAndModify();
    void isRequired();
    bool isEmpty();
    void set_disabled();
    void set_enabled();

    void getActorValue(Actor &_actor);
    void getActorOnlineValue(Actor &_actor);
    void setActorValue(const Actor &_actor);
    QString getImagePath();

    void set_comboBox_sex(QMap<int, QString> &_sex);
    void set_comboBox_nation(QMap<int, QString> &_nat);
    void set_comboBox_Remain();
    void setImageOnlineRetPath(const QString &path);

signals:

public slots:
    void uploadImage();
    void uploadImageOnline();
    void previewOnline();

private:
    QHBoxLayout *serial_id_layout;
    QHBoxLayout *sex_layout;
    QHBoxLayout *stars_layout;
    QHBoxLayout *pinyin_layout;
    QHBoxLayout *head_layout;
    QHBoxLayout *count_layout;
    QVBoxLayout *left_layout;

    QHBoxLayout *name_layout;
    QHBoxLayout *nation_layout;
    QHBoxLayout *enabled_layout;
    QHBoxLayout *header_layout;
    QHBoxLayout *words_layout;
    QHBoxLayout *info_layout;
    QHBoxLayout *info_online_layout;
    QVBoxLayout *center_layout;

    QHBoxLayout *upload_layout;
    QHBoxLayout *bottom_layout;
    QHBoxLayout *upload_online_layout;
    QHBoxLayout *bottom_online_layout;

    QHBoxLayout *image_tooltip_layout;
    QVBoxLayout *right_layout;
    QHBoxLayout *singerInfo_layout;
    QVBoxLayout *vLayout;

    QWidget *widgetLeft;
    QWidget *widgetCenter;
    QWidget *widgetRight;
    QWidget *widgetBottom;
    QWidget *widgetBottom_online;


    QLabel *label_serial_id;
    QLabel *label_sex;
    QLabel *label_stars;
    QLabel *label_pinyin;
    QLabel *label_head;
    QLabel *label_count;

    QLabel *label_name;
    QLabel *label_nation;
    QLabel *label_enabled;
    QLabel *label_header;
    QLabel *label_words;
    QLabel *label_info;
    QLabel *label_info_online;

    QLabel *label_image;
    QLabel *label_show_image;

private:
    ///星号提示
    QLabel *label_serial_id_tooptip;
    QLabel *label_sex_tooptip;
    QLabel *label_stars_tooptip;
    QLabel *label_pinyin_tooptip;
    QLabel *label_head_tooptip;
    QLabel *label_count_tooptip;

    QLabel *label_name_tooptip;
    QLabel *label_nation_tooptip;
    QLabel *label_enabled_tooptip;
    QLabel *label_header_tooptip;
    QLabel *label_words_tooptip;
    QLabel *label_info_tooptip;
    QLabel *label_info_online_tooptip;

    QLabel *label_image_tooptip;

    QLineEdit *lineEdit_serial_id;
    QLineEdit *lineEdit_pinyin;
    QLineEdit *lineEdit_head;
    QLineEdit *lineEdit_count;

    QLineEdit *lineEdit_name;
    QLineEdit *lineEdit_header;
    QLineEdit *lineEdit_words;
    QLineEdit *lineEdit_info;
    QLineEdit *lineEdit_image;
    QLineEdit *lineEdit_info_online;
    QLineEdit *lineEdit_image_online;

public:
    QPushButton *pushButton_upload;
    QPushButton *pushButton_upload_online;
    QPushButton *pushButton_preview_online;

    QComboBox *comboBox_sex;
    QComboBox *comboBox_stars;

    QComboBox *comboBox_nation;
    QComboBox *comboBox_enabled;


    Actor actor;
    QMap<int, QString> sex, nation, enabled, stars;
};

#endif // SINGERINFOWDIGET_H
