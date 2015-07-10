#include "libinfowidget.h"
#include "mysqlquery.h"
#include "pagingtableview.h"
#include "tablemodel.h"
#include "yqcdelegate.h"
#include "libinfodialog.h"
#include "typeindexvalue.h"
#include "releasedialog.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTableView>
#include <QPainter>
#include <QLabel>
#include <QFile>
#include <QHeaderView>
#include <QMessageBox>
#include <QPushButton>
#include <QDebug>

LibInfoWidget::LibInfoWidget(QWidget *parent)
    : QWidget(parent)
{
    initWidget();
    readAndSetStyleSheet();
    initWidgetValue();

    connect(button_release, &QPushButton::clicked, this, &LibInfoWidget::release);
}

LibInfoWidget::~LibInfoWidget()
{

}

void LibInfoWidget::readAndSetStyleSheet()
{
    QFile qss(":/qss/libinfo.qss");
    qss.open(QFile::ReadOnly);
    this->setStyleSheet(qss.readAll());
    qss.close();

    this->setObjectName("TitleWidget");
    label_musicTotal->setObjectName("TotalLabel");
    label_libTitle->setObjectName("TitleLabel");
    label_singerTotal->setObjectName("TotalLabel");

    widget_title->setObjectName("Title");
    button_release->setObjectName("Button");
}

void LibInfoWidget::initWidget()
{
    widget_libInfo = new QWidget(this);
    widget_title = new QWidget(this);
    tableView_songsTotal = new PagingTableView(this, true);
    tableView_singerTotal = new PagingTableView(this, true);
    tableView_singerTotal->model->setMediaOrActor(false);
    label_libTitle = new QLabel(this);
    label_musicTotal = new QLabel(this);
    label_singerTotal = new QLabel(this);

    button_release = new QPushButton(this);

    m_libDelegateA = new LibDelegate(this);
    m_libDelegateM = new LibDelegate(this);
    m_libDelegateA->setRGB(248, 109, 147);
    m_libDelegateM->setRGB(110, 161, 240);
    tableView_singerTotal->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    tableView_singerTotal->tableView->setItemDelegate(m_libDelegateA);
    tableView_songsTotal->tableView->setItemDelegate(m_libDelegateM);
    connect(tableView_singerTotal->tableView, &TableView::doubleClicked, this, &LibInfoWidget::singerDoubleClicked);
    connect(tableView_songsTotal->tableView, &TableView::doubleClicked, this, &LibInfoWidget::songDoubleClicked);


    musicLayout = new QVBoxLayout();
    singerLayout = new QVBoxLayout();
    centerLayout = new QVBoxLayout();
    vLayout = new QVBoxLayout();

    musicLayout->addWidget(label_musicTotal);
    musicLayout->addWidget(tableView_songsTotal);
    musicLayout->setContentsMargins(0, 0, 0, 0);
    musicLayout->setSpacing(10);

    singerLayout->addWidget(label_singerTotal);
    singerLayout->addWidget(tableView_singerTotal);
    singerLayout->setContentsMargins(0, 0, 0, 0);
    singerLayout->setSpacing(10);

    centerLayout->addLayout(musicLayout);
    centerLayout->addLayout(singerLayout);
    centerLayout->setContentsMargins(20, 20, 2, 10);
    centerLayout->setSpacing(28);

    QHBoxLayout *titleLayout = new QHBoxLayout();
    titleLayout->addWidget(label_libTitle);
    titleLayout->addStretch();
    titleLayout->addWidget(button_release);
    titleLayout->setContentsMargins(0, 0, 20, 0);
    titleLayout->setSpacing(0);
    widget_title->setLayout(titleLayout);

    vLayout->addWidget(widget_title);
    vLayout->addLayout(centerLayout);
    vLayout->setContentsMargins(0, 0, 0, 0);
    vLayout->setSpacing(0);

    this->setLayout(vLayout);
}

void LibInfoWidget::initWidgetValue()
{
    label_libTitle->setText("总库统计");
    label_musicTotal->setText("歌曲统计");
    label_singerTotal->setText("歌手统计");
    label_libTitle->setFixedHeight(60);
    button_release->setFixedSize(90, 36);

    tableView_singerTotal->widget_bottom->setHidden(true);
    tableView_songsTotal->widget_bottom->setHidden(true);

    tableView_singerTotal->tableView->horizontalHeader()->setVisible(false);
    tableView_songsTotal->tableView->horizontalHeader()->setVisible(false);

    tableView_singerTotal->tableView->verticalHeader()->setDefaultSectionSize(100);
    tableView_singerTotal->tableView->horizontalHeader()->setDefaultSectionSize(230);
    tableView_songsTotal->tableView->verticalHeader()->setDefaultSectionSize(100);
    tableView_songsTotal->tableView->horizontalHeader()->setDefaultSectionSize(230);
}

void LibInfoWidget::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void LibInfoWidget::initSqlPointer( MysqlQuery *sql)
{
    _sql = sql;
}

void LibInfoWidget::initQueryCondition()
{
    QList< QPair<QString, qint64> > listM;
    qint64 totalM, enabledM, disabledM, matchM;
    QSqlQuery language, type;
    _sql->queryCountTotal_M(totalM);
    _sql->queryCountEnabled_M(enabledM);
    _sql->queryCountDisabled_M(disabledM);
    _sql->queryCountIsMatch_M(matchM);
    _sql->queryCountLanguage_M(language);
    _sql->queryCountType_M(type);
    listM.clear();

    listM.append(QPair<QString, qint64>("other,全部歌曲", totalM));
    listM.append(QPair<QString, qint64>("other,启用歌曲", enabledM));
    listM.append(QPair<QString, qint64>("other,禁用歌曲", disabledM));
    listM.append(QPair<QString, qint64>("other,可K歌歌曲", matchM));
    while(language.next()){
        QString temp("language,");
        temp.append(language.value("_language").toString());
        listM.append(QPair<QString, qint64>(temp, language.value("_count").toLongLong()));
    }
    while(type.next()){
        QString temp("type,");
        temp.append(type.value("_type").toString());
        listM.append(QPair<QString, qint64>(temp, type.value("_count").toLongLong()));
    }

    QList< QPair<QString, qint64> > listA;
    qint64 totalA, enabledA, disabledA;
    QSqlQuery sex, nation;
    _sql->queryCountSinger_A(totalA);
    _sql->queryCountEnabled_A(enabledA);
    _sql->queryCountDisable_A(disabledA);
    _sql->queryCountSex_A(sex);
    _sql->queryCountNation_A(nation);
    listA.clear();
    listA.append(QPair<QString, qint64>("other,全部歌星", totalA));
    listA.append(QPair<QString, qint64>("other,启用歌星", enabledA));
    listA.append(QPair<QString, qint64>("other,禁用歌星", disabledA));
    while(sex.next()){
        QString temp("sex,");
        temp.append(sex.value("_sex").toString());
        listA.append(QPair<QString, qint64>(temp, sex.value("_count").toLongLong()));
    }
    while(nation.next()){
        QString temp("nation,");
        temp.append(nation.value("_nation").toString());
        listA.append(QPair<QString, qint64>(temp, nation.value("_count").toLongLong()));
    }

    setTableModelValue(listA, listM);
}

void LibInfoWidget::setTableModelValue( QList< QPair<QString, qint64> > listA,
                                        QList< QPair<QString, qint64> > listM )
{
    int remainderM = listM.size()%5;
    if(remainderM != 0){
        for(int i=0; i<5-remainderM; i++){
            listM.append(QPair<QString, qint64>(",", 0));
        }
    }

    int remainderA = listA.size()%5;
    if(remainderA != 0){
        for(int i=0; i<5-remainderA; i++){
            listA.append(QPair<QString, qint64>(",", 0));
        }
    }


    if(!rowListSong.isEmpty())
        rowListSong.clear();
    QStringList rowValue;
    for(int i=0; i<listM.size(); i++){

        QString str = listM.at(i).first;
        str.append(",");
        str.append(QString::number(listM.at(i).second));
        rowValue.append(str);

        if (i < (rowListSong.size()+1) *5 - 1)
            continue;

        rowListSong.append(rowValue);
        rowValue.clear();
    }

    if(!rowListSinger.isEmpty())
        rowListSinger.clear();
    QStringList rowValueSong;
    for(int i=0; i<listA.size(); i++){

        QString str = listA.at(i).first;
        str.append(",");
        str.append(QString::number(listA.at(i).second));
        rowValueSong.append(str);

        if (i < (rowListSinger.size()+1) *5 - 1)
            continue;
        rowListSinger.append(rowValueSong);
        rowValueSong.clear();
    }

    tableView_singerTotal->model->setModalDatas(&rowListSinger);
    tableView_songsTotal->model->setModalDatas(&rowListSong);
}

void LibInfoWidget::singerDoubleClicked(const QModelIndex &index)
{    
    ActorPagingQuery queryArgu;
    queryArgu._enabled = -1;
    queryArgu._nation = -1;
    queryArgu._sex = -1;
    queryArgu._stars = -1;

    QStringList dataList = index.data().toString().split(",");
    QString type = dataList.at(0);
    QString data = dataList.at(1);
    TypeIndexValue value;
    if(index.row() == 0 && index.column() == 0){///全部歌星

    }else if(index.row() == 0 && index.column() == 1){///启用歌星

        queryArgu._enabled = 1 + 1; //"启用";
    }else if(index.row() == 0 && index.column() == 2){///禁用歌星

        queryArgu._enabled = 0 + 1; //"禁用";
    }else if(type.compare("sex") == 0){
        queryArgu._sex = value.sex.key(data);
    }else if(type.compare("nation") == 0)
        queryArgu._nation = value.nation.key(data);
    else
        return;


    LibInfoDialog *singer = new LibInfoDialog(false);
    singer->showInfoActor(_sql, queryArgu);

    singer->exec();
}

void LibInfoWidget::songDoubleClicked(const QModelIndex &index)
{
    QString all("全部");
    MediaPagingQuery queryArgu;

    queryArgu.language = all;
    queryArgu.pitch = all;
    queryArgu.quality = all;
    queryArgu.resolution = all;
    queryArgu.rthym = all;
    queryArgu.source = all;
    queryArgu.type = all;
    queryArgu.version = all;
    queryArgu.enabled = all;
    queryArgu.match = all;

    QStringList dataList = index.data().toString().split(",");
    QString type = dataList.at(0);
    QString data = dataList.at(1);
    if(index.row() == 0 && index.column() == 0){///全部歌星

    }else if(index.row() == 0 && index.column() == 1){///启用歌星
        queryArgu.enabled = "1";
    }else if(index.row() == 0 && index.column() == 2){///禁用歌星
        queryArgu.enabled = "0";
    }else if(index.row() == 0 && index.column() == 3){

        queryArgu.match = "0";
    }else if(type.compare("language") == 0){
        queryArgu.language = data;
    }else if (type.compare("type") == 0)
        queryArgu.type = data;
    else
        return;


    LibInfoDialog *song = new LibInfoDialog(true);
    song->showInfoMedia(_sql, queryArgu);

    song->exec();
}

void LibInfoWidget::release()
{
    ReleaseDialog *dialog = new ReleaseDialog();

    dialog->exec();
}


