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

private slots:
    void showContextMenu(const QPoint &point);
};


#endif // TABBAR_H
