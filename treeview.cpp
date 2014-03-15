#include "treeview.h"

TreeView::TreeView(QWidget* parent) : QTreeView(parent)
{
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(showContextMenu(const QPoint &)));
}

void TreeView::showContextMenu(const QPoint &point)
{
    QModelIndex currentIndex = this->indexAt(point);
    if(!currentIndex.isValid())
    {
        return;
    }
    QFileSystemModel *fileSystemModel = (QFileSystemModel*)this->model();
    QFileInfo fileInfo = fileSystemModel->fileInfo(currentIndex);
    if(fileInfo.isFile())
    {
        QMenu menu(this);
        QAction deleteFileAction(tr("&Delete File"), this);
        connect(&deleteFileAction, SIGNAL(triggered()), this, SLOT(deleteFile()));
        menu.addAction(&deleteFileAction);
        menu.exec(this->mapToGlobal(point));
    }
}

void TreeView::deleteFile()
{
    qDebug() << "delete file";
}
