#ifndef ITEMDELEGATE_H
#define ITEMDELEGATE_H


#include <QStyledItemDelegate>
#include <QListView>
#include <QMap>
class LibListView;

class ItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    ItemDelegate(QObject * parent=0);
    virtual ~ItemDelegate(){}
    void paint(QPainter * painter,const QStyleOptionViewItem & option,const QModelIndex & index) const;
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);   

    void setIconSize(QSize size);
    void setExpandIcon(QString expandIconName);
    void setcollapseIcon(QString collapseIconName);

//    void setExpandOrColl(bool _exp);

signals:
    void expanded(int row, bool isexpanded);

private:    
    LibListView *m_listView;
    int m_pixmapHeight;
    int m_pixmapWidth;
    QString m_expandIconName;
    QString m_collapseIconName;

    QMap<QModelIndex, int> iconStatus;
//    bool isexpanded;
};

#endif // ITEMDELEGATE_H
