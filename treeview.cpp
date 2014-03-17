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

        QAction *renameFileAction = new QAction(tr("&Rename File"), &menu);
        connect(renameFileAction, SIGNAL(triggered()), this, SLOT(renameFile()));
        menu.addAction(renameFileAction);
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

            QAction *renameFolderAction = new QAction(tr("&Rename Folder"), &menu);
            connect(renameFolderAction, SIGNAL(triggered()), this, SLOT(renameFolder()));
            menu.addAction(renameFolderAction);
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
    int i = QMessageBox::warning(this, tr("Delete File"), QString("Are you sure to delete file %1 ?").arg(filePath),
                                 QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok);
    if(QMessageBox::Cancel == i)
    {
        return;
    }
    bool r = fileSystemModel->remove(this->currentIndex());
    if(r)
    {
        emit MainWindow::GetInstance()->deleteFileRequested(filePath);
    }
}

void TreeView::renameFile()
{
    QFileSystemModel *fileSystemModel = (QFileSystemModel*)this->model();
    QFileInfo fileInfo = fileSystemModel->fileInfo(this->currentIndex());
    if(!fileInfo.isFile())
    {
        return;
    }
    QString filePath = fileInfo.absoluteFilePath();
    QString fileName = QInputDialog::getText(this, tr("Rename File"), filePath, QLineEdit::Normal, fileInfo.fileName());
    if(fileName.isEmpty() || fileName == fileInfo.fileName())
    {
        return;
    }
    QFile file(filePath);
    QString newFilePath = QDir(fileInfo.absolutePath()).absoluteFilePath(fileName);
    bool r = file.rename(newFilePath);
    if(r)
    {
        emit MainWindow::GetInstance()->renameFileRequested(filePath, newFilePath);
    }
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
    bool r = file.open(QIODevice::WriteOnly);
    file.close();
    if(r)
    {
        emit MainWindow::GetInstance()->openFileRequested(filePath);
    }
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
    int i = QMessageBox::warning(this, tr("Delete Folder"), QString("Are you sure to delete folder %1 ?").arg(folderPath),
                                 QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok);
    if(QMessageBox::Cancel == i)
    {
        return;
    }
    bool r = fileSystemModel->remove(this->currentIndex());
    if(r)
    {
        emit MainWindow::GetInstance()->deleteFolderRequested(folderPath);
    }
}

void TreeView::renameFolder()
{
    QFileSystemModel *fileSystemModel = (QFileSystemModel*)this->model();
    QFileInfo fileInfo = fileSystemModel->fileInfo(this->currentIndex());
    if(!fileInfo.isDir())
    {
        return;
    }
    QString folderPath = fileInfo.absoluteFilePath();
    QString folderName = QInputDialog::getText(this, tr("Rename Folder"), folderPath, QLineEdit::Normal, fileInfo.fileName());
    if(folderName.isEmpty() || folderName == fileInfo.fileName())
    {
        return;
    }
    QString newFolderPath = fileInfo.absoluteDir().absoluteFilePath(folderName);
    QDir dir;
    bool r = dir.rename(folderPath, newFolderPath);
    if(r)
    {
        emit MainWindow::GetInstance()->renameFolderRequested(folderPath, newFolderPath);
    }
}
