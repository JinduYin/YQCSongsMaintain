#ifndef ACTIVITYLABEL_H
#define ACTIVITYLABEL_H

#include <QLabel>
#include <QObject>
class ActivityLabel : public QLabel
{   
    Q_OBJECT
public:
    ActivityLabel(QWidget * parent = 0);
    ~ActivityLabel(void);
public:
    void mousePressEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent * ev);
signals:
    void clicked();
public slots:
};

#endif // ACTIVITYLABEL_H
