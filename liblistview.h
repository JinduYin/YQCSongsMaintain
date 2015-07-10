#ifndef LIBLISTVIEW_H
#define LIBLISTVIEW_H

#include <QWidget>
#include <QTreeWidget>
#include <QListView>
#include <QPushButton>
#include <QMenu>
#include <QAction>
#include "liblistview.h"
#include "util.h"
class QStandardItemModel;

class LibListView : public QWidget
{
Q_OBJECT

public:
   explicit LibListView(QWidget *parent = 0);
   ~LibListView();

    void setupModelData();    
private:
    void initHiddenItem();
public slots:
    void setHiddenItem(int row, bool isexpanded);

protected:
   void paintEvent(QPaintEvent *);  
private slots:   
   void treeViewCustomContextMenuRequested(const QPoint &pos);

   void clickedRow(const QModelIndex & index);
signals:
   void currentPage(const int &page);

private:
//   QTreeView *m_treeView;
   QListView *m_listView;
   QStandardItemModel *model;
   QRect m_rect;
   QMenu *m_menu;
   int m_height;
   int m_shadowSize;

   QList<ToolUtil> toolList;
};

#endif // LIBLISTVIEW_H
