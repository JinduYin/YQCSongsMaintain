#include "fmaddmodifydialog.h"
#include "pagingtableview.h"
#include "tablemodel.h"
#include "enuminfo.h"
#include <QFile>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QPainter>
#include <QFileDialog>
#include <QStyleOption>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QDebug>
FmAddModifyDialog::FmAddModifyDialog(QWidget *parent)
    : DropShadowWidget(parent)
{
    setFixedHeight(650);
    setFixedWidth(900);

    _sql = NULL;
    imagePath = "";  
    fmState  = -1;
    _widItem = -1;
    replaceRow = -1;
    _type = "";
    replaceFalg = false;

    initWidget();
    initWidgetValue();
    lineEdit_search->setEnabled(false);
    label_image->setScaledContents(true);
    pushButton_addMusic->setCheckable(true);    
    connect(pushButton_close, &QPushButton::clicked, this, &FmAddModifyDialog::close_dialog);
    connect(pushButton_addMusic, &QPushButton::clicked, this, &FmAddModifyDialog::addMusic);

    connect(view_music, &PagingTableView::currentRow, this, &FmAddModifyDialog::deleteMusic);
    connect(view_music, &PagingTableView::moveUp, this, &FmAddModifyDialog::moveUp);
    connect(view_music, &PagingTableView::moveDown, this, &FmAddModifyDialog::moveDown);
    connect(view_music, &PagingTableView::replace, this, &FmAddModifyDialog::replace);
    connect(view_addMusic, &PagingTableView::currentRow, this, &FmAddModifyDialog::addMusicDetail);

    connect(pushButton_upload, &QPushButton::clicked, this, &FmAddModifyDialog::uploadImage);
    connect(pushButton_search, &QPushButton::clicked, this, &FmAddModifyDialog::serachMusic);
    connect(pushButton_preview, &QPushButton::clicked, this, &FmAddModifyDialog::previewImage);
    connect(pushButton_save, &QPushButton::clicked, this, &FmAddModifyDialog::save);
    connect(view_addMusic, &PagingTableView::play, this, &FmAddModifyDialog::playAddMusic);
    connect(view_music, &PagingTableView::play, this, &FmAddModifyDialog::play);
}

FmAddModifyDialog::~FmAddModifyDialog()
{

}

void FmAddModifyDialog::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void FmAddModifyDialog::initWidget()
{
    widgetTitle = new QWidget(this);
    widgetImage = new QWidget(this);
    widgetAddMusic = new QWidget(this);

    label_title = new QLabel(widgetTitle);
    label_listName = new QLabel(this);
    label_listImage = new QLabel(this);
    label_music = new QLabel(this);
    label_image = new QLabel(widgetImage);

    lineEdit_listName = new QLineEdit(this);
    lineEdit_listImage = new QLineEdit(widgetImage);
    lineEdit_search = new QLineEdit(this);

    pushButton_close = new QPushButton(widgetTitle);
    pushButton_preview = new QPushButton(widgetImage);
    pushButton_upload = new QPushButton(widgetImage);
    pushButton_addMusic = new QPushButton(this);
    pushButton_save = new QPushButton(this);
    pushButton_search = new QPushButton(lineEdit_search);

    view_addMusic = new PagingTableView(widgetAddMusic);
    view_music = new PagingTableView(this);

    QHBoxLayout *title_layout = new QHBoxLayout();
    title_layout->addWidget(label_title);
    title_layout->addStretch();
    title_layout->addWidget(pushButton_close);
    title_layout->setContentsMargins(20, 0, 20, 0);
    title_layout->setSpacing(0);

    widgetTitle->setLayout(title_layout);

    QHBoxLayout *addMusic_button_layout = new QHBoxLayout();
    addMusic_button_layout->addWidget(lineEdit_search);
    addMusic_button_layout->addWidget(pushButton_addMusic);
    addMusic_button_layout->setMargin(0);
    addMusic_button_layout->setSpacing(10);

    QHBoxLayout *list_layout = new QHBoxLayout();
    list_layout->addWidget(label_listName);
    list_layout->addWidget(lineEdit_listName);
    list_layout->addStretch();
    list_layout->addLayout(addMusic_button_layout);
    list_layout->setContentsMargins(12, 10, 58, 0);
    list_layout->setSpacing(0);

    QHBoxLayout *upload_layout = new QHBoxLayout();
    upload_layout->addWidget(lineEdit_listImage);
    upload_layout->addWidget(pushButton_preview);
    upload_layout->addWidget(pushButton_upload);
    upload_layout->setContentsMargins(0, 0, 0, 0);
    upload_layout->setSpacing(10);

    QHBoxLayout *image_layout = new QHBoxLayout();
    image_layout->addWidget(label_image);
    image_layout->addStretch();
    image_layout->setContentsMargins(0, 10, 0, 0);
    image_layout->setSpacing(0);

    QVBoxLayout *upload_image_layout = new QVBoxLayout();
    upload_image_layout->addLayout(upload_layout);
    upload_image_layout->addLayout(image_layout);
    upload_image_layout->setMargin(0);
    upload_image_layout->setSpacing(10);

    widgetImage->setLayout(upload_image_layout);

    QHBoxLayout *addMusic_layout = new QHBoxLayout();
    addMusic_layout->addWidget(view_addMusic);
    addMusic_layout->setMargin(0);
    addMusic_layout->setSpacing(0);
    widgetAddMusic->setLayout(addMusic_layout);


    QHBoxLayout *listImage_layout = new QHBoxLayout();
    listImage_layout->addWidget(label_listImage, 0, Qt::AlignTop);
    listImage_layout->addWidget(widgetImage, 0, Qt::AlignLeft);
    listImage_layout->addWidget(widgetAddMusic, 0, Qt::AlignLeft);
    listImage_layout->setContentsMargins(12, 8, 20, 0);
    listImage_layout->setSpacing(0);

    QVBoxLayout *music_layout = new QVBoxLayout();
    music_layout->addWidget(label_music);
    music_layout->addWidget(view_music);
    music_layout->setContentsMargins(20, 10, 20, 0);

    QHBoxLayout *save_layout = new QHBoxLayout();
    save_layout->addStretch();
    save_layout->addWidget(pushButton_save);
    save_layout->addStretch();
    save_layout->setContentsMargins(0, 10, 0, 10);

    QVBoxLayout *vLayout = new QVBoxLayout();

    vLayout->addWidget(widgetTitle);
    vLayout->addLayout(list_layout);
    vLayout->addLayout(listImage_layout);
    vLayout->addLayout(music_layout);
    vLayout->addLayout(save_layout);
    vLayout->setContentsMargins(0, 0, 0, 0);
    vLayout->setSpacing(0);

    this->setLayout(vLayout);
}

void FmAddModifyDialog::initWidgetValue()
{
    QFile qss(":/qss/title.qss");
    qss.open(QFile::ReadOnly);
    this->setStyleSheet(qss.readAll());
    qss.close();

    label_title->setText("新建歌单");
    label_listName->setText("歌单名称");
    label_listImage->setText("歌单封面");
    label_music->setText("已选歌曲");

    pushButton_addMusic->setText("添加歌曲");
    pushButton_preview->setText("浏览");
    pushButton_upload->setText("上传");
    pushButton_save->setText("保存");

    lineEdit_search->setPlaceholderText("输入歌星/歌曲名字");

    widgetTitle->setFixedHeight(33);
    widgetImage->setFixedWidth(250);

    label_listName->setFixedWidth(60);
    label_listImage->setFixedWidth(60);
    label_music->setFixedWidth(60);

    label_listName->setFixedHeight(24);
    label_listImage->setFixedHeight(24);
    label_music->setFixedHeight(24);

    label_image->setFixedHeight(188);
    label_image->setFixedWidth(188);

    lineEdit_listName->setFixedWidth(250);
    lineEdit_listImage->setFixedWidth(150);
    lineEdit_search->setFixedWidth(260);
    lineEdit_listName->setFixedHeight(24);
    lineEdit_listImage->setFixedHeight(24);
    lineEdit_search->setFixedHeight(24);

    pushButton_close->setFixedHeight(14);
    pushButton_close->setFixedWidth(14);
    pushButton_preview->setFixedHeight(24);
    pushButton_preview->setFixedWidth(40);
    pushButton_upload->setFixedHeight(24);
    pushButton_upload->setFixedWidth(40);

    pushButton_addMusic->setFixedWidth(60);
    pushButton_addMusic->setFixedHeight(24);
    pushButton_save->setFixedWidth(60);
    pushButton_save->setFixedHeight(24);

    this->setObjectName("WidgetCenter");
    widgetTitle->setObjectName("TitleWidget");
    label_title->setObjectName("TitleLabel");
    label_listName->setObjectName("Label");
    label_listImage->setObjectName("Label");
    label_music->setObjectName("Label");
//    label_image->setStyleSheet("background:rgb(250, 0, 0);");

    lineEdit_listImage->setObjectName("LineEdit");
    lineEdit_listName->setObjectName("LineEdit");
    lineEdit_search->setObjectName("LineEdit");

    pushButton_preview->setObjectName("Button");
    pushButton_upload->setObjectName("Button");
    pushButton_save->setObjectName("Button");
    pushButton_addMusic->setObjectName("Button");
    pushButton_search->setObjectName("SerachButton");
    pushButton_close->setObjectName("CloseButton");

    QRect rect = lineEdit_search->geometry();
    lineEdit_search->setTextMargins(0, 0, 20, 0);
    pushButton_search->setGeometry(rect.width()-25, 3, 20, 20);
    pushButton_search->setCursor(Qt::PointingHandCursor);

    widgetAddMusic->setHidden(true);
    view_addMusic->setWidgetBottomHidden();
    view_music->setWidgetBottomHidden();    
}

void FmAddModifyDialog::setTitle(const QString &str)
{
    label_title->setText(str);
}

void FmAddModifyDialog::close_dialog()
{
    emit update_view();
    this->close();
}

void FmAddModifyDialog::addMusic(bool checked)
{
    disconnect(view_addMusic, SIGNAL(currentRow(int)), 0, 0);
    connect(view_addMusic, &PagingTableView::currentRow, this, &FmAddModifyDialog::addMusicDetail);

    if(checked){
        widgetAddMusic->setHidden(false);
        widgetImage->setHidden(true);
        lineEdit_search->setEnabled(true);
        if(_widItem == widItem_FM)
            widgetAddMusic->setFixedWidth(view_music->geometry().width()
                                          - label_listImage->geometry().width());
        else
            widgetAddMusic->setFixedWidth(view_music->geometry().width());
    }else{
        widgetAddMusic->setHidden(true);
        widgetImage->setHidden(false);
        lineEdit_search->setEnabled(false);
    }
}

void FmAddModifyDialog::initSql(MysqlQuery *sql, QSqlQuery &query)
{
    if(!paths.isEmpty())
        paths.clear();
    if(!rowList.isEmpty())
        rowList.clear();
    _sql = sql;
    _query = query;
}

void FmAddModifyDialog::initType(const QString &type)
{
    _type = type;
}

void FmAddModifyDialog::setReplaceRow(const bool &rep, const int &row)
{
    replaceFalg = rep;
    replaceRow = row;
}

void FmAddModifyDialog::setFmState(const int &state)
{
    fmState = state;
}

void FmAddModifyDialog::setType_delegate(const int &item)
{
    _widItem = item;

    if(_widItem == widItem_FM){
        view_addMusic->setFmAddMusicDelegate("添加");
        view_music->setFmShowMusicDelegate();
    }else{

        view_addMusic->setFmAddMusicDelegate("添加");
        view_music->setFmAddMusicDelegate("取消");
    }
}

void FmAddModifyDialog::setFmViewValue()
{
    song_list.lid = _query.value("_lid").toString();
    song_list.title = _query.value("_title").toString();
    song_list.serial_id = _query.value("_serial_id").toString();

    lineEdit_listName->setText(_query.value("_title").toString());

    lid = _query.value("_lid").toInt();
    if(_sql->queryFMSongListDetail(_query.value("_lid").toLongLong(), _queryList)){
        view_music->showUploadData(_queryList, true);
//        view_music->getValue(rowList);
    }
}

void FmAddModifyDialog::setAdViewValue(const QString &type)
{
    _type = type;

    _query.clear();
    view_music->tableView->clear();
    if(!_sql->queryMediaList(type,  _query)) return;
    view_music->setTotal_Rows_Pages(_query.size());

    view_music->showUploadMediaListData(_query);
    view_music->getValue(rowList);
}

void FmAddModifyDialog::previewImage()
{
    QString fileFormat("图片文件(*.jpg)");
    QString pathStr = QFileDialog::getOpenFileName(this,
                                                tr("上传头像"),
                                                ".",
                                                fileFormat
                                                );
    if(pathStr.isEmpty())
        return;

    lineEdit_listImage->setText(pathStr);
    widgetImage->setHidden(false);
    widgetAddMusic->setHidden(true);
    label_image->setHidden(false);
    QPixmap pixmap(pathStr);
    label_image->setPixmap(pixmap);
}

void FmAddModifyDialog::uploadImage()
{
    QString path = lineEdit_listImage->text();
    CurlUpload *curlUpload = new CurlUpload();
    curlUpload->uploadFmImage(path);
}

void FmAddModifyDialog::deleteMusic(const int &row)
{
//    paths.removeAt(row);
//    rowList.removeAt(row);
//    view_music->setModelValue(rowList);

    _queryList.seek(row);

    qint64 lid = song_list.lid.toLongLong();
    qint64 serial_id_lid = song_list.serial_id.toLongLong();
    MediaList value;
    getMediaListValue(_queryList, value);
    if(_sql->deleteFMSonglistDetail(lid, value, serial_id_lid));
        setFmViewValue();
}

void FmAddModifyDialog::moveUp(const int &row)
{
//    if(row  <= 0)
//        return;

//    paths.swap(row, row-1);
//    rowList.swap(row, row-1);
//    view_music->setModelValue(rowList);



    if(row <= 0)
        return;

    _queryList.seek(row);

    MediaList ad, adPre;
    getMediaListValue(_queryList, ad);

    if(!_queryList.previous())
        return;
    getMediaListValue(_queryList, adPre);

    qint64 serial_id_lid = song_list.serial_id.toLongLong();
    if(_sql->updateFmDetail(ad, adPre, serial_id_lid)){
       if(_sql->updateFmDetail(adPre, ad, serial_id_lid));
       else
           _sql->updateFmDetail(ad, adPre, serial_id_lid);
    }

    setFmViewValue();
}

void FmAddModifyDialog::moveDown(const int &row)
{
//    if(row >= _queryList.size() - 1)
//        return;

//    paths.swap(row, row+1);
//    rowList.swap(row, row+1);
//    view_music->setModelValue(rowList);

    if(row >= _queryList.size() - 1)
        return;
    _queryList.seek(row);

    MediaList ad, adNext;
    getMediaListValue(_queryList, ad);

    if(!_queryList.next())
        return;
    getMediaListValue(_queryList, adNext);

    qint64 serial_id_lid = song_list.serial_id.toLongLong();
    if(_sql->updateFmDetail(ad, adNext, serial_id_lid)){
        if(_sql->updateFmDetail(adNext, ad, serial_id_lid));
        else
            _sql->updateFmDetail(ad, adNext, serial_id_lid);
    }

    setFmViewValue();
}

void FmAddModifyDialog::replace(const int &row)
{
    widgetAddMusic->setHidden(false);
    widgetImage->setHidden(true);
    lineEdit_search->setEnabled(true);
    if(_widItem == widItem_FM)
        widgetAddMusic->setFixedWidth(view_music->geometry().width()
                                      - label_listImage->geometry().width());

    replaceRow = row;
    disconnect(view_addMusic, SIGNAL(currentRow(int)), 0, 0);
    connect(view_addMusic, &PagingTableView::currentRow, this, &FmAddModifyDialog::replaceViewMusic);
}

void FmAddModifyDialog::replaceViewMusic(const int &row)
{
    MediaList value, conditiaon;
    _querySearch.seek(row);
    value.mid = _querySearch.value("_mid").toString();


    if(replaceRow == -1) return;

    _queryList.seek(replaceRow);
    getMediaListValue(_queryList, conditiaon);

    qint64 serial_id_lid = song_list.serial_id.toLongLong();
    _sql->updateFmDetail(value, conditiaon, serial_id_lid);
    setFmViewValue();

//    rowList.replace(replaceRow, tempValue);
//    view_music->setModelValue(rowList);
}

void FmAddModifyDialog::serachMusic()
{
    QString str = lineEdit_search->text();
    if(str.isEmpty())
        return;

    _querySearch.clear();
    if(_sql->querySongOrSingerSearch(str, _querySearch))
        view_addMusic->showUploadData(_querySearch, true);
}

void FmAddModifyDialog::getMusicDetail(QSqlQuery &querySearch, QStringList &tempValue)
{
    tempValue << querySearch.value("_mid").toString()
              << querySearch.value("_serial_id").toString()
              << querySearch.value("_name").toString()
              << querySearch.value("_singer").toString()
              << querySearch.value("_language").toString()
              << querySearch.value("_type").toString()
              << querySearch.value("_path").toString();
}

void FmAddModifyDialog::getMediaListValue(const QSqlQuery &_que, MediaList &_list)
{
    _list.type =   song_list.lid;
    _list.index = _que.value("_index").toString();
    _list.mid = _que.value("_mid").toString();
    _list.serial_id = _que.value("_serial_id").toString();
}

void FmAddModifyDialog::addMusicDetail(const int &row)
{
    _querySearch.seek(row);
    MediaList tempValue;
    getMediaListValue(_querySearch, tempValue);
//    if(replaceFalg == -1)
//    {
        qint64 lid = song_list.lid.toLongLong();
        qint64 serial_id_lid = song_list.serial_id.toLongLong();
        _sql->insertFmDetail1(lid, tempValue, serial_id_lid);
        setFmViewValue();

//    }

//    QString path = _querySearch.value("_path").toString();
//    if(replaceFalg){
//        if(rowList.isEmpty()){
//            paths.insert(0, path);
//            rowList.insert(0, tempValue);
//        }
//        else{
//            paths.replace(0, path);
//            rowList.replace(0, tempValue);
//        }
//    }else{
//        paths.append(path);
//        rowList.append(tempValue);
//    }
//    view_music->setModelValue(rowList);
}

void FmAddModifyDialog::save()
{
    qDebug() << " size : " << rowList.size();

    bool succ = false;

    if(_widItem == widItem_FM){

        if(fmState == fm_modify){
//            if(saveModityLid())
//                succ = saveMusic();
            succ = saveModityLid();
        }else if(fmState == fm_new){
//            if(saveNewLid())
//                succ = saveMusic();
            succ = saveNewLid();
        }
    }
//    else if(_widItem == widItem_AD){

//        succ = saveMediaList();
//    }else if(_widItem == widItem_listbillboard ||
//             _widItem == widItem_listChinese  ||
//             _widItem == widItem_listHi ||
//             _widItem == widItem_listNew
//             ){
//        if(replaceFalg)
//            succ = saveReplaceMediaList();
//        else
//            succ = saveMediaList();
//    }else if(_widItem == widItem_listNet){

//        if(replaceFalg)
//            succ = saveReplaceMediaList("net");
//        else
//            succ = saveMediaListNet();
//    }else if(_widItem == widItem_listHot){

//        if(replaceFalg)
//            succ = saveReplaceMediaList("hot");
//        else
//            succ = saveMediaListHot();
//    }

    if(succ)
        QMessageBox::information(this, "提示", "保存成功！");
}

void FmAddModifyDialog::play(const int &row, const int &)
{
   _queryList.seek(row);
   QString path = _queryList.value("_path").toString();
   if(!path.isEmpty())
       view_music->palyVideo(path);
}

void FmAddModifyDialog::playAddMusic(const int &row, const int &)
{
    _querySearch.seek(row);
    QString path = _querySearch.value("_path").toString();
    if(!path.isEmpty())
        view_addMusic->palyVideo(path);
}


bool FmAddModifyDialog::saveModityLid()
{
    SongList _songList;
    _songList.lid = QString::number(lid);
    _songList.serial_id = _query.value("_serial_id").toString();
    _songList.title = lineEdit_listName->text();
    _songList.image = lineEdit_listImage->text();
    _songList.type = "yqc";
    _songList.count = QString::number(rowList.size());
    _songList.special = QString::number(0);
    return _sql->updateFmLid(_songList, song_list);
}

bool FmAddModifyDialog::saveNewLid()
{
    _query.first();
    int _lid = _query.value("_lid").toUInt();
    _lid++;
    lid = _lid;
    qint64 _serial_id = 1780000000 + _lid;

    SongList _songList;
    _songList.lid = QString::number(_lid);
    _songList.serial_id = QString::number(_serial_id);
    _songList.title = lineEdit_listName->text();
    _songList.image = lineEdit_listImage->text();
    _songList.type = "yqc";
    _songList.count = QString::number(rowList.size());
    _songList.special = "";
    return _sql->insertFmLid(_songList);
}

bool FmAddModifyDialog::saveMusic()
{
    QStringList list;

    for(int i=0; i<rowList.size(); i++){
        QStringList temp;
        QString tempStr;
        tempStr.append(QString::number(lid));
        tempStr.append(", ");
        tempStr.append(QString::number(lid*10000 + i));
        tempStr.append(", ");
        temp = rowList.value(i);
        tempStr.append(temp.value(0));

        list.append(tempStr);
    }

    return _sql->insertFmDetail(lid, list);
}

void FmAddModifyDialog::initMediaList()
{
    label_listImage->setHidden(true);
    label_listName->setHidden(true);
    lineEdit_listImage->setHidden(true);
    lineEdit_listName->setHidden(true);
    pushButton_preview->setHidden(true);
    pushButton_upload->setHidden(true);    
}

bool FmAddModifyDialog::saveMediaList()
{
    QList<MediaList> addM;
    QStringList list;
    qint64 maxIndex;
    _sql->getMaxIndex(_type, maxIndex);
    for(int i=0; i<rowList.size(); i++){
        maxIndex++;
        MediaList media;
        QStringList temp;
        QString tempStr;
        tempStr.append(QString("'%1'").arg(_type));
        tempStr.append(", ");
        tempStr.append(QString::number(maxIndex));
        tempStr.append(", ");
        temp = rowList.value(i);
        tempStr.append(temp.value(0));        

        list.append(tempStr);

        media.index = QString::number(maxIndex);
        media.type = _type;
        media.serial_id = temp.value(1);

        addM.append(media);
    }

    return _sql->addMediaList(_type, list, addM);
}


bool FmAddModifyDialog::saveReplaceMediaList(QString hotnet)
{
    _query.seek(replaceRow);
    int srcMid, srcIndex, destMid;
    srcMid = _query.value("_mid").toInt();
    srcIndex = _query.value("_index").toInt();
    QStringList value;
    if(rowList.isEmpty())
        return false;
    value = rowList.at(0);
    destMid = value.value(0).toInt();

    QString serial_id = value.value(1);

   return  _sql->replaceMediaList(srcMid, srcIndex, destMid, _type, serial_id, hotnet);
}

bool FmAddModifyDialog::saveMediaListNet()
{    
    QStringList list;
    qint64 maxIndex;
    _sql->getMaxIndex_hotnet(_type,"net", maxIndex);
    for(int i=0; i<rowList.size(); i++){
        maxIndex++;
        QStringList temp;
        QString tempStr;
        tempStr.append(_type);
        tempStr.append(", ");
        tempStr.append(QString::number(maxIndex));
        tempStr.append(", ");
        temp = rowList.value(i);
        tempStr.append(temp.value(0));

        list.append(tempStr);
    }
    QString net = "net";
    bool ret = _sql->addMediaList_hotnet(net, _type, list);
    return ret;
}

void FmAddModifyDialog::setSavePushbuttonHidden(bool hidden)
{
    pushButton_save->setHidden(hidden);
}

bool FmAddModifyDialog::saveMediaListHot()
{
    QStringList list;
    qint64 maxIndex;
    _sql->getMaxIndex_hotnet(_type,"hot", maxIndex);
    for(int i=0; i<rowList.size(); i++){
        maxIndex++;
        QStringList temp;
        QString tempStr;
        tempStr.append(_type);
        tempStr.append(", ");
        tempStr.append(QString::number(maxIndex));
        tempStr.append(", ");
        temp = rowList.value(i);
        tempStr.append(temp.value(0));

        list.append(tempStr);
    }

    int ret = _sql->addMediaList_hotnet("hot", _type, list);
    return ret;
}
