#include "pagingtablewidget.h"
#include "activitylabel.h"
#include "yqcdelegate.h"
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QValidator>
#include <QPushButton>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QMenu>
#include <QHeaderView>
#include <QDebug>

#define DEFAULT_MINNUM   5
#define DEFAULT_ROWCOUNT 20  //每页默认行数

PagingTableWidget::PagingTableWidget(QWidget *parent) : QWidget(parent)
{
    total_page = 0;
    current_page = 0;
    total_Rows = 0;  //总共多少行
    row_page = DEFAULT_ROWCOUNT ;
    default_value = DEFAULT_ROWCOUNT;
    hiddenMenu = false;

    tableWidget = new QTableWidget(this);
    label_upPage = new ActivityLabel(this);
    label_nextPage = new ActivityLabel(this);
    label_showPage = new ActivityLabel(this);
    bottomWidget = new QWidget(this);
    connect(label_upPage, &ActivityLabel::clicked, this, &PagingTableWidget::up_page);
    connect(label_nextPage, &ActivityLabel::clicked, this, &PagingTableWidget::next_page);    


    label_upPage->setText("上一页");
    label_nextPage->setText("下一页");
    label_showPage->setText(" 页/共  页");  


    setTableWidget();
    widgetLayout();
    actionMenu();
}

PagingTableWidget::~PagingTableWidget()
{

}

void PagingTableWidget::setTableWidget()
{
    QPalette pal;
    pal.setColor(QPalette::Base, QColor(0xf7, 0xf6, 0xf6));
    pal.setColor(QPalette::AlternateBase, QColor(0xea, 0xea, 0xea));
    tableWidget->setPalette(pal);
    tableWidget->setAlternatingRowColors(true);

    tableWidget->setItemDelegate(new NoFocusDelegate());
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableWidget->horizontalHeader()->setHighlightSections(false);
    tableWidget->verticalHeader()->setVisible(false);
    tableWidget->setShowGrid(false);
    tableWidget->resizeRowsToContents();
    tableWidget->setHorizontalScrollBarPolicy((Qt::ScrollBarAlwaysOff));
    QHeaderView *headerWidget = tableWidget->horizontalHeader();
    headerWidget->setStretchLastSection(true);  ////最后一行适应空余部分

    tableWidget->show();
    tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
}

void PagingTableWidget::widgetLayout()
{
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addStretch();
    buttonLayout->addWidget(label_upPage);
    buttonLayout->addWidget(label_showPage);
    buttonLayout->addWidget(label_nextPage);
    bottomWidget->setLayout(buttonLayout);
    QLayout *bottomLayout= bottomWidget->layout();
    bottomLayout->setContentsMargins(0, 0, 0, 0);

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addWidget(tableWidget);
    vLayout->addWidget(bottomWidget);
    setLayout(vLayout);
    QLayout *layout =  this->layout();
    layout->setSpacing(6);
    layout->setContentsMargins(0, 0, 0, 0);
}

void PagingTableWidget::actionMenu()
{
    menuRight = new QMenu(tableWidget);
    select = new QAction("选择", this);
    allSelect = new QAction("全部选择", this);
    upPage = new QAction("上一页", this);
    nextPage = new QAction("下一页", this);
    firstPage = new QAction("首页", this);
    lastPage = new QAction("末页", this);
    checkPaging = new  QAction("分页显示", this);

    select->setCheckable(true);
    allSelect->setCheckable(true);
    checkPaging->setCheckable(true);
    checkPaging->setChecked(true);
    connect(select, &QAction::triggered, this, &PagingTableWidget::selectChecked);
    connect(allSelect, &QAction::triggered, this, &PagingTableWidget::selectAllChecked);
    connect(upPage, &QAction::triggered, this, &PagingTableWidget::up_page);
    connect(nextPage, &QAction::triggered, this, &PagingTableWidget::next_page);
    connect(firstPage, &QAction::triggered, this, &PagingTableWidget::first_page);
    connect(lastPage, &QAction::triggered, this, &PagingTableWidget::last_page);
    connect(checkPaging, &QAction::triggered, this, &PagingTableWidget::isPaging);
    connect(tableWidget, &QTableWidget::customContextMenuRequested,
            this, &PagingTableWidget::on_widget_customContextMenuRequested);
}

void PagingTableWidget::up_page()
{
    if (current_page <= 0)
        return;

    current_page--;
    show_page(current_page);
}

void PagingTableWidget::next_page()
{
    if (current_page >= total_page - 1)
        return;

    current_page++;
    show_page(current_page);
}

void PagingTableWidget::first_page()
{
    current_page = 0;
    show_page(current_page);
}

void PagingTableWidget::last_page()
{
    current_page = total_page - 1;
    show_page(current_page);
}

void PagingTableWidget::jump_page(const int page)
{
    current_page = page;
    show_page(current_page);
}

 void PagingTableWidget::show_page(int currentPage)
 {
    emit updateView(currentPage);
 }

void PagingTableWidget::isPaging(int checked)
{
    if(checked){ ///勾选

        label_upPage->setEnabled(true);
        label_nextPage->setEnabled(true);

        upPage->setEnabled(true);
        nextPage->setEnabled(true);
        firstPage->setEnabled(true);
        lastPage->setEnabled(true);

        setTotal_Rows_Pages(total_Rows);
        show_page(0);
    }else{

        label_upPage->setEnabled(false);
        label_nextPage->setEnabled(false);

        upPage->setEnabled(false);
        nextPage->setEnabled(false);
        firstPage->setEnabled(false);
        lastPage->setEnabled(false);

        row_page = total_Rows; //一页的行数
        total_page = 1;
        current_page = 0;
        show_page(0);
    }
}

void PagingTableWidget::rowPageEditFinish()
{
    int num = default_value;//rowPageLineEdit->text().toInt();
    if (num < DEFAULT_MINNUM)
       return;

    setTotal_Rows_Pages(total_Rows);
    row_page = num;
    show_page();
}

void PagingTableWidget::jumpEditFinish()
{
//    if (jumpPageLineEidt->text().toInt() < 1
//       || jumpPageLineEidt->text().toInt() > total_page)
//        return;
//    jump_page(jumpPageLineEidt->text().toInt() -1 );
}

void PagingTableWidget::jumppushButton()
{
//    if (jumpPageLineEidt->text().toInt() < 1
//       || jumpPageLineEidt->text().toInt() > total_page)
//        return;
    //    jump_page(jumpPageLineEidt->text().toInt() -1 );
}

void PagingTableWidget::selectChecked(int checked)
{
    if (checked){
        int currentRow = tableWidget->currentRow();
        tableWidget->item(currentRow, 0)->setCheckState(Qt::Checked);
    }else{
        int currentRow = tableWidget->currentRow();
        tableWidget->item(currentRow, 0)->setCheckState(Qt::Unchecked);
    }
}

void PagingTableWidget::selectAllChecked(int checked)
{
    select->setChecked(false);
    if (checked){
        for(int i=0; i<tableWidget->rowCount(); i++){
            tableWidget->item(i, 0)->setCheckState(Qt::Checked);

        }
        allSelect->setChecked(true);
    }else{
        for(int i=0; i<tableWidget->rowCount(); i++){
            tableWidget->item(i, 0)->setCheckState(Qt::Unchecked);
        }
        allSelect->setChecked(false);
    }
}

void PagingTableWidget::on_widget_customContextMenuRequested(const QPoint &pos)
{   
    menuRight->clear();
    emit addMenu(pos);
    if(hiddenMenu){
        return;
    }

    int row = tableWidget->rowAt(pos.y());    
    if (row == -1){
        menuRight->setEnabled(false);
    }else{
        menuRight->setEnabled(true);
        if(tableWidget->item(row, 0)->checkState() == Qt::Checked)
            select->setChecked(true);
        else
            select->setChecked(false);
    }

    menuRight->addAction(checkPaging);
    menuRight->addSeparator();
    menuRight->addAction(upPage);
    menuRight->addAction(nextPage);
    menuRight->addAction(firstPage);
    menuRight->addAction(lastPage);
    menuRight->exec(QCursor::pos());
}

int PagingTableWidget::setValidRowsCount()
{
    int rowsCount = row_page;
    if (total_page == 0)
        rowsCount = 0;
    if (current_page +1 == total_page){
       rowsCount = total_Rows - row_page * current_page;
    }

    return rowsCount;
}

void PagingTableWidget::setTotal_Rows_Pages(const int rowsSize)
{
    total_Rows = rowsSize;
    row_page = default_value; // rowPageLineEdit->text().toInt();
    if (row_page <= 0){
        row_page = default_value;
        total_page = 1;
    }

    total_page = total_Rows/row_page + (bool)(total_Rows%row_page);
}

void PagingTableWidget::setDefaultValue(const int &value)
{
    if (value >= DEFAULT_MINNUM)
        default_value = value;
}

void PagingTableWidget::setHiddenMenu(bool isHidden)
{
    hiddenMenu = isHidden;
}

