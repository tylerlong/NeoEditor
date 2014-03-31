#include "tabbar.h"

TabBar::TabBar(QWidget *parent) : QTabBar(parent)
{
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

    QTabWidget *tabWidget = (QTabWidget*)this->parentWidget();
    QWidget *selectedWidget = tabWidget->widget(index);

    QMenu menu(this);

    QAction closeAction(tr("&Close"), selectedWidget);
    connect(&closeAction, SIGNAL(triggered()), tabWidget, SLOT(close()));
    menu.addAction(&closeAction);

    QAction closeOthersAction(tr("Close &Others"), selectedWidget);
    connect(&closeOthersAction, SIGNAL(triggered()), tabWidget, SLOT(closeOthers()));
    if(this->count() > 1)
    {
        menu.addAction(&closeOthersAction);
    }

    QAction closeTabsToTheRightAction(tr("Close Tabs to the &Right"), selectedWidget);
    connect(&closeTabsToTheRightAction, SIGNAL(triggered()), tabWidget, SLOT(closeTabsToTheRight()));
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
            emit ((QTabWidget*)this->parentWidget())->tabCloseRequested(tabIndex);
        }
    }
}
