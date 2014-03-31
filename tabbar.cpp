#include "tabbar.h"

TabBar::TabBar(QWidget *parent) : QTabBar(parent)
{
    this->tabWidget = (QTabWidget*)parent;
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(showContextMenu(const QPoint &)));
}

void TabBar::showContextMenu(const QPoint &point)
{
    int index = this->tabAt(point);
    if(index == -1)
    {
        return;
    }

    QWidget *selectedWidget = tabWidget->widget(index);

    QMenu menu(this);

    QAction closeAction(tr("&Close"), selectedWidget);
    connect(&closeAction, SIGNAL(triggered()), this, SLOT(close()));
    menu.addAction(&closeAction);

    QAction closeOthersAction(tr("Close &Others"), selectedWidget);
    connect(&closeOthersAction, SIGNAL(triggered()), this, SLOT(closeOthers()));
    if(this->count() > 1)
    {
        menu.addAction(&closeOthersAction);
    }

    QAction closeTabsToTheRightAction(tr("Close Tabs to the &Right"), selectedWidget);
    connect(&closeTabsToTheRightAction, SIGNAL(triggered()), this, SLOT(closeTabsToTheRight()));
    if(this->count() > index + 1)
    {
        menu.addAction(&closeTabsToTheRightAction);
    }

    menu.exec(this->mapToGlobal(point));
}

void TabBar::mouseReleaseEvent(QMouseEvent *mouseEvent)
{
    if(mouseEvent->button() == Qt::MidButton)
    {
        int tabIndex = this->tabAt(mouseEvent->pos());
        if(tabIndex != -1)
        {
            emit tabWidget->tabCloseRequested(tabIndex);
        }
    }
}

void TabBar::close()
{
    QObject *object = sender(); //action
    QObject *parent = object->parent();
    int index = tabWidget->indexOf((QWidget*)parent);
    emit tabWidget->tabCloseRequested(index);
}

void TabBar::closeOthers()
{
    QObject *object = sender(); //action
    QObject *parent = object->parent();
    int index = tabWidget->indexOf((QWidget*)parent);
    for(int i = this->count() - 1; i >= 0; i--)
    {
        if(i == index)
        {
            continue;
        }
        emit tabWidget->tabCloseRequested(i);
    }
}

void TabBar::closeTabsToTheRight()
{
    QObject *object = sender(); //action
    QObject *parent = object->parent();
    int index = tabWidget->indexOf((QWidget*)parent);
    for(int i = this->count() - 1; i > index; i--)
    {
        emit tabWidget->tabCloseRequested(i);
    }
}
