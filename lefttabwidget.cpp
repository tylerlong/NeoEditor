#include "lefttabwidget.h"

LeftTabWidget::LeftTabWidget(QWidget *parent) : QTabWidget(parent)
{
    this->setTabsClosable(true);
    connect(this, SIGNAL(tabCloseRequested(int)), this, SLOT(close(int)));
}

void LeftTabWidget::close(int index)
{
    this->removeTab(index);
}
