#ifndef TABBAR_H
#define TABBAR_H


#include <QtWidgets>

class TabBar : public QTabBar
{
    Q_OBJECT

public:
    TabBar(QTabWidget *parent);

protected:
    void mouseReleaseEvent(QMouseEvent *mouseEvent);

private:
    QTabWidget *tabWidget;

private slots:
    void showContextMenu(const QPoint &point);
    void close();
    void closeOthers();
    void closeTabsToTheRight();
};


#endif // TABBAR_H
