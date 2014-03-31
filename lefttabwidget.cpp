#include "lefttabwidget.h"
#include "treeview.h"
#include "tabbar.h"

LeftTabWidget::LeftTabWidget(QWidget *parent) : QTabWidget(parent)
{
    TabBar *tabBar = new TabBar(this);
    this->setTabBar(tabBar);
    this->mainWindow = (QMainWindow*)parent;
    this->setTabsClosable(true);
    connect(this, SIGNAL(tabCloseRequested(int)), this, SLOT(close(int)));
}

void LeftTabWidget::close(int index)
{
    this->removeTab(index);
}

void LeftTabWidget::showFolderTree(QString folderPath)
{
    QDir dir(folderPath);
    if(!dir.exists() || !dir.isAbsolute() || !dir.isReadable())
    {
        return;
    }
    for(int i = 0; i < this->count(); i++)
    {
        if(folderPath == this->tabToolTip(i))
        {
            this->setCurrentIndex(i);
            return;
        }
    }

    TreeView *treeView = new TreeView(this, folderPath);
    connect(treeView, SIGNAL(doubleClicked(QModelIndex)), mainWindow, SLOT(openFile(QModelIndex)));
    int index = this->addTab(treeView, QDir(folderPath).dirName());
    treeView->setFocus();
    this->setTabToolTip(index, folderPath);
    this->setCurrentIndex(index);
}
