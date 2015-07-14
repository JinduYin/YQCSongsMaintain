#include "releasedialog.h"
#include <QDir>
#include <QFile>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QPainter>
#include <QDateTime>
#include <QDateEdit>
#include <QStyleOption>
#include <QCalendarWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
//#include <QJsonParseError>
#include <QCoreApplication>
#include <QFileInfoList>
#include <QTextCodec>
#include <QProgressBar>
#include <QProgressDialog>

#include "zlib128-dll/ZLib/ScopeGuard.h"
extern "C"{
#include "curlupload.h"
#include "zlib.h"
#include "zip.h"
}

#define ZLIB_WINAPI

#define FM_TYPE_IMAGE "fm"
#define ACTOR_TYPE_IMAGE "avatar"
#define MP4_TYPE "mp4"
#define LYRIC_TYPE "lyric"

#define WRITEBUFFERSIZE (16384)
#define MAXFILENAME (256)

#define FOPEN_FUNC(filename, mode) fopen64(filename, mode)
#define FTELLO_FUNC(stream) ftello64(stream)
#define FSEEKO_FUNC(stream, offset, origin) fseeko64(stream, offset, origin)

enum json_type{

    other = 0,
    songlist_detail = 1,
    media_list = 2,
    media = 100,
    actor = 101,
    songlist = 102
};

#define ZIP_GPBF_LANGUAGE_ENCODING_FLAG 0x800


ReleaseDialog::ReleaseDialog(QWidget *parent)
    : DropShadowWidget(parent)
{
    initWidget();
    initWidgetValue();

    setTitle("发布版本");
    calendarStart->setHidden(true);
    calendarEnd->setHidden(true);

    currentDate = QDateTime::currentDateTime();
    QDateTime defaultS = currentDate.addDays(-1);
    start_time->setDateTime(defaultS);
    end_time->setDateTime(currentDate);

    lineedit_start->setHidden(true);
    lineedit_end->setHidden(true);


    connect(pb_close, &QPushButton::clicked, this, &ReleaseDialog::close);
    connect(pushbutton_start, &QPushButton::clicked, this, &ReleaseDialog::calendar_start_clicked);
    connect(pushbutton_end, &QPushButton::clicked, this, &ReleaseDialog::calendar_end_clicked);
    connect(calendarStart, &QCalendarWidget::selectionChanged, this, &ReleaseDialog::setStartDateTime);
    connect(calendarEnd, &QCalendarWidget::selectionChanged, this, &ReleaseDialog::setEndDateTime);

    connect(pb_release, &QPushButton::clicked, this, &ReleaseDialog::release);


    bar = new QProgressBar(this);
//    bar->setBaseSize(80, 30);
    bar->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);      
}

ReleaseDialog::~ReleaseDialog()
{

}

void ReleaseDialog::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

//    QRect rect  = this->geometry();
//    QPainter painter(this);
//    painter.setRenderHint(QPainter::Antialiasing, true);
////    painter.setPen(QPen(Qt::red, Qt::SolidLine));
//    painter.setBrush(QBrush(Qt::red, Qt::SolidPattern));
//    painter.drawRect(rect);
}

void ReleaseDialog::initWidget()
{
    widgetTitle = new QWidget(this);
    widgetCenter = new QWidget(this);

    start_time = new QDateEdit(this);
    end_time = new QDateEdit(this);

    label_title = new QLabel(widgetTitle);
    lineedit_start = new QLineEdit(this);
    lineedit_end = new QLineEdit(this);

    lineedit_pwd = new QLineEdit(this);
    lineedit_name = new QLineEdit(this);

    pb_close = new QPushButton(widgetTitle);
    pb_release = new QPushButton(this);
    pushbutton_start = new QPushButton(lineedit_start);
    pushbutton_end = new QPushButton(lineedit_end);
    calendarStart = new QCalendarWidget(this);
    calendarEnd = new QCalendarWidget(this);

    calendarStart->resize(180, 110);
    calendarEnd->resize(180, 110);

    QHBoxLayout *title_layout = new QHBoxLayout();
    title_layout->addWidget(label_title);
    title_layout->addStretch();
    title_layout->addWidget(pb_close);
    title_layout->setContentsMargins(20, 0, 20, 0);
    title_layout->setSpacing(0);
    widgetTitle->setLayout(title_layout);

    QHBoxLayout *yes_layout = new QHBoxLayout();
    yes_layout->addStretch();
    yes_layout->addWidget(pb_release);
    yes_layout->addStretch();
    yes_layout->setMargin(0);
    yes_layout->setSpacing(0);

    QVBoxLayout *bottom_layout = new QVBoxLayout();
    bottom_layout->addWidget(start_time);
    bottom_layout->addWidget(end_time);
    bottom_layout->addWidget(lineedit_pwd);
    bottom_layout->addWidget(lineedit_name);
    bottom_layout->addLayout(yes_layout);
    bottom_layout->setContentsMargins(20, 10, 20, 10);
    bottom_layout->setSpacing(10);
    widgetCenter->setLayout(bottom_layout);

    QVBoxLayout *vLayout = new QVBoxLayout();
    vLayout->addWidget(widgetTitle);
    vLayout->addWidget(widgetCenter);
    vLayout->setMargin(0);
    vLayout->setSpacing(0);

    this->setLayout(vLayout);
}

void ReleaseDialog::initWidgetValue()
{
    QFile qss(":/qss/title.qss");
    qss.open(QFile::ReadOnly);
    this->setStyleSheet(qss.readAll());
    qss.close();


    widgetTitle->setFixedHeight(50);
    lineedit_start->setPlaceholderText("开始日期");
    lineedit_end->setPlaceholderText("结束日期");
    lineedit_pwd->setPlaceholderText("加密密码");
    lineedit_pwd->setEchoMode(QLineEdit::Password);
    lineedit_name->setPlaceholderText("版本信息");
    pb_release->setText("确定");

    lineedit_name->setFixedSize(180, 36);
    lineedit_pwd->setFixedSize(180, 36);
    lineedit_start->setFixedSize(180, 36);
    lineedit_end->setFixedSize(180, 36);
    start_time->setFixedSize(180, 36);
    end_time->setFixedSize(180, 36);

    pb_close->setFixedSize(14, 14);
    pb_release->setFixedSize(90, 36);

    this->setObjectName("WidgetCenter");
    widgetTitle->setObjectName("TitleWidget");
    label_title->setObjectName("TitleLabel");
    pb_release->setObjectName("Button");
    pb_close->setObjectName("CloseButton");


    lineedit_name->setObjectName("LineEdit");
    lineedit_pwd->setObjectName("LineEdit");
    lineedit_start->setObjectName("LineEdit");
    lineedit_end->setObjectName("LineEdit");
    pushbutton_start->setObjectName("CalendarButton");
    pushbutton_end->setObjectName("CalendarButton");
    QRect sCalendar = lineedit_start->geometry();
    QRect eCalendar = lineedit_end->geometry();
    lineedit_start->setTextMargins(0, 0, 20, 0);
    pushbutton_start->setGeometry(sCalendar.width()-25, 10, 20, 20);
    pushbutton_start->setCursor(Qt::PointingHandCursor);
    lineedit_end->setTextMargins(0, 0, 20, 0);
    pushbutton_end->setGeometry(eCalendar.width()-25, 10, 20, 20);
    pushbutton_end->setCursor(Qt::PointingHandCursor);

    pushbutton_start->setCheckable(true);
    pushbutton_end->setCheckable(true);
}

void ReleaseDialog::setTitle(const QString &str)
{
    label_title->setText(str);
}

void ReleaseDialog::release()
{
    QString pwd = lineedit_pwd->text();
    QString name = lineedit_name->text();
    if(pwd.isEmpty() || name.isEmpty() || name.size() > 16)
    {
        QString prompt;
        prompt = QString("必须设置加密密码\n填写版本信息。");
        if(name.size() > 16)
            prompt = QString("版本信息不能超过16个字符。");
        QMessageBox box(QMessageBox::Information, "提示", prompt);
        box.setStandardButtons(QMessageBox::Ok);
        box.setButtonText(QMessageBox::Ok, "确定");
        box.exec();
        return;
    }

    ////name 最大16个字符



    if(!setFilePath())
        return;

    QDateTime start,end;
    getDateTime(start, end);
    QString jsonfilePath = getReadFilePath(start, end);

    ///读JSON下载资源
    readJsonFile(jsonfilePath);

    ///打包
    QStringList fileNames = getCurrentDirFiles(releasePath);
    QString destPath  = QCoreApplication::applicationDirPath();
    destPath.append("/ZIP/");
    QDir dir(destPath);
    if(!dir.exists())
        dir.mkpath(destPath);
    QString destName = currentDate.toString("yyyy-MM-dd_hh_mm_ss");
    destName.append(".zip");
    destPath.append(destName);

    QFile destFile(destPath);
    if(destFile.exists())
    {
    }

    zipFile zf;
    QByteArray dest = destPath.toLocal8Bit();
    zf = zipOpen(dest.data(), APPEND_STATUS_CREATE);


    if (zf == NULL)
    {
        return;
    }

//   LOKI_ON_BLOCK_EXIT(zipClose, zf, (const char *)NULL);
   for (int i=0; i<fileNames.size(); i++)
   {
       QString tempStr = fileNames.at(i);
       QString path = releasePath;
       path.remove("music");
       QString temprel = path;
       QString deststr = tempStr.remove(temprel);
       if (!ZipAddFile(zf, deststr, fileNames.at(i),  pwd,  true)) //"default_yqc"
       {
           continue;
       }
   }

   int errclose = zipClose(zf, NULL);
   if (errclose != ZIP_OK)
       qDebug() << " zipClose ret : " << errclose;

   ///上传打包文件
   QString url;
   CurlUpload *curlUpload = new CurlUpload();
   bool ok = curlUpload->uploadYQDyun(destName, destPath, url);

   qDebug() << " upload yun : ok : " << ok;
   qDebug() << " zip name " << destName;
   qDebug() << " url " << url;
   /// post 表格数据
   QDateTime time = QDateTime::currentDateTime();
   QString timeStr = time.toString("yyyy-MM-dd-hh-mm-ss");
   int version = time.toTime_t();
   QString postStr = QString("name=%1&url=%2&time=%3&remark=%4&version=%5")
                            .arg(name)
                            .arg(url)
                            .arg(timeStr)
                            .arg(pwd)
                            .arg(version);


   CurlUpload *curlDownlaod = new CurlUpload();
   curlDownlaod->postJson(postStr);

   return;
}

void ReleaseDialog::getDateTime(QDateTime &start, QDateTime &end)
{
    start = start_time->dateTime();
    end = end_time->dateTime();

    if (start > end)
    {
        QMessageBox::information(this, "日期错误", "开始时间不能大于结束日期.");
    }

    if (start > currentDate)
    {
        QMessageBox::information(this, "日期错误", "开始时间不能大于当前日期.");
    }
}

QString ReleaseDialog::getReadFilePath(QDateTime &start, QDateTime &end)
{        
    QString path = QCoreApplication::applicationDirPath();
    QString readjsonPath = path;
    readjsonPath.append("/JSON/");

    QString destPath = jsonPath;
    destPath.append("sql.json");

    QFile sqlFile(destPath);
    if(sqlFile.exists())
        sqlFile.remove();

    bool res = true;
    if(sqlFile.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        while(res)
        {
            QString tempPath = readjsonPath;
            tempPath.append("/");
            tempPath.append(start.toString("yyyy-MM-dd"));
            tempPath.append(".json");

            QFile file(tempPath);
            if(file.exists())
            {
                if(file.open(QIODevice::ReadOnly))
                {
                    sqlFile.write(file.readAll());
                    sqlFile.write("\r\n");
                }
                file.close();
            }

            start = start.addDays(1);
            if(start > end || start > currentDate)
                res = false;
        }
    }

    sqlFile.close();
    return destPath;
}

void ReleaseDialog::readJsonFile(const QString &path)
{
    if(path.isEmpty())
        return;
    QFile file(path);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return;
    }

    QString text;    
    QTextStream in(&file);
    while(!in.atEnd()){
        text = in.readLine();
        if(!text.isEmpty()){
            text.remove(text.size()-1, 1);

            downloadFiles(text);
        }
    }    
    file.close();
}

void ReleaseDialog::downloadFiles(const QString json)
{
    QByteArray byte_array = json.toLocal8Bit();
    QJsonParseError json_error;
    QJsonDocument parse_doucment = QJsonDocument::fromJson(byte_array, &json_error);
    if(json_error.error == QJsonParseError::NoError)
    {
        if(!parse_doucment.isObject())
            return;
        QJsonObject json = parse_doucment.object();
        if(json.contains("type"))
        {
            QJsonValue type_value = json.take("type");
            int type = type_value.toInt();

            QString op;
            QJsonValue op_value = json.take("op");
            if(!op_value.isNull())
                op = op_value.toString();

            if(type ==  songlist_detail)  ///songlist_detail
            {
                if(op.compare("insert") == 0)
                {

                }
                else if(op.compare("update") == 0)
                {

                }
                else if(op.compare("delete") == 0)
                {

                }
            }
            else if(type == media_list) ///media_list
            {
                if(op.compare("insert") == 0 )
                {
                   QJsonValue serial_id_value = json.take("name");
//                       qint64 serial_id = serial_id_value.toVariant().toLongLong();
                }
                else if(op.compare("update") == 0)
                {

                }
                else if(op.compare("delete") == 0)
                {

                }
            }
            else if(type == media) ////media
            {
                if(op.compare("insert") == 0)
                {
                   QString lyric = json.take("lyric").toString();
                   QString path = json.take("path").toString();
                   downloadVideoLyric(LYRIC_TYPE, lyric);
                   downloadVideoLyric(MP4_TYPE, path);
                }
                else if(op.compare("delete") == 0)
                {

                }
                else if(op.compare("update") == 0)
                {
                    QString old_lyric = json.take("old_lyric").toString();
                    QString new_lyric = json.take("new_lyric").toString();
                    QString old_path = json.take("old_path").toString();
                    QString new_path = json.take("new_path").toString();

                    if(old_lyric.compare(new_lyric) != 0)
                        downloadVideoLyric(LYRIC_TYPE, new_lyric);
                    if(old_path.compare(new_path) != 0)
                        downloadVideoLyric(MP4_TYPE, new_path);
                }
            }
            else if(type == actor) ///
            {
                if(op.compare("insert") == 0)
                {
                   QString name = json.take("name").toString();
                   downloadImageFile(ACTOR_TYPE_IMAGE, name);
                }
                else if(op.compare("delete") == 0)
                {

                }
                else if(op.compare("update") == 0)
                {
                    QString old_name = json.take("old_name").toString();
                    QString new_name = json.take("new_name").toString();
                    if(old_name.compare(new_name) != 0)
                        downloadImageFile(ACTOR_TYPE_IMAGE, new_name);
                }
            }
            else if(type == songlist)
            {
                if(op.compare("insert") == 0)
                {
                   QString title = json.take("title").toString();
                   downloadImageFile(FM_TYPE_IMAGE, title);
                }
                else if(op.compare("delete") == 0)
                {

                }
                else if(op.compare("update") == 0)
                {
                    QString old_title = json.take("old_title").toString();
                    QString new_title = json.take("new_title").toString();
                    if(old_title.compare(new_title) != 0)
                        downloadImageFile(FM_TYPE_IMAGE, new_title);
                }
            }
            else if(type == other)
            {
                return ;
            }
        }
    }
}

void ReleaseDialog::downloadImageFile(const QString &type, const QString &name)
{
    CurlUpload *curlDownlaod = new CurlUpload();
    QString filePath;
    if(type.compare(ACTOR_TYPE_IMAGE) == 0)
        filePath = avatarPath;
    if(type.compare(FM_TYPE_IMAGE) == 0)
        filePath = fmPath;
    filePath.append(name);
    filePath.append(".jpg");

    QFile file(filePath);
    if(!file.exists())
    {
        curlDownlaod->download_jsonIm(type, name, filePath);
    }

    delete curlDownlaod;
}

void ReleaseDialog::downloadVideoLyric(const QString &type, const QString &path)
{
    CurlUpload *curlDownlaod = new CurlUpload();
    QString filePath;
    if(type.compare(MP4_TYPE) == 0)
        filePath = mp4Path;
    if(type.compare(LYRIC_TYPE) == 0)
        filePath = lyricPath;

    QStringList namelist = path.split("/");
    if(namelist.size() > 1)
    {
        QString tempPath = path;
        tempPath.remove(namelist.last());
        filePath.append(QString("/%1").arg(tempPath));
        QDir dir(filePath);
        if(!dir.exists())
            dir.mkpath(filePath);

    }
    filePath.append("/");
    filePath.append(namelist.last());


//    filePath.append(path);
    QFile file(filePath);
    if(!file.exists())
    {
        curlDownlaod->download_jsonVi(path, filePath);
    }

    delete curlDownlaod;
}

QStringList ReleaseDialog::getCurrentDirFiles(const QString &path)
{   
    QStringList list;
    QFileInfo info(path);
    if(info.isFile())
    {
        list.append(path);
        return list;
    }

    if(info.isDir())
    {
        QDir dir(path);
        dir.setFilter(QDir::AllDirs | QDir::NoDotAndDotDot | QDir::Files);
        QFileInfoList dirlist = dir.entryInfoList();

        if(dirlist.size() <= 0)
        {
//            list.append(path);
//            list.append("/");
        }
        else
        {
            for (int i=0; i < dirlist.size(); i++){

                QStringList tempList = getCurrentDirFiles(dirlist.at(i).filePath());
                list.append(tempList);
            }
        }
    }
    return list;
}

bool ReleaseDialog::ZipAddFile(zipFile zf, QString lpszFileNameInZip, QString lpszFilePath, QString password, bool bUtf8)
{
    zip_fileinfo FileInfo;
    ZeroMemory(&FileInfo, sizeof(FileInfo));

    QTextCodec *codec = QTextCodec::codecForName("GBK");
    QByteArray nameInZip = codec->fromUnicode(lpszFileNameInZip); ///gbk
//    QByteArray nameInZip = lpszFileNameInZip.toLocal8Bit();  ///utf-8
    QByteArray pwd = password.toLocal8Bit();
    if (bUtf8)
    {
        if (zipOpenNewFileInZip4(zf, nameInZip.data(), &FileInfo, NULL, 0, NULL, 0, NULL, Z_DEFLATED, 9,
                                 0, -MAX_WBITS, DEF_MEM_LEVEL, Z_DEFAULT_STRATEGY, pwd.data(), 0, 0, ZIP_GPBF_LANGUAGE_ENCODING_FLAG) != ZIP_OK)
        {
            return FALSE;
        }
    }
    else
    {
//        QTextCodec *codec = QTextCodec::codecForName("GBK");
//        QByteArray nameInZip = codec->fromUnicode(lpszFileNameInZip);
        if (zipOpenNewFileInZip(zf, nameInZip.data(), &FileInfo, NULL, 0, pwd.data(), 0, NULL, Z_DEFLATED, 9) != ZIP_OK)
        {
            return FALSE;
        }
    }

    LOKI_ON_BLOCK_EXIT(zipCloseFileInZip, zf);
    const qint64 BUFFER_SIZE = 4096;
    char *buffer = new char[BUFFER_SIZE];

    QFile file(lpszFilePath);
    if(!file.open(QIODevice::ReadOnly))
        return false;
    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_5_4);
    qint64 size = file.size();

    bar->setHidden(false);
    bar->setRange(0, size);
    bar->setValue(0);    

    qint64 readCount = 0;
    qint64 index = size;
    qint64 total = 0;
    while (index > 0)
    {
        qint64 dwSizeToRead = index > BUFFER_SIZE ? BUFFER_SIZE : (size-total);

        memset(buffer,0,sizeof(char)*BUFFER_SIZE);

        readCount = in.readRawData(buffer, dwSizeToRead);
        if (zipWriteInFileInZip(zf, buffer, readCount))
        {
            return FALSE;
        }

        total += readCount;
        index -= readCount;
        file.seek(total);

        bar->setValue(total);
    }


    bar->setHidden(true);

    delete []buffer;
    file.close();
    return TRUE;
}

bool ReleaseDialog::setFilePath()
{
    QString path = QCoreApplication::applicationDirPath();
    releasePath = path;
    releasePath.append(QString("/%1/music").arg(currentDate.toString("yyyy-MM-dd")));

    QDir dateDir(releasePath);
    if(dateDir.exists())
    {
//        QString mkPath = releasePath;
//        mkPath.remove("music");
//        QString title("文件重复");
//        QString content = QString("文件：%1 \n"
//                                  "已经存在，是否覆盖？").arg(mkPath);
//        QMessageBox box(QMessageBox::Warning, title, content);
//        box.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
//        box.setButtonText(QMessageBox::Ok, "确定");
//        box.setButtonText(QMessageBox::Cancel, "取消");

//        if(box.exec() == QMessageBox::Cancel)
//        {
//            return false;
//        }
    }
    else
        dateDir.mkpath(releasePath);

    jsonPath = releasePath;
    jsonPath.append("/json/");

    avatarPath = releasePath;
    avatarPath.append("/avatar/");

    fmPath = releasePath;
    fmPath.append("/fm/");

    mp4Path = releasePath;
    mp4Path.append("/mp4/");

    lyricPath = releasePath;
    lyricPath.append("/lyric/");

    QDir dir(jsonPath);
    if(!dir.exists())
    {
        dir.mkpath(jsonPath);
    }

    dir.setPath(avatarPath);
    if(!dir.exists())
        dir.mkpath(avatarPath);

    dir.setPath(fmPath);
    if(!dir.exists())
        dir.mkpath(fmPath);

    dir.setPath(mp4Path);
    if(!dir.exists())
        dir.mkpath(mp4Path);

    dir.setPath(lyricPath);
    if(!dir.exists())
        dir.mkpath(lyricPath);

    return true;
}

void ReleaseDialog::calendar_start_clicked(bool checked)
{
    QRect rect; // = calendarStart->geometry();
    QPoint point = QCursor::pos();

    rect.setX(point.x());
    rect.setY(point.y());

    calendarStart->setGeometry(point.x() - 180, point.y() + 50, 180, 110);

    if(checked){
        calendarStart->setHidden(false);
        calendarStart->setFocus();
    }else{
        calendarStart->setHidden(true);
    }
}

void ReleaseDialog::calendar_end_clicked(bool checked)
{
    if(checked){
        calendarEnd->setHidden(false);
        calendarEnd->setFocus();
    }else{
        calendarEnd->setHidden(true);
    }
}

void ReleaseDialog::setStartDateTime()
{
    QString date = calendarStart->selectedDate().toString("yyyy-MM-dd");
    lineedit_start->setText(date);
}

void ReleaseDialog::setEndDateTime()
{
    QString date = calendarEnd->selectedDate().toString("yyyy-MM-dd");
    lineedit_end->setText(date);
}


//QString title("文件重复");
//QString content = QString("文件：%1 \n"
//                          "已经存在，是否覆盖？").arg(destName);
//QMessageBox box(QMessageBox::Warning, title, content);
//box.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
//box.setButtonText(QMessageBox::Ok, "确定");
//box.setButtonText(QMessageBox::Cancel, "取消");

//if(box.exec() == QMessageBox::Cancel)
//{
//    return;
//}
