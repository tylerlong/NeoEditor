#include "mainwindow.h"
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
        currentIndex = this->rootIndex();
        this->setCurrentIndex(this->rootIndex());
    }
    QFileSystemModel *fileSystemModel = (QFileSystemModel*)this->model();
    QFileInfo fileInfo = fileSystemModel->fileInfo(currentIndex);
    if(!(fileInfo.isFile()||fileInfo.isDir()))
    {
        return;
    }

    QMenu menu(this);
    if(fileInfo.isFile())
    {
        QAction *deleteFileAction = new QAction(tr("&Delete File"), &menu);
        connect(deleteFileAction, SIGNAL(triggered()), this, SLOT(deleteFile()));
        menu.addAction(deleteFileAction);
    }
    else if(fileInfo.isDir())
    {
        QAction *newFileAction = new QAction(tr("&New File"), &menu);
        connect(newFileAction, SIGNAL(triggered()), this, SLOT(newFile()));
        menu.addAction(newFileAction);

        QAction *newFolderAction = new QAction(tr("&New Folder"), &menu);
        connect(newFolderAction, SIGNAL(triggered()), this, SLOT(newFolder()));
        menu.addAction(newFolderAction);

        if(currentIndex != this->rootIndex())
        {
            QAction *deleteFolderAction = new QAction(tr("&Delete Folder"), &menu);
            connect(deleteFolderAction, SIGNAL(triggered()), this, SLOT(deleteFolder()));
            menu.addAction(deleteFolderAction);
        }
    }
    menu.exec(this->mapToGlobal(point));
}

void TreeView::deleteFile()
{
    QFileSystemModel *fileSystemModel = (QFileSystemModel*)this->model();
    QFileInfo fileInfo = fileSystemModel->fileInfo(this->currentIndex());
    if(!fileInfo.isFile())
    {
        return;
    }
    QString filePath = fileInfo.absoluteFilePath();
    int r = QMessageBox::warning(this, tr("Delete File"), QString("Are you sure to delete file %1 ?").arg(filePath),
                                 QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok);
    if(QMessageBox::Cancel == r)
    {
        return;
    }
    fileSystemModel->remove(this->currentIndex());

    MainWindow *mainWindow = (MainWindow*)QApplication::topLevelWidgets()[0];
    emit mainWindow->deleteFileRequested(filePath);
}

void TreeView::newFile()
{
    QFileSystemModel *fileSystemModel = (QFileSystemModel*)this->model();
    QFileInfo fileInfo = fileSystemModel->fileInfo(this->currentIndex());
    if(!fileInfo.isDir())
    {
        return;
    }
    QString folderPath = fileInfo.absoluteFilePath();
    QString fileName = QInputDialog::getText(this, tr("New File"), folderPath);
    if(fileName.isEmpty())
    {
        return;
    }
    QString filePath = QDir(folderPath).absoluteFilePath(fileName);
    QFile file(filePath);
    if(file.exists())
    {
        return;
    }
    file.open(QIODevice::WriteOnly);
    file.close();

    MainWindow *mainWindow = (MainWindow*)QApplication::topLevelWidgets()[0];
    QThread::msleep(100);
    emit mainWindow->openFileRequested(filePath);
}

void TreeView::newFolder()
{
    QFileSystemModel *fileSystemModel = (QFileSystemModel*)this->model();
    QFileInfo fileInfo = fileSystemModel->fileInfo(this->currentIndex());
    if(!fileInfo.isDir())
    {
        return;
    }
    QString folderPath = fileInfo.absoluteFilePath();
    QString folderName = QInputDialog::getText(this, QString("New Folder"), folderPath);
    if(folderName.isEmpty())
    {
        return;
    }
    fileSystemModel->mkdir(this->currentIndex(), folderName);
}

void TreeView::deleteFolder()
{
    QFileSystemModel *fileSystemModel = (QFileSystemModel*)this->model();
    QFileInfo fileInfo = fileSystemModel->fileInfo(this->currentIndex());
    if(!fileInfo.isDir())
    {
        return;
    }
    QString folderPath = fileInfo.absoluteFilePath();
    int r = QMessageBox::warning(this, tr("Delete Folder"), QString("Are you sure to delete folder %1 ?").arg(folderPath),
                                 QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok);
    if(QMessageBox::Cancel == r)
    {
        return;
    }
    fileSystemModel->remove(this->currentIndex());
}
