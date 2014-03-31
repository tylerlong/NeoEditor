#include "tabbar.h"

TabBar::TabBar(QWidget *parent) : QTabBar(parent)
{
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
