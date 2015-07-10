#include "addfmmedialist.h"
#include "ui_addfmmedialist.h"
#include "yqcdelegate.h"
#include "pagingtablewidget.h"
#include "mysqlquery.h"
#include <QTableWidget>
#include <QMenu>
#include <QAction>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>

AddFmMediaList::AddFmMediaList(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddFmMediaList)
{
    ui->setupUi(this);

    up = new QAction("上移", this);
    down = new QAction("下移", this);
    dele = new QAction("删除", this);
    connect(up, &QAction::triggered, this, &AddFmMediaList::upMove);
    connect(down, &QAction::triggered, this, &AddFmMediaList::downMove);
    connect(dele, &QAction::triggered, this, &AddFmMediaList::deleItem);

    initTableWidget();
    ui->label_mediaName->setText("歌单名称");
    ui->label_mediaImage->setText("歌单封面");
    ui->pushButton_preview->setText("浏览……");
    ui->pushButton_addMedia->setText("添加歌曲");
    ui->pushButton_save->setText("确认保存");
    ui->widget->bottomWidget->setHidden(true);
    ui->widget->setHiddenMenu(true);
    connect(ui->widget, &PagingTableWidget::addMenu, this, &AddFmMediaList::addMenuRight);
}

AddFmMediaList::~AddFmMediaList()
{
    delete ui;
}

void AddFmMediaList::initAddFm()
{

}

void AddFmMediaList::initUpdateFm(MysqlQuery *sql, QSqlQuery *lidQuery, QSqlQuery *query)
{
    _sql = sql;
    _fmLidQuery = lidQuery;
    _fmQuery = query;

    setFmMediaList();
    setTableWidget();
}

void AddFmMediaList::setSqlPointer(MysqlQuery *sql)
{
    _sql = sql;
}

void AddFmMediaList::setQueryPointer(QSqlQuery *lidQuery, QSqlQuery *query)
{
    _fmLidQuery = lidQuery;
    _fmQuery = query;
}

void AddFmMediaList::initTableWidget()
{
    QStringList headerList;
    headerList << "序号" << "歌曲名称" << "歌星" << "歌曲语种" << "歌曲分类";// << "" << "";

    ui->widget->tableWidget->setItemDelegate(new NoFocusDelegate());
    ui->widget->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->widget->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->widget->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->widget->tableWidget->horizontalHeader()->setHighlightSections(false);
    ui->widget->tableWidget->verticalHeader()->setVisible(false);
    ui->widget->tableWidget->setShowGrid(false);
    ui->widget->tableWidget->resizeRowsToContents();
    ui->widget->tableWidget->setHorizontalScrollBarPolicy((Qt::ScrollBarAlwaysOff));
    QHeaderView *headerWidget = ui->widget->tableWidget->horizontalHeader();
    headerWidget->setStretchLastSection(true);  ////最后一行适应空余部分    

    ui->widget->tableWidget->setColumnCount(headerList.size());
    ui->widget->tableWidget->setHorizontalHeaderLabels(headerList);

    ui->widget->isPaging(false);
}

void AddFmMediaList::setTableWidget()
{
    ui->widget->tableWidget->clearContents();
    ui->widget->tableWidget->setRowCount(_fmQuery->size());
    ui->widget->setTotal_Rows_Pages(_fmQuery->size());

    _fmQuery->seek(0);
    _fmQuery->previous();
    int row = 0;
    while(_fmQuery->next()){
        ui->widget->tableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(row+1)));
        ui->widget->tableWidget->setItem(row, 1, new QTableWidgetItem(_fmQuery->value("_name").toString()));
        ui->widget->tableWidget->setItem(row, 2, new QTableWidgetItem(_fmQuery->value("_singer").toString()));
        ui->widget->tableWidget->setItem(row, 3, new QTableWidgetItem(_fmQuery->value("_language").toString()));
        ui->widget->tableWidget->setItem(row, 4, new QTableWidgetItem(_fmQuery->value("_type").toString()));
        row++;
    }
}

void AddFmMediaList::setFmMediaList()
{
    QString imagePath = _fmLidQuery->value("_image").toString();
    ui->lineEdit_meidaName->setText(_fmLidQuery->value("_title").toString());
    ui->lineEdit_mediaImage->setText(imagePath);

    if(imagePath.isEmpty()){
        ui->label_showImage->setText("无图像");
        return;
    }

    ui->label_showImage->setScaledContents(true);
    QImage image;
    image.load(imagePath);
    ui->label_showImage->setPixmap(QPixmap::fromImage(image));
}

void AddFmMediaList::addMenuRight(const QPoint &pos)
{
    if (ui->widget->tableWidget->rowAt(pos.y()) == -1)
        return;

    if (!ui->widget->tableWidget->rowAt(pos.y()) == 0)
        ui->widget->menuRight->addAction(up);
    if (!(ui->widget->tableWidget->rowAt(pos.y()) == ui->widget->total_Rows-1))
        ui->widget->menuRight->addAction(down);
    ui->widget->menuRight->addAction(dele);
    ui->widget->menuRight->exec(QCursor::pos());
}

void AddFmMediaList::upMove()
{
//    int currentRow = ui->widget->tableWidget->currentRow();
//    _fmQuery->seek(currentRow);

//    qint64 mid, lid, index;
//    mid = _fmQuery->value("_mid").toLongLong();
//    lid = _fmQuery->value("_lid").toLongLong();
//    index = _fmQuery->value("_index").toLongLong();
//    _fmQuery->previous();
//    qint64 midPre, lidPre, indexPre;
//    midPre = _fmQuery->value("_mid").toLongLong();
//    lidPre = _fmQuery->value("_lid").toLongLong();
//    indexPre = _fmQuery->value("_index").toLongLong();

//    if(_sql->updateFmMediaListUpDownMove(lid, index, midPre)){
//       if(_sql->updateFmMediaListUpDownMove(lidPre, indexPre, mid));
//       else
//           _sql->updateFmMediaListUpDownMove(lid, index, mid);
//    }

    emit updateView();
    setTableWidget();
}

void AddFmMediaList::downMove()
{
//    int currentRow = ui->widget->tableWidget->currentRow();
//    _fmQuery->seek(currentRow);

//    qint64 mid, lid, index;
//    mid = _fmQuery->value("_mid").toLongLong();
//    lid = _fmQuery->value("_lid").toLongLong();
//    index = _fmQuery->value("_index").toLongLong();
//    _fmQuery->next();
//    qint64 midNext, lidNext, indexNext;
//    midNext = _fmQuery->value("_mid").toLongLong();
//    lidNext = _fmQuery->value("_lid").toLongLong();
//    indexNext = _fmQuery->value("_index").toLongLong();

//    if(_sql->updateFmMediaListUpDownMove(lid, index, midNext)){
//       if(_sql->updateFmMediaListUpDownMove(lidNext, indexNext, mid));
//       else
//           _sql->updateFmMediaListUpDownMove(lid, index, mid);
//    }

    emit updateView();
    setTableWidget();
}

void AddFmMediaList::deleItem()
{
    int currentRow = ui->widget->tableWidget->currentRow();
    _fmQuery->seek(currentRow);

//    qint64 mid, lid;
//    mid = _fmQuery->value("_mid").toLongLong();
//    lid = _fmQuery->value("_lid").toLongLong();

//    if(_sql->deleteFMSonglistDetail(lid, mid)){
//        emit updateView();
//        setTableWidget();
//    }else
//        QMessageBox::information(this, "提示", "删除失败!");
}

void AddFmMediaList::on_pushButton_preview_clicked()
{
    QString fileFormat("图片文件(*.jpg)");
    QString pathStr = QFileDialog::getOpenFileName(this,
                                                tr("上传头像"),
                                                ".",
                                                fileFormat
                                                );
    if(pathStr.isEmpty())
        return;

//    CurlUpload *curlUpload = new CurlUpload();
//    if(!curlUpload->uploadActorImage(pathStr)){
//        ui->label_showImage->setText("头像/n上传失败！");
//    }else{
        ui->label_showImage->setScaledContents(true);
        QImage image;
        image.load(pathStr);
        ui->label_showImage->setPixmap(QPixmap::fromImage(image));
//    }
}
