#include "activitylabel.h"
#include <QMouseEvent>
#include <QDebug>
ActivityLabel::ActivityLabel(QWidget * parent):
    QLabel(parent)
{

}

ActivityLabel::~ActivityLabel()
{

}

void ActivityLabel::mousePressEvent(QMouseEvent *ev)
{
    if(ev->button() == Qt::LeftButton)
     {

     }
}

void ActivityLabel::mouseReleaseEvent(QMouseEvent *ev)
{
    if(ev->button() == Qt::LeftButton)
     {        
      Q_UNUSED(ev)
       emit clicked();
     }
}

