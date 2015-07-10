#ifndef TYPEINDEXVALUE_H
#define TYPEINDEXVALUE_H
#include <QWidget>
#include <QMap>
class TypeIndexValue
{
public:
    TypeIndexValue();
    ~TypeIndexValue();
private:
    void initType();
    void initLanguage();
    void initVersion();
    void initEffect();
    void initResolution();
    void initQuality();
    void initSource();
    void initRhythm();
    void initPitch();

    void initNation();
    void initSex();

    void initMatch();
    void initEnabled();
    void initTrack();
    void initStars();

public:


public:
    QMap<int, QString> type;  //歌曲类型
    QMap<int, QString> language; //歌曲语种
    QMap<int, QString> version; //版本类型
    QMap<int, QString> effect; //音效类型
    QMap<int, QString> resolution; //分辨率类型
    QMap<int, QString> quality; //音质类型
    QMap<int, QString> source; //来源类型
    QMap<int, QString> rhythm; //节奏类型
    QMap<int, QString> pitch; //高音类型

    QMap<int, QString> nation; // 国籍
    QMap<int, QString> sex; // 性别

    QMap<int, QString> match;
    QMap<int, QString> enabled;
    QMap<int, QString> track;
    QMap<int, QString> stars;
};

#endif // TYPEINDEXVALUE_H
