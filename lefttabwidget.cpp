#include "lefttabwidget.h"

LeftTabWidget::LeftTabWidget(QWidget *parent) : QTabWidget(parent)
{
    this->setTabsClosable(true);
    connect(this, SIGNAL(tabCloseRequested(int)), parent, SLOT(closeLeftTab(int)));
}
