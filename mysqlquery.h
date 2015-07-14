#ifndef MYSQLQUERY_H
#define MYSQLQUERY_H

#include <QSqlDatabase>
#include <QMap>
#include <QString>
class Media;
class Actor;
class QJsonObject;
class SongList;
class MediaList;
class QSettings;
class QSqlTableModel;
class MediaPagingQuery;
class LimitArgumnet;
class ActorPagingQuery;
class PagingQueryLimitArgu;

class MysqlQuery
{
public:
    MysqlQuery();
    ~MysqlQuery();

public:
    void readConfigFile();
    bool openMysql(const QString databaseName="yiqiding_ktv");
    void closeMysql(const QString databaseName="yiqiding_ktv");

    bool queryStaff(QSqlQuery &query);    
    bool querySql(const QString &queryStr, QSqlQuery &query);
    bool queryActor(const ActorPagingQuery &argu, const PagingQueryLimitArgu &limitArg, QSqlQuery &query);
    bool queryMedia(const MediaPagingQuery &argu, const PagingQueryLimitArgu &limitArg, QSqlQuery &query);


    bool queryActorOfSerialId(const qint64 serial, QSqlQuery &query);
    bool queryMediaOfSerialId(const qint64 serial, QSqlQuery &query);
    bool queryMediaList(const QString argu, const PagingQueryLimitArgu &limitArg, QSqlQuery &query);
    bool queryMediaList(const QString argu, QSqlQuery &query);

    bool queryMediaList_createList(QList<QStringList> &condition, QSqlQuery &query, const int &limitNum);
    bool queryCount_createList(QList<QStringList> &condition,  int limitNum, int &count);

    bool queryMediaListHot(const QString argu, const PagingQueryLimitArgu &limitArg, QSqlQuery &query);
    bool queryMediaListNet(const QString argu, const PagingQueryLimitArgu &limitArg, QSqlQuery &query);

    bool queryMediaBlack(const PagingQueryLimitArgu &limitArg, QSqlQuery &query); ///查询黑名单
    bool queryActorBlack(const PagingQueryLimitArgu &limitArg, QSqlQuery &query); ///
    bool queryMediaBlackSearch(const QString argu, QSqlQuery &query);
    bool queryActorBlackSearch(const QString argu, QSqlQuery &query);

    bool querySongOrSingerSearch(const QString argu, QSqlQuery &query);
    bool querySingerSearch(const QString &name, QSqlQuery &query);//歌星名或拼音
    bool querySongSearch(const QString &name, QSqlQuery &query);
    bool querySongSearch_serial_id(qint64 serial_id, QSqlQuery &query);
    bool querySingerSearch_serial_id(qint64 serial_id, QSqlQuery &query);

    bool queryFMSongList(QSqlQuery &query);
    bool queryFMSongListDetail(const qint64 &lid, QSqlQuery &query);    

    bool queryCountListMedia(const QString type, qint64 &count);
    bool queryCountListHot(const QString type, qint64 &count);
    bool queryCOuntListNet(const QString type, qint64 &count);
    bool queryCountMedia_M(const MediaPagingQuery &argu, qint64 &count);
    bool queryCountTotal_M(qint64 &count);
    bool queryCountEnabled_M(qint64 &count);
    bool queryCountDisabled_M(qint64 &count);
    bool queryCountIsMatch_M(qint64 &count);
    bool queryCountBlack_M(qint64 &count);

    bool queryCountLanguage_M(QSqlQuery &query);
    bool queryCountType_M(QSqlQuery &query);
    bool queryCountVersion_M(QSqlQuery &query);
    bool queryCountEffect_M(QSqlQuery &query);
    bool queryCountResolution_M(QSqlQuery &query);
    bool queryCountQuality_M(QSqlQuery &query);
    bool queryCountSource_M(QSqlQuery &query);
    bool queryCountRhythm_M(QSqlQuery &query);
    bool queryCountPitch_M(QSqlQuery &query);

    bool queryCountActor_A(const ActorPagingQuery &argu, qint64 &count);
    bool queryCountSinger_A(qint64 &count);
    bool queryCountEnabled_A(qint64 &count);
    bool queryCountDisable_A(qint64 &count);
    bool queryCountBlack_A(qint64 &count);
    bool queryCountSex_A(QSqlQuery &query);
    bool queryCountNation_A(QSqlQuery &query);

public:
    bool getSex(QMap<int, QString> &sex);
    bool getNation(QMap<int, QString> &nation);
    bool getMediaLanguage(QMap<int, QString> &mediaLanguage);
    bool getMediaType(QMap<int, QString> &mediaType);
    bool getMediaVersion(QMap<int, QString> &mediaVer);
    bool getMediaEffect(QMap<int, QString> &mediaEff); //音效
    bool getMediaResolution(QMap<int, QString> &mediaRes); //分辨率
    bool getMediaQuality(QMap<int, QString> &mediaQua);   //音质
    bool getMediaSource(QMap<int, QString> &mediaSou); //来源
    bool getMediaRthym(QMap<int, QString> &mediaRth); //节奏
    bool getMediaPitch(QMap<int, QString> &mediaPit); //音高
    bool getMidsOfSid(const qint64 &sid, QVector<qint64> &mids);

    bool getMediaListNet(QMap<int, QString> &listNet); //网络排行榜
    bool getMediaListHot(QMap<int, QString> &listHot); //热歌排行榜
    bool getMaxIndex(const QString &type, qint64 &maxIndex);
    bool getMaxMediaListIndex(qint64 &maxIndex);
    bool getMaxIndex_hotnet(const QString &id,  const QString &hotnet, qint64 &maxIndex);
    bool getMaxMediaListIndex_hotnet(const QString &hotnet, qint64 &maxIndex);
    bool getMediaList(const QString &type, QVector<qint64> &indexList);
    bool getMediaListType(QStringList &typeList);
    bool getMediaListHotNetType(QMap<int, QString> &type, const bool isHot = true);

    bool getFmLids(const qint64 &lid, QVector<qint64> &lids);
    bool getFmMaxLid(qint64 &maxLid);
    bool getFmMaxIndex(int &maxIndex);

    bool getActorSerial_id(const qint64 &sid, qint64 &serial_id);

public:   

    bool deleteActor(const qint64 &serial_id, const QString &actor);
    bool deleteMedia(const qint64 &serial_id, const QString &lyric, QString &path);

    bool deleteMuchActor(const QStringList &sidM);
    bool deleteMuchMedia(const QStringList &midM);    

    bool deleteFMSonglistDetail(const qint64 &lid, const MediaList &value, const qint64 &serial_id_lid);
    bool deleteFmSonglist(const qint64 &lid, const  QString &title, const qint64 &serial_id );



    qint64 isActorSerialId(qint64 serialid); // -1不存在 存在返回最大值
    qint64 isMediaSerialId(qint64 serialid);

    bool isSongOfSid(const int &sid_1);

public:
    bool updateActor(const qint64 &sid, const Actor &actor, const Actor &oldActor);
    bool updateMedia(const qint64 &mid, const Media &media, const Media &oldMedia);
    bool updateMediaBlack(const int &mid, int black);  // 0取消黑名单  非零 黑名单
    bool updateActorBlack(const int &sid, int black);
    bool updateMediaBlackMush(const QVector<qint64> &mids, int black);
    bool updateActorBlackMush(const QVector<qint64> &sids, int black);

    bool updateMatchMusic(const int &mid, int isMatch);

    bool updateMoveFmLid(const qint64 &upLid, const qint64 &downLid, const qint64 &maxLid);
    bool updateFmLid(const SongList &value, const SongList &oldValue);
    bool updateFmDetail(const MediaList &value, const MediaList &conditiaon, const qint64 &serial_id_lid);

    bool updateMediaList(const MediaList &value, const MediaList &conditiaon, const QString &type = NULL);

    bool insertMedia(const Media &media);
    bool insertActor(const Actor &actor);
    bool insertFmDetail(const int &lid, const QStringList &value);
    bool insertFmDetail1(const qint64 &lid, const MediaList &value, const qint64 &serial_id_lid);
    bool insertFmLid(const SongList &value);    

    bool insertMediaListSongs(const int &index, const QString &detail);
    bool deleteMediaListSongs(const int &index, const QString &detail);
    bool updateMediaListSongs(const int &index, const QString &src, const QString &dest);
    bool isMediaListExistSongs(const int &index, const QString &detail);
    bool getSongsType(const int &index, QString &type);
    void getNameOrDetail(const int &index, QString &typeA);

    bool insertMediaListSinger(const QString &detail);
    bool deleteMediaListSinger(const QString &detail);
    bool updateMediaListSinger(const QString &src, const QString &dest);
    bool isMediaListExistSinger(const QString &detail);

    bool insertMediaListInfo(const int &index, const QString &detail);
    bool deleteMediaListInfo(const int &index, const QString &detail);
    bool updateMediaListInfo(const int &index, const QString &src, const QString &dest);
    bool isMediaListExistInfo(const int &index, const QString &detail);
    bool getInfoType(const int &index, QString &type);


    bool deleteMedialist(const MediaList &value);
    bool deleteMediaList_hotnet(const MediaList &value, QString listType = "");
    bool insertMediaList(const QString &type, const QStringList &value, QList<MediaList> medias);
    bool insertMediaList_hotnet(const QString &type, const int &id, const QStringList &value);

    bool addMediaList(const QString &, const QStringList &value, QList<MediaList> medias);
    bool addMediaList_hotnet(const QString &hotnet, const QString &, const QStringList &value);
    bool replaceMediaList(int srcMid, int srcIndex,  int destMid, QString type, QString serial_id, QString hotnet = NULL);

private:
    QString getQueryStr(const QString argu, const PagingQueryLimitArgu &limitArg, QString type = NULL);
    QString getQueryStr(const QString argu);


    void JsonFile(const QJsonObject &json);

public:
    QString hostName;
    QString port;
    QString databaseName;
    QString userName;
    QString password;
    QString dataBase;

private:

public:
    QSqlDatabase db;
    QSettings *initConfig;
    QSqlQuery *_query;
};

//    QString getHotNetQueryStr(const QString argu, const PagingQueryLimitArgu &limitArg);

    ///未使用
//    bool updateFmMediaListUpDownMove(const qint64 &lid, const qint64 &index, const qint64 &mid);
//    bool addMediaList(QString &typeStr, qint64 &maxIndex, QList<qint64> &mids);
#endif // MYSQLQUERY_H
