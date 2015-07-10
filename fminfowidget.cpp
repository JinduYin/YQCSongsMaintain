#include "fminfowidget.h"
#include "pagingtableview.h"
#include "tablemodel.h"
#include <QFile>
#include <QLabel>
#include <QPainter>
#include <QPushButton>
#include <QTableView>
#include <QHBoxLayout>
#include <QVBoxLayout>
FmInfoWidget::FmInfoWidget(QWidget *parent)
    : QWidget(parent)
{
    initWidget();
    readAndSetStyleSheet();
    initWidgetValue();
    setWidgetSize();

    label_image->setScaledContents(true);//图片随label调整大小
    label_image->setAlignment(Qt::AlignCenter);
    tableView_fm->setFmDelegate();
    tableView_fm->setWidgetBottomHidden();

    connect(pushButton_modify, &QPushButton::clicked, this, &FmInfoWidget::modifyFm);
    connect(pushButton_delete, &QPushButton::clicked, this, &FmInfoWidget::deleteFm);

    connect(tableView_fm, &PagingTableView::play, this, &FmInfoWidget::play);
}

FmInfoWidget::~FmInfoWidget()
{

}

void FmInfoWidget::readAndSetStyleSheet()
{
    QFile qss(":/qss/fminfo.qss");
    qss.open(QFile::ReadOnly);
    this->setStyleSheet(qss.readAll());
    qss.close();

    label_image_header->setObjectName("HeaderLabel");
    pushButton_delete->setObjectName("DeleteTextButton");
    pushButton_modify->setObjectName("TextButton");
}

void FmInfoWidget::initWidget()
{
    label_fmName = new QLabel(this);
    label_total = new QLabel(this);
    label_image_header = new QLabel(this);
    label_image = new QLabel(this);

    pushButton_modify = new QPushButton(this);
    pushButton_delete = new QPushButton(this);

    tableView_fm = new PagingTableView(this);

    image_layout = new QVBoxLayout();
    imageHeader_layout = new QVBoxLayout();

    image_layout->addWidget(label_image);
    image_layout->setContentsMargins(12, 40, 10, 0);
    image_layout->setSpacing(0);

    imageHeader_layout->addWidget(label_image_header);
    imageHeader_layout->addLayout(image_layout);
    imageHeader_layout->setContentsMargins(0, 0, 0, 0);
    imageHeader_layout->setSpacing(0);

    imageTable_layout = new QHBoxLayout();
    imageTable_layout->addLayout(imageHeader_layout);
    imageTable_layout->addWidget(tableView_fm);
    imageTable_layout->setContentsMargins(0, 0, 0, 0);
    imageTable_layout->setSpacing(0);

    fmName_layout = new QHBoxLayout();
    fmModify_layout = new QHBoxLayout();
    top_layout = new QHBoxLayout();

    fmName_layout->addWidget(label_fmName);
    fmName_layout->addWidget(label_total);
    fmName_layout->setContentsMargins(0, 0, 0, 0);
    fmName_layout->setSpacing(0);

    fmModify_layout->addWidget(pushButton_modify);
    fmModify_layout->addWidget(pushButton_delete);
    fmModify_layout->setContentsMargins(0, 0, 0, 0);
    fmModify_layout->setSpacing(10);

    top_layout->addLayout(fmName_layout);
    top_layout->addStretch();
    top_layout->addLayout(fmModify_layout);
    top_layout->setContentsMargins(0, 0, 0, 0);
    top_layout->setSpacing(0);

    vLayout = new QVBoxLayout();

    vLayout->addLayout(top_layout);
    vLayout->addLayout(imageTable_layout);
    vLayout->setContentsMargins(18, 0, 20, 0);
    vLayout->setSpacing(0);

    this->setLayout(vLayout);
}

void FmInfoWidget::initWidgetValue()
{
    label_image_header->setText("  封面");
    pushButton_delete->setText("删除");
    pushButton_modify->setText("修改");
}

void FmInfoWidget::setWidgetSize()
{
    label_image_header->setFixedHeight(42);
    label_image_header->setFixedWidth(210);

    label_image->setFixedHeight(188);
    label_image->setFixedWidth(188);

    label_fmName->setFixedHeight(40);
    label_total->setFixedHeight(40);

    pushButton_modify->setFixedWidth(35);
    pushButton_delete->setFixedWidth(35);
}

void FmInfoWidget::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void FmInfoWidget::initSql(MysqlQuery *sql)
{
    _sql = sql;
}

void FmInfoWidget::setFmName(const QString &fmname)
{
     label_fmName->setText(fmname);
}

void FmInfoWidget::setImage(const QString &path)
{
    QImage image;
    image.load(path);

    label_image->setPixmap(QPixmap::fromImage(image));
}

void FmInfoWidget::setTotal(const int &total)
{
    label_total->setText(QString("(总%1首歌曲)").arg(total));
}

void FmInfoWidget::setTotalRows(const int &total)
{
    tableView_fm->setTotal_Rows_Pages(total);
}

void FmInfoWidget::setTableValue(QSqlQuery &query)
{
    _query = query;
    tableView_fm->showUploadData(query, true);
}

QRect FmInfoWidget::getRightButtonGeometry()
{
     QRect fmNameG = label_fmName->geometry();
     QRect fmModiftG = pushButton_modify->geometry();


     QRect rightButton = QRect(fmNameG.x() + fmNameG.width() + 80,
                               fmNameG.y(),
                               fmModiftG.x() - 10,
                               fmNameG.height());

     return rightButton;
}

void FmInfoWidget::clear()
{
    tableView_fm->tableView->clear();
}

void FmInfoWidget::setImage(const QPixmap &pixmap)
{
//    if(path.isEmpty())
//        return;
//    QPixmap pixmap(path);
    label_image->setPixmap(pixmap);
}

void FmInfoWidget::play(const int &row, const int &)
{
    _query.seek(row);
    QString path = _query.value("_path").toString();
    if(!path.isEmpty())
        tableView_fm->palyVideo(path);
}


