#include "listinfowidget.h"
#include "pagingtableview.h"
#include "tablemodel.h"
#include <QFile>
#include <QLabel>
#include <QPainter>
#include <QComboBox>
#include <QTableView>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDebug>
ListInfoWidget::ListInfoWidget(QWidget *parent, MysqlQuery *sql)
    : QWidget(parent),
      _sql(sql)
{
    initWidget();
    readAndSetStyleSheet();        
    tableView_listInfo->setWidgetBottomHidden();
    tempEdit->setHidden(true);
    connect(tempEdit, &QLineEdit::editingFinished, this, &ListInfoWidget::editFinish);

    connect(tableView_listInfo, &PagingTableView::modify, this, &ListInfoWidget::modifyList);
    connect(tableView_listInfo, &PagingTableView::dele, this, &ListInfoWidget::deleteList);
    connect(tableView_listInfo, &PagingTableView::add, this, &ListInfoWidget::addList);
}

ListInfoWidget::~ListInfoWidget()
{

}

void ListInfoWidget::readAndSetStyleSheet()
{
    QFile qss(":/qss/songquery.qss");
    qss.open(QFile::ReadOnly);
    this->setStyleSheet(qss.readAll());
    qss.close();

    this->setObjectName("Widget");
    widgetCenter->setObjectName("CenterWidget");
    label_title->setObjectName("TitleLabel");
    label_select->setObjectName("Label");
    combobox_select->setObjectName("Combobox");

    tableView_listInfo->setObjectName("ResultTableView");
}

void ListInfoWidget::initWidget()
{
    widgetCenter = new QWidget(this);
    label_title = new QLabel(this);
    label_select = new QLabel(widgetCenter);
    combobox_select = new QComboBox(widgetCenter);
    tableView_listInfo = new PagingTableView(this);

    edit = new QLineEdit(this);
    tempEdit = new QLineEdit(this);

    label_title->setFixedHeight(60);
    combobox_select->setFixedHeight(36);
    combobox_select->setFixedWidth(150);
    label_select->setText("选择内容");

    title_layout = new QHBoxLayout();

    title_layout->addWidget(label_title);
    title_layout->setContentsMargins(20, 0, 0, 0);
    title_layout->setSpacing(0);

    select_layout = new QHBoxLayout();
    select_layout->addWidget(label_select);
    select_layout->addWidget(combobox_select);
    select_layout->addStretch();
    select_layout->setContentsMargins(46, 15, 0, 15);
    select_layout->setSpacing(10);
    widgetCenter->setLayout(select_layout);

    tableView_layout = new QVBoxLayout();
    vLayout = new QVBoxLayout();

    tableView_layout->addWidget(tableView_listInfo);
    tableView_layout->setContentsMargins(12, 20, 12, 3);
    tableView_layout->setSpacing(0);

    vLayout->addLayout(title_layout);
    vLayout->addWidget(widgetCenter);
    vLayout->addLayout(tableView_layout);
    vLayout->setContentsMargins(0, 0, 0, 0);
    vLayout->setSpacing(0);

    this->setLayout(vLayout);

}

void ListInfoWidget::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void ListInfoWidget::initSongInfo(int itemIndex)
{    
    _itemIndex = itemIndex;
    label_title->setText("歌曲资料");

    QStringList list;
    list << "歌曲语种" << "歌曲分类" << "歌曲分辨率"
         << "歌曲质量" << "歌曲来源" << "版本类型"
         << "歌曲节奏" << "高音类型";
    combobox_select->clear();
    combobox_select->addItems(list);

    disconnect(combobox_select, SIGNAL(currentIndexChanged(int)), 0, 0);
    connect(combobox_select, SIGNAL(currentIndexChanged(int)),
            this, SLOT(setSongViewValue(int)));

    setSongViewValue(0);
}

void ListInfoWidget::initSingerInfo(int itemIndex)
{
    _itemIndex = itemIndex;
    label_title->setText("歌星资料");    

    QStringList list;
    list << "歌星区域";
    combobox_select->clear();
    combobox_select->addItems(list);

    disconnect(combobox_select, SIGNAL(currentIndexChanged(int)), 0, 0);
    connect(combobox_select, SIGNAL(currentIndexChanged(int)),
            this, SLOT(setSingerViewValue(int)));

   setSingerViewValue(0);
}

void ListInfoWidget::initListInfo(int itemIndex)
{    
    _itemIndex = itemIndex;
    label_title->setText("排行榜资料");
    widgetCenter->setHidden(false);

    QStringList list;
    list << "选秀热歌榜" << "网络排行榜";
    combobox_select->clear();
    combobox_select->addItems(list);

    disconnect(combobox_select, SIGNAL(currentIndexChanged(int)), 0, 0);
    connect(combobox_select, SIGNAL(currentIndexChanged(int)),
            this, SLOT(setListViewValue(int)));

   setSingerViewValue(0);

    setListViewValue(0);
}

void ListInfoWidget::setSongViewValue(const int &index)
{
    tempEdit->setHidden(true);
    if(!values.isEmpty())
        values.clear();
    if(index == 0)
        _sql->getMediaLanguage(values);
    else if(index == 1)
        _sql->getMediaType(values);
    else if(index == 2)
        _sql->getMediaResolution(values);
    else if(index == 3)
        _sql->getMediaQuality(values);
    else if(index == 4)
        _sql->getMediaSource(values);
    else if(index == 5)
        _sql->getMediaVersion(values);
    else if(index == 6)
        _sql->getMediaRthym(values);
    else if(index == 7)
        _sql->getMediaPitch(values);
    else
        return;

    setModelData(values);
}

void ListInfoWidget::setSingerViewValue(const int &index)
{
    tempEdit->setHidden(true);
    if(!values.isEmpty())
        values.clear();
    if(index == 0)
        _sql->getNation(values);
    else
        return;

    setModelData(values);
}

void ListInfoWidget::setListViewValue(const int &index)
{
    tempEdit->setHidden(true);
    if(!values.isEmpty())
        values.clear();
    if(index == 0)
        _sql->getMediaListHot(values);
    else if(index == 1)
        _sql->getMediaListNet(values);
    else
        return;

    setModelData(values);
}

void ListInfoWidget::setModelData(QMap<int, QString> &values)
{    
    if(!datas.isEmpty())
        datas.clear();

    tableView_listInfo->tableView->clear();    
    QMap<int, QString>::iterator it = values.begin();
    QStringList row;
    while(it != values.end()){
        row.clear();
        row.append(QString::number(it.key()));
        row.append(it.value());

        datas.append(row);
        it++;
    }

    it--;
    row.clear();
    if(values.isEmpty()){
        row.append(QString::number(1));
    }else
        row.append(QString::number(it.key() + 1));
    row.append("");
    datas.append(row);

    int rows = datas.size();
    edit->setGeometry(258, 155+(rows*38), 100, 30);
    tableView_listInfo->setInfoDelegate(datas.size());
    if(!datas.isEmpty())
        tableView_listInfo->setModelValue(datas);
}

void ListInfoWidget::modifyList(const int &row)
{
    QModelIndex item = tableView_listInfo->model->index(row, 1);
    QString text = item.data().toString();
    if(text.isEmpty())
        return;

    tempEdit->setHidden(false);
    tempEdit->setGeometry(258, 155+((row+1)*38), 100, 30);
    tempEdit->setText(text);

    src = text;
}

void ListInfoWidget::deleteList(const int &row)
{
    QModelIndex item = tableView_listInfo->model->index(row, 1);
    QString text = item.data().toString();
    if(text.isEmpty())
        return;

    QMessageBox box(QMessageBox::Information, "提示", "是否确定删除");
    box.setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
    box.setButtonText(QMessageBox::Ok, "是(&Y)");
    box.setButtonText(QMessageBox::Cancel, "否(&N)");
    if (box.exec() != QMessageBox::Ok)
        return;


    int index = combobox_select->currentIndex();
    if(_itemIndex == stacked_setmediainfo){

        if(_sql->deleteMediaListSongs(index, text))
            setSongViewValue(index);
    }else if(_itemIndex == stacked_setactorinfo){

        if( _sql->deleteMediaListSinger(text))
            setSingerViewValue(index);

    }else if(_itemIndex == stacked_setlistinfo){

        if(_sql->deleteMediaListInfo(index, text))
            setListViewValue(index);
    }

}

void ListInfoWidget::addList(const int &)
{
    QString text = edit->text();
    qDebug() << "size : " << text.size();
    if(text.isEmpty()){
        QMessageBox::information(this, "提示", "添加不能为空！");
        return;
    }


    int index = combobox_select->currentIndex();
    if(_itemIndex == stacked_setmediainfo){
        if(text.size() > 10){
            QMessageBox::information(this, "提示", "类型不能超过十个字符!");
            return;
        }

        if(_sql->isMediaListExistSongs(index, text)){
            QString prompt(QString("类型\"%1\"存在重复!").arg(text));
            QMessageBox::information(this, "提示", prompt, QMessageBox::Ok);
            return;
        }

        _sql->insertMediaListSongs(index, text);
        setSongViewValue(index);
        edit->clear();

    }else if(_itemIndex == stacked_setactorinfo){

        if(text.size() > 10){
            QMessageBox::information(this, "提示", "类型不能超过十个字符!");
            return;
        }

        if(_sql->isMediaListExistSinger(text)){
            QString prompt(QString("区域\"%1\"存在重复!").arg(text));
            QMessageBox::information(this, "提示", prompt, QMessageBox::Ok);
            return;
        }

        _sql->insertMediaListSinger(text);
        setSingerViewValue(index);
        edit->clear();

    }else if(_itemIndex == stacked_setlistinfo){

        if(text.size() > 10){
            QMessageBox::information(this, "提示", "类型不能超过十个字符!");
            return;
        }

        if(_sql->isMediaListExistInfo(index, text)){
            QString prompt(QString("区域\"%1\"存在重复!").arg(text));
            QMessageBox::information(this, "提示", prompt, QMessageBox::Ok);
            return;
        }

        _sql->insertMediaListInfo(index, text);
        setListViewValue(index);
        edit->clear();
    }
}

void ListInfoWidget::editFinish()
{
    dest = tempEdit->text();
    if(src.compare(dest) == 0)
        return;

    QMessageBox box(QMessageBox::Information, "提示", "是否确定修改");
    box.setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
    box.setButtonText(QMessageBox::Ok, "是(&Y)");
    box.setButtonText(QMessageBox::Cancel, "否(&N)");
    if (box.exec() != QMessageBox::Ok)
        return;


    int index = combobox_select->currentIndex();
    if(_sql->isMediaListExistSongs(index, dest)){
        QString prompt(QString("类型\"%1\"存在重复!").arg(dest));
        QMessageBox::information(this, "提示", prompt, QMessageBox::Ok);
        return;
    }

    if(dest.isEmpty() || src.isEmpty()){
        QMessageBox::information(this, "提示", "修改内容不能是空！");
        return;
    }


    if(_itemIndex == stacked_setmediainfo){

        if(_sql->updateMediaListSongs(index, src, dest))
            setSongViewValue(index);
    }else if(_itemIndex == stacked_setactorinfo){

        if(_sql->updateMediaListSinger(src, dest))
            setSingerViewValue(index);
    }else if(_itemIndex == stacked_setlistinfo){

        if(_sql->updateMediaListInfo(index, src, dest))
            setListViewValue(index);
    }

    tempEdit->setHidden(true);
}

