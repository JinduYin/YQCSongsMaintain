#include "singerquerywidget.h"
#include "pagingtableview.h"
#include "typeindexvalue.h"
#include "mysqlquery.h"
#include "tablemodel.h"
#include "singerinfodialog.h"

#include <QFile>
#include <QLabel>
#include <QPainter>
#include <QComboBox>
#include <QLineEdit>
#include <QTableView>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QDebug>

SingerQueryWidget::SingerQueryWidget(QWidget *parent)
    : QWidget(parent),
      _sql(NULL)
{
    initWidget();
    readAndSetStyleSheet();
    initWidgetValue();
    initCombobox();
    connect(pushButton_export_excel, &QPushButton::clicked, this, &SingerQueryWidget::export_excel_clicked);
    connect(pushButton_search, &QPushButton::clicked, this, &SingerQueryWidget::setActorValue);
    connect(lineEdit_search, &QLineEdit::editingFinished, this, &SingerQueryWidget::setActorValue);

    connect(tableView_singerQuery, &PagingTableView::updateView, this, &SingerQueryWidget::setActorValue);
    connect(tableView_singerQuery, &PagingTableView::currentRow, this, &SingerQueryWidget::setActorInfo);

    connect(comboBox_sex, SIGNAL(currentIndexChanged(QString)), this, SLOT(combobox_currentIndexChanged(QString)));
    connect(comboBox_nation, SIGNAL(currentIndexChanged(QString)), this, SLOT(combobox_currentIndexChanged(QString)));
    connect(comboBox_stars, SIGNAL(currentIndexChanged(QString)), this, SLOT(combobox_currentIndexChanged(QString)));
    connect(comboBox_enabled, SIGNAL(currentIndexChanged(QString)), this, SLOT(combobox_currentIndexChanged(QString)));
}

SingerQueryWidget::~SingerQueryWidget()
{

}

void SingerQueryWidget::readAndSetStyleSheet()
{
    QFile qss(":/qss/singerquery.qss");
    qss.open(QFile::ReadOnly);
    this->setStyleSheet(qss.readAll());
    qss.close();

    this->setObjectName("Widget");
    widgetTitle->setObjectName("TopWidget");
    widgetCenter->setObjectName("CenterWidget");
    label_title->setObjectName("TitleLabel");
    label_select->setObjectName("SelectLabel");
    label_result->setObjectName("ResultLabel");

    label_sex->setObjectName("Label");
    label_nation->setObjectName("Label");
    label_stars->setObjectName("Label");
    label_enabled->setObjectName("Label");
    label_search->setObjectName("Label");

    pushButton_export_excel->setObjectName("Button");
    pushButton_search->setObjectName("SerachButton");
    lineEdit_search->setObjectName("SerachEdit");

    comboBox_sex->setObjectName("Combobox");
    comboBox_nation->setObjectName("Combobox");
    comboBox_stars->setObjectName("Combobox");
    comboBox_enabled->setObjectName("Combobox");
}

void SingerQueryWidget::initWidget()
{
    widgetTitle = new QWidget(this);
    widgetCenter = new QWidget(this);

    lineEdit_search = new QLineEdit(widgetTitle);
    pushButton_search = new QPushButton(lineEdit_search);
    pushButton_export_excel = new QPushButton(widgetTitle);

    label_search = new QLabel(widgetTitle);
    label_title = new QLabel(widgetTitle);
    label_select = new QLabel(widgetCenter);
    label_sex = new QLabel(widgetCenter);
    label_nation = new QLabel(widgetCenter);
    label_stars = new QLabel(widgetCenter);
    label_enabled = new QLabel(widgetCenter);
    label_result = new QLabel(this);

    comboBox_sex = new QComboBox(widgetCenter);
    comboBox_nation = new QComboBox(widgetCenter);
    comboBox_stars = new QComboBox(widgetCenter);
    comboBox_enabled = new QComboBox(widgetCenter);

    tableView_singerQuery = new PagingTableView(this);
    tableView_singerQuery->model->setMediaOrActor(false);

    label_search->setFixedWidth(56);
    pushButton_export_excel->setFixedHeight(36);
    pushButton_export_excel->setFixedWidth(90);
    lineEdit_search->setFixedWidth(260);
    lineEdit_search->setFixedHeight(36);

    comboBox_sex->setFixedHeight(36);
    comboBox_sex->setFixedWidth(110);
    comboBox_nation->setFixedHeight(36);
    comboBox_nation->setFixedWidth(110);
    comboBox_stars->setFixedHeight(36);
    comboBox_stars->setFixedWidth(110);
    comboBox_enabled->setFixedHeight(36);
    comboBox_enabled->setFixedWidth(110);

    searchSingerLayout = new QHBoxLayout();
    searchLayout = new QHBoxLayout();
    titleLayout = new QHBoxLayout();

    searchSingerLayout->addWidget(label_search);
    searchSingerLayout->addWidget(lineEdit_search);
    searchSingerLayout->setContentsMargins(0, 0, 0, 0);
    searchSingerLayout->setSpacing(12);

    searchLayout->addLayout(searchSingerLayout);
    searchLayout->addWidget(pushButton_export_excel);
    searchLayout->setContentsMargins(0, 0, 0, 0);
    searchLayout->setSpacing(20);

    titleLayout->addWidget(label_title);
    titleLayout->addStretch();
    titleLayout->addLayout(searchLayout);
    titleLayout->setContentsMargins(20, 10, 12, 10);
    widgetTitle->setLayout(titleLayout);
    widgetTitle->setFixedHeight(60);

    sexLayout = new QHBoxLayout();
    nationLayout = new QHBoxLayout();
    starsLayout = new QHBoxLayout();
    enabledLayout = new QHBoxLayout();
    conditionLayout = new QHBoxLayout();
    centerLayout = new QVBoxLayout();

    sexLayout->addWidget(label_sex);
    sexLayout->addWidget(comboBox_sex);
    sexLayout->setContentsMargins(0, 0, 0, 0);
    sexLayout->setSpacing(6);

    nationLayout->addWidget(label_nation);
    nationLayout->addWidget(comboBox_nation);
    nationLayout->setContentsMargins(0, 0, 0, 0);
    nationLayout->setSpacing(8);

    starsLayout->addWidget(label_stars);
    starsLayout->addWidget(comboBox_stars);
    starsLayout->setContentsMargins(0, 0, 0, 0);
    starsLayout->setSpacing(8);

    enabledLayout->addWidget(label_enabled);
    enabledLayout->addWidget(comboBox_enabled);
    enabledLayout->setContentsMargins(0, 0, 0, 0);
    enabledLayout->setSpacing(8);

    conditionLayout->addLayout(sexLayout);
    conditionLayout->addLayout(nationLayout);
    conditionLayout->addLayout(starsLayout);
    conditionLayout->addLayout(enabledLayout);
    conditionLayout->addStretch();
    conditionLayout->setContentsMargins(26, 0, 0, 0);
    conditionLayout->setSpacing(30);

    centerLayout->addWidget(label_select);
    centerLayout->addLayout(conditionLayout);
    centerLayout->setContentsMargins(20, 15, 12, 20);
    widgetCenter->setLayout(centerLayout);

    tableViewLayout = new QVBoxLayout();
    tableViewLayout->addWidget(label_result);
    tableViewLayout->addWidget(tableView_singerQuery);
    tableViewLayout->setContentsMargins(20, 15, 12, 9);
    tableViewLayout->setSpacing(10);

    vLayout = new QVBoxLayout();
    vLayout->addWidget(widgetTitle);
    vLayout->addWidget(widgetCenter);
    vLayout->addLayout(tableViewLayout);
    vLayout->setContentsMargins(0, 0, 0, 0);
    vLayout->setSpacing(0);

    this->setLayout(vLayout);
}

void SingerQueryWidget::initWidgetValue()
{
    label_title->setText("歌星查询");
    label_select->setText("筛选条件");
    label_sex->setText("歌星性别");
    label_nation->setText("歌星区域");
    label_stars->setText("歌星评星");
    label_enabled->setText("歌星状态");
    label_result->setText("搜索结果");
    label_search->setText("歌星搜索");

    lineEdit_search->setPlaceholderText("歌星名称");
    pushButton_export_excel->setText("导出总表");

    tableView_singerQuery->initActorDelegate(false);
    QRect rect = lineEdit_search->geometry();
    lineEdit_search->setTextMargins(0, 0, 20, 0);
    pushButton_search->setGeometry(rect.width()-20, 10, 14, 14);
    pushButton_search->setCursor(Qt::PointingHandCursor);
}

void SingerQueryWidget::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void SingerQueryWidget::setActorValue()
{
    ActorPagingQuery argu;
    getQueryCondition(argu);

    qint64 total = 0;
    _sql->queryCountActor_A(argu, total);
    tableView_singerQuery->setTotal_Rows_Pages(total);

    query.clear();
    tableView_singerQuery->tableView->clear();

    _sql->queryActor(argu, tableView_singerQuery->limitArgu, query);
    tableView_singerQuery->showUploadData(query, false);
}

void SingerQueryWidget::setActorInfo(const int &row)
{
    SingerInfoDialog *dialog = new SingerInfoDialog();

    query.seek(row);
    qint64 serial = query.value("_serial_id").toLongLong();    
    QModelIndex index = tableView_singerQuery->model->index(row, 1);

    QSqlQuery _query;
    Actor _actor;
    _actor.image = index.data().toString();
    if(!_sql->queryActorOfSerialId(serial, _query))
        return;

    getValue(_query, _actor);
    dialog->setValue(_actor);

    dialog->exec();
}

void SingerQueryWidget::getQueryCondition(ActorPagingQuery &argu)
{
    argu._sex = comboBox_sex->currentIndex();
    argu._nation = comboBox_nation->currentIndex();
    argu._enabled = comboBox_enabled->currentIndex();
    argu._stars = comboBox_stars->currentIndex();

    argu.singerName = lineEdit_search->text();
}

void SingerQueryWidget::getValue(QSqlQuery &_query, Actor &_actor)
{
    _query.first();
    _actor.sid = _query.value("sid").toString();
    _actor.serial_id = _query.value("serial_id").toString();
    _actor.name = _query.value("name").toString();
    _actor.nation = _query.value("nation").isNull()?"":_query.value("nation").toString();
    _actor.sex = _query.value("sex").isNull()?"":_query.value("sex").toString();

    _actor.pinyin = _query.value("pinyin").toString();
    _actor.header = _query.value("header").toString();
    _actor.head = _query.value("head").toString();
    _actor.words = _query.value("words").toString();
    _actor.song_count = _query.value("song_count").toString();

    _actor.stars = _query.value("stars").toString();
    _actor.count = _query.value("count").toString();
    _actor.order = _query.value("order").isNull()?"":_query.value("order").toString();
    _actor.enabled = _query.value("enabled").toString();
    _actor.black = _query.value("black").toString();

    _actor.info = _query.value("info").isNull()?"":_query.value("info").toString();
}

void SingerQueryWidget::initSql(MysqlQuery *sql)
{
    _sql = sql;    
}

void SingerQueryWidget::initCombobox()
{
    TypeIndexValue value;
    comboBox_nation->insertItems(0, QStringList(value.nation.values()));
    comboBox_sex->insertItems(0, QStringList(value.sex.values()));
    comboBox_enabled->insertItems(0, QStringList(value.enabled.values()));
    comboBox_stars->insertItems(0, QStringList(value.stars.values()));
}

void SingerQueryWidget::set_comboBox_sex(QStringList &sex)
{   
    comboBox_sex->addItems(sex);
}

void SingerQueryWidget::set_comboBox_nation(QStringList &nat)
{ 
    comboBox_nation->addItems(nat);
}

void SingerQueryWidget::set_comboBox_stars(QStringList &sta)
{
    comboBox_stars->addItems(sta);
}

void SingerQueryWidget::set_comboBox_enabled(QStringList &ena)
{
    comboBox_enabled->addItems(ena);
}

void SingerQueryWidget::export_excel_clicked()
{
    QMessageBox::information(this, "一起唱", "导出表格");
}

void SingerQueryWidget::combobox_currentIndexChanged(const QString &)
{
    tableView_singerQuery->limitArgu.currentpage = 0;
    tableView_singerQuery->current_page = 0;
    tableView_singerQuery->limitArgu.tagPage = -1;
    setActorValue();
}

