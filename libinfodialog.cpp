#include "libinfodialog.h"
#include "pagingtableview.h"
#include "tablemodel.h"
#include "mysqlquery.h"

#include <QFile>
#include <QLabel>
#include <QPainter>
#include <QStyleOption>
#include <QPushButton>
#include <QEventLoop>
#include <QHBoxLayout>
#include <QVBoxLayout> //
LibInfoDialog::LibInfoDialog(bool isMedia, QWidget *parent)
    : DropShadowWidget(parent),
      _isMedia(isMedia)
{
    setFixedHeight(484);
    setFixedWidth(762);

    widgetTitle = new QWidget(this);
    label_title = new QLabel(widgetTitle);
    pushButton_close = new QPushButton(widgetTitle);
    view = new PagingTableView(this, false);

    connect(view, &PagingTableView::play, this, &LibInfoDialog::play);
    connect(view, &PagingTableView::updateView, this, &LibInfoDialog::showQueryValue);
    connect(pushButton_close, &QPushButton::clicked, this, &LibInfoDialog::close);


    hLayout = new QHBoxLayout();
    hLayout->addWidget(label_title);
    hLayout->addStretch();
    hLayout->addWidget(pushButton_close);
    hLayout->setContentsMargins(20, 0, 20, 0);
    hLayout->setSpacing(0);
    widgetTitle->setLayout(hLayout);

    vLayout = new QVBoxLayout();
    vLayout->addWidget(widgetTitle);
    vLayout->addWidget(view);
    vLayout->setMargin(0);
    vLayout->setSpacing(0);

    this->setLayout(vLayout);


    QFile qss(":/qss/title.qss");
    qss.open(QFile::ReadOnly);
    this->setStyleSheet(qss.readAll());
    qss.close();

    pushButton_close->setFixedHeight(14);
    pushButton_close->setFixedWidth(14);
    widgetTitle->setFixedHeight(38);
    widgetTitle->setObjectName("TitleWidget");
    pushButton_close->setObjectName("CloseButton");
    view->tableView->setObjectName("PagingTable");    
}

LibInfoDialog::~LibInfoDialog()
{

}

void LibInfoDialog::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void LibInfoDialog::setTitleString(const QString &title)
{
    label_title->setText(title);
}

void LibInfoDialog::initActorOrMedia()
{
    qint64 total = 0;

    if(_isMedia){
        view->initMediaDelegate(false);
        _sql->queryCountTotal_M(total);        

    }else{
        view->initActorDelegate(false);        
        _sql->queryCountActor_A(_queryArgu_actor, total);
    }

    view->setTotal_Rows_Pages(total);
}

void LibInfoDialog::play(const int &row, const int &)
{
    query.seek(row);
    QString path = query.value("_path").toString();
    view->palyVideo(path);
}

void LibInfoDialog::showInfoActor(MysqlQuery *sql, ActorPagingQuery queryArgu)
{
    _sql = sql;
    _queryArgu_actor = queryArgu;
    initActorOrMedia();

    showQueryValue();
}

void LibInfoDialog::showInfoMedia(MysqlQuery *sql, MediaPagingQuery queryArgu)
{
    _sql = sql;
    _queryArgu_media = queryArgu;
    initActorOrMedia();

    showQueryValue();
}

void LibInfoDialog::showQueryValue()
{
    query.clear();
    view->tableView->clear();


    if(_isMedia){
        _sql->queryMedia(_queryArgu_media, view->limitArgu, query);        
        view->showUploadData(query, true);
    }
    else{
        _sql->queryActor(_queryArgu_actor, view->limitArgu, query);
        view->showUploadData(query, false);
    }
}
