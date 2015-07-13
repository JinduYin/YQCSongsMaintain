#ifndef CURLUPLOAD_H
#define CURLUPLOAD_H
#include <iostream>
extern "C"{
#include "curl/curl.h"
}
class QString;
class QPixmap;
class QByteArray;
class CurlUpload
{
public:
    CurlUpload();
    ~CurlUpload();

public:
    bool downloadActorImage( QString actorName, QString filePath);
    bool download_fmImage(const QString titleName, QString &savPath);

    bool download_jsonIm(const QString &type, const QString &name, QString &savePath);
    bool download_jsonVi(const QString &urlPath, QString &savePath);

    bool uploadActorImage(const char *fileName, const char *filePath);
    QString uploadActorImage(const QString &filePath);
    QString uploadFmImage(const QString &filePath);
    QString uploadMediaVideo(const QString videoPath);
    QString uploadMedialyric(const QString lyricPath);

    QString postJson(QString json);

    bool uploadYQDyun(const QString &filename , const QString &localpath);

private:
    QString getImgPath(QString filename);
    QString getUrl(QString filename);

    CURLcode download_image( QString url,  QString save_path);
    CURLcode download_image(const char *url, const char *save_path, const char *file_name);


    int uploadFile(const char *url,
                   const char *type,
                   const char *filename,
                   const char *filepath
                   );
    int uploadFile(QByteArray &url,
                   QByteArray &type,
                   QByteArray &fileName,
                   QByteArray &filePath
                   );
};

#endif // CURLUPLOAD_H
