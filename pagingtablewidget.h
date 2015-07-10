#ifndef PAGINGTABLEWIDGET_H
#define PAGINGTABLEWIDGET_H

#include <QWidget>
class QMenu;
class QLabel;
class QCheckBox;
class QLineEdit;
class QPushButton;
class QTableWidget;
class ActivityLabel;

class PagingTableWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PagingTableWidget(QWidget *parent = 0);
    ~PagingTableWidget();

private:
    void setTableWidget();
    void widgetLayout();
    void actionMenu();

signals:
    void updateView(const int &currPage);
    void addMenu(const QPoint &pos);    
public slots:
    void up_page();
    void next_page();
    void first_page();
    void last_page();
    void jump_page(const int page);
    void show_page(int currentPage=0);

    void isPaging(int checked);
    void rowPageEditFinish();
    void jumpEditFinish();
    void jumppushButton();

    void selectChecked(int checked);
    void selectAllChecked(int checked);

    void on_widget_customContextMenuRequested(const QPoint &pos);

public:
    int setValidRowsCount(); ///获取有效行数
    void setTotal_Rows_Pages(const int rowsSize);
    void setDefaultValue(const int &value);
    void setHiddenMenu(bool isHidden);
public:
    int total_page; //总页码
    int current_page; //当前页码
    int total_Rows;  //总共行数
    int row_page; //一页行数

    int default_value;
    bool hiddenMenu;


    QTableWidget *tableWidget;
    ActivityLabel *label_upPage;
    ActivityLabel *label_nextPage;
    ActivityLabel *label_showPage;

    QWidget *bottomWidget;
    QMenu   *menuRight;
    QAction *cancelBlack;
    QAction *upPage;
    QAction *nextPage;
    QAction *firstPage;
    QAction *lastPage;
    QAction *checkPaging;
    QAction *select;
    QAction *cancelSelect;
    QAction *allSelect;
};

#endif // PAGINGTABLEWIDGET_H
