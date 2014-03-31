#ifndef TABBAR_H
#define TABBAR_H


#include <QtWidgets>

class TabBar : public QTabBar
{
    Q_OBJECT

public:
    TabBar(QWidget * parent = 0);

protected:
    void mouseReleaseEvent(QMouseEvent *mouseEvent);
};


#endif // TABBAR_H
