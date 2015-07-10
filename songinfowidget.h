#ifndef SONGINFOWIDGET_H
#define SONGINFOWIDGET_H

#include "defistruct.h"
#include <QWidget>
#include <QMap>
class Actor;
class Media;
class QLabel;
class QLineEdit;
class QComboBox;
class QPushButton;
class QCalendarWidget;
class QVBoxLayout;
class QHBoxLayout;

class SongInfoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SongInfoWidget(QWidget *parent = 0);
    ~SongInfoWidget();

    void readAndSetStyleSheet();
    void initWidget();
    void initWidgetValue();
    void setWidgetSize();
    void paintEvent(QPaintEvent *);

    void set_disabled();
    void set_enabled();
    void isRequired();
    bool isEmpty();
    void getMediaValue(Media &_media);
    void setMediaValue(const Media &_media);

    void set_comboBox_Language(QMap<int, QString> &lan);
    void set_comboBox_type(QMap<int, QString> &typ);
    void set_comboBox_version(QMap<int, QString> &ver);
    void set_comboBox_effect(QMap<int, QString> &eff);
    void set_comboBox_resolution(QMap<int, QString> &res);
    void set_comboBox_quality(QMap<int, QString> &qua);
    void set_comboBox_source(QMap<int, QString> &sou);
    void set_comboBox_rthym(QMap<int, QString> &rth);
    void set_comboBox_pitch(QMap<int, QString> &pit);

    void set_comboBox_track();
    void set_comboBox_Remain();

    QString uploadV(const QString path);
    QString uploadL(const QString path);

signals:

public slots:    
    void PushButton_question_pressed();
    void PushButton_question_released();

    void getCalendarDate(bool checked = false);
    void setDateTime();

    void addSinger();
    void uploadVideo();
    void uploadLyric();

    void setAddSinger(QList< Actor > _actor);

private:
    QHBoxLayout *serial_id_layout;
    QHBoxLayout *upload_video_pushbutton_layout;
    QHBoxLayout *upload_video_layout;
    QHBoxLayout *language_layout;
    QHBoxLayout *version_layout;
    QHBoxLayout *pinyin_layout;
    QHBoxLayout *head_layout;
    QHBoxLayout *source_layout;
    QHBoxLayout *create_time_layout;
    QVBoxLayout *leftLayout;

    QHBoxLayout *name_layout;
    QHBoxLayout *upload_lyric_pushbutton_layout;
    QHBoxLayout *upload_lyric_layout;
    QHBoxLayout *type_layout;
    QHBoxLayout *resolution_layout;
    QHBoxLayout *header_layout;
    QHBoxLayout *words_layout;
    QHBoxLayout *prelude_layout;
    QHBoxLayout *prelude_unit_layout;
    QHBoxLayout *rthym_layout;
    QVBoxLayout *centerLayout;

    QHBoxLayout *addSinger_pushbutton_layout;
    QHBoxLayout *addSinger_layout;
    QHBoxLayout *match_layout;
    QHBoxLayout *enabled_layout;
    QHBoxLayout *track_layout;
    QHBoxLayout *track_help_layout;
    QHBoxLayout *original_track_layout;
    QHBoxLayout *sound_track_layout;//ban chang
    QHBoxLayout *quality_layout;
    QHBoxLayout *effect_layout;
    QHBoxLayout *info_layout;
    QHBoxLayout *pitch_layout;
    QVBoxLayout *rightLayout;

public:
    QHBoxLayout *infoLayout;
    QHBoxLayout *attributeLayout;
    QHBoxLayout *attributeAddLayout;
    QVBoxLayout *vLayout;

    QCalendarWidget *calendar;
    QWidget *widgetLeft;
    QWidget *widgetRight;
    QWidget *widgetCenter;

    QWidget *widgetTrack;

    QLabel *label;
    QLabel *label_serial_id;
    QLabel *label_upload_video;
    QLabel *label_language;
    QLabel *label_version;
    QLabel *label_pinyin;
    QLabel *label_head;
    QLabel *label_source;
    QLabel *label_create_time;

    QLabel *label_name;
    QLabel *label_lyric;
    QLabel *label_type;
    QLabel *label_resolution;
    QLabel *label_header;
    QLabel *label_words;
    QLabel *label_prelude;
    QLabel *label_prelude_unit;
    QLabel *label_rthym;

    QLabel *label_addSinger;
    QLabel *label_match;
    QLabel *label_enabled;
    QLabel *label_track;
    QLabel *label_original_track;
    QLabel *label_sound_track;//ban chang
    QLabel *label_quality;
    QLabel *label_effect;
    QLabel *label_info;
    QLabel *label_pitch;

    QLabel *label_attribute;

    ///星号提示
    QLabel *label_serial_id_tooptip;
    QLabel *label_upload_video_tooptip;
    QLabel *label_language_tooptip;
    QLabel *label_version_tooptip;
    QLabel *label_pinyin_tooptip;
    QLabel *label_head_tooptip;
    QLabel *label_source_tooptip;
    QLabel *label_create_time_tooptip;

    QLabel *label_name_tooptip;
    QLabel *label_lyric_tooptip;
    QLabel *label_type_tooptip;
    QLabel *label_resolution_tooptip;
    QLabel *label_header_tooptip;
    QLabel *label_words_tooptip;
    QLabel *label_prelude_tooptip;
    QLabel *label_rthym_tooptip;

    QLabel *label_addSinger_tooptip;
    QLabel *label_match_tooptip;
    QLabel *label_enabled_tooptip;
    QLabel *label_track_tooptip;
    QLabel *label_quality_tooptip;
    QLabel *label_effect_tooptip;
    QLabel *label_info_tooptip;
    QLabel *label_pitch_tooptip;

    QLabel *label_attribute_tooptip;

    QLineEdit *lineEdit_serial_id;
    QLineEdit *lineEdit_upload_video;
    QLineEdit *lineEdit_pinyin;
    QLineEdit *lineEdit_head;
    QLineEdit *lineEdit_create_time;

    QLineEdit *lineEdit_name;
    QLineEdit *lineEdit_lyric;
    QLineEdit *lineEdit_header;
    QLineEdit *lineEdit_words;
    QLineEdit *lineEdit_prelude;
    QLineEdit *lineEdit_addSinger;
    QLineEdit *lineEdit_info;

    QComboBox *comboBox_language;
    QComboBox *comboBox_version;
    QComboBox *comboBox_source;

    QComboBox *comboBox_type;
    QComboBox *comboBox_resolution;
    QComboBox *comboBox_rthym;

    QComboBox *comboBox_match;
    QComboBox *comboBox_enabled;
    QComboBox *comboBox_original_track;
    QComboBox *comboBox_sound_track;//ban chang
    QComboBox *comboBox_quality;
    QComboBox *comboBox_effect;
    QComboBox *comboBox_pitch;

    QComboBox *comboBox_attribute01;
    QComboBox *comboBox_attribute02;
    QComboBox *comboBox_attribute03;
    QComboBox *comboBox_attribute04;
    QComboBox *comboBox_attribute05;
    QComboBox *comboBox_attribute06;

    QPushButton *pushButton_calendar;
    QPushButton *pushButton_addSinger;
    QPushButton *pushButton_upload_video;
    QPushButton *pushButton_upload_lyric;
    QPushButton *PushButton_question;
    QPushButton *PushButton_attribute;

public:
    QMap<int, QString> language, type, version, effect;
    QMap<int, QString> resolution, quality, source, rthym, pitch;
    QMap<int, QString> match, enabled, track;

    QList< Actor > actor;
    Media media;
};

#endif // SONGINFOWIDGET_H
