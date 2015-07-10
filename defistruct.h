#ifndef DEFISTRUCT
#define DEFISTRUCT

//#include <QString>
#include <QtGlobal>
#include <QStringList>
struct MediaPagingQuery{

    QString language;
    QString type;
    QString resolution;
    QString quality;
    QString source;
    QString version;
    QString rthym;
    QString pitch;    
    QString enabled;
    QString match;


    int _language;
    int _type;
    int _resolution;
    int _quality;
    int _source;
    int _version;
    int _rthym;
    int _pitch;
    int _enabled;
    int _match;
};

struct LimitArgumnet{ ///舍弃

    bool upPage;
    bool nextPage;
    qint64 curMaxVal;
    qint64 curMinVal;
    qint64 limitNum;
    qint64 limitStart;

    bool selectFlag;
};

struct PagingQueryLimitArgu{

    int tagPage; //  //初始值-1
    qint64 curMaxVal; /// 当前页最大值
    qint64 curMinVal;
    qint64 limitStartVal;
    qint64 limitOffset;
    int    rowNum; // 每页显示的行数
    int    currentpage; //当前页码
    int    totalRow; //总共行数
    int    totalPage;//总页码
};

enum paging{
    paging_jumppage = 0,
    paging_nextPage = 1,
    paging_upPage = 2,
    paging_firtPage = 3,
    paging_lastPage = 4
};

enum fmState{
    fm_modify = 0,
    fm_new = 1,
};

struct ActorPagingQuery{
    int _sex;
    int _nation;
    int _stars;
    int _enabled;
    QString singerName;
};


struct Media{

   QString mid;
   QString serial_id;
   QString artist_sid_1;
   QString artist_sid_2;
   QString count;

   QString name;
   QString singer;
   QString pinyin;
   QString header;
   QString head;

   QString path;
   QString lyric;
   QString create_time;
   QString update_time;
   QString info;

   QStringList musicTag;

   QString language;
   QString type;
   QString words;
   QString original_track;
   QString sound_track;

   QString start_volume_1;
   QString start_volume_2;
   QString prelude;
   QString effect;
   QString version;

   QString hot;
   QString enabled;
   QString black;
   QString match;
   QString resolution;

   QString quality;
   QString source;
   QString rhythm;
   QString pitch;
   QString stars;
};

struct Actor{
    QString sid;
    QString serial_id;
    QString count;

    QString name;
    QString pinyin;
    QString header;
    QString head;
    QString info;

    QString nation;
    QString sex;
    QString words;
    QString song_count;
    QString order;

    QString enabled;
    QString black;
    QString stars;

    QString image;
};

struct SongList{
    QString lid;
    QString serial_id;
    QString title;

    QString image;
    QString type;
    QString count;
    QString special;

    QString index;
    QString mid;
};

struct MediaList{
    QString type;
    QString index;
    QString mid;
    QString serial_id;
};



#endif // DEFISTRUCT

