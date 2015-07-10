#include "ItemDelegate.h"
#include "liblistview.h"
#include "enuminfo.h"
#include <QPainter>
#include <QMouseEvent>
#include <QStyledItemDelegate>
#include <QToolTip>
#include <QApplication>


ItemDelegate::ItemDelegate(QObject * parent)
    : QStyledItemDelegate(parent),
      m_pixmapHeight(8),
      m_pixmapWidth(8)
{

    m_expandIconName = ":/arrow/images/expansion.png";
    m_collapseIconName = ":/arrow/images/receives.png";
}

void ItemDelegate::setIconSize(QSize size)
{
    m_pixmapHeight = size.height();
    m_pixmapWidth = size.width();
}

void ItemDelegate::setExpandIcon(QString expandIconName)
{
    m_expandIconName = expandIconName;
}

void ItemDelegate::setcollapseIcon(QString collapseIconName)
{
    m_collapseIconName = collapseIconName;
}

void ItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionViewItem  viewOption(option);
    if (viewOption.state & QStyle::State_HasFocus)
    {
        viewOption.state = viewOption.state ^ QStyle::State_HasFocus;
    }

    QStyledItemDelegate::paint(painter, viewOption, index);

    int row = index.row();
    if(!(row == widItem_songsLib
       || row == widItem_songsLibOnline
       || row == widItem_list
       || row == widItem_black
       || row == widItem_setInfo))
        return;

    int status = -1;
    QPixmap pixmap;
    status = iconStatus.value(index);
    if(status != icon_normal && status != icon_pressed){
        (const_cast<ItemDelegate *>(this))->iconStatus.insert(index, icon_normal);
        pixmap = m_collapseIconName;
    }

    if(status == icon_normal)
        pixmap = m_collapseIconName;
    else if(status == icon_pressed){
        pixmap = m_expandIconName;
    }


    int height = (viewOption.rect.height() - m_pixmapWidth) / 2;
//    QPixmap pixmap = bExpanded ? QPixmap(m_expandIconName) : QPixmap(m_collapseIconName);
    QRect decorationRect = QRect(viewOption.rect.left() + viewOption.rect.width() - 30, viewOption.rect.top() + height, m_pixmapHeight, m_pixmapWidth);
    painter->drawPixmap(decorationRect, pixmap);
}

bool ItemDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
//    int height = (option.rect.height() - m_pixmapWidth) / 2;
    QRect decorationRect = option.rect;

    QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
    if (event->type() == QEvent::MouseButtonPress && decorationRect.contains(mouseEvent->pos()))
    {
        int row = index.row();
        int status = iconStatus.value(index);
        if (status == icon_normal){
            iconStatus.insert(index, icon_pressed);
            emit expanded(row, false);
        }else if(status == icon_pressed){
            iconStatus.insert(index, icon_normal);
            emit expanded(row, true);
        }
    }

    if (event->type() == QEvent::MouseMove && decorationRect.contains(mouseEvent->pos()))
    {

    }
    else
    {
        QCursor cursor(Qt::ArrowCursor);
        QApplication::setOverrideCursor(cursor);
    }

    return QStyledItemDelegate::editorEvent(event, model, option, index);
}

