#include <typeinfo>
#include "mainwindow.h"
#include "lefttabwidget.h"
#include "righttabwidget.h"
#include "webview.h"
#include "treeview.h"

MainWindow::MainWindow()
{
    //initial window size
    int width = 1024;
    int height = 576;
    this->resize(width, height);
    QDesktopWidget *desktop = QApplication::desktop();
    int marginLeft = (desktop->width() - width) / 2;
    int marginTop = (desktop->height() - height) / 2;
    this->move(marginLeft, marginTop);

    //title and icon
    this->setWindowTitle(tr("NeoEditor"));
    this->setWindowIcon(QIcon(":/images/neo.png"));

    //style
    this->setStyleSheet("QTreeView{border: 0;} QTabWidget {border: 0;}");
    this->setContextMenuPolicy(Qt::NoContextMenu);

    //tool bar
    QToolBar *fileToolBar = new QToolBar(tr("&File"), this);
    fileToolBar->setObjectName("fileToolBar");
    this->addToolBar(Qt::LeftToolBarArea, fileToolBar);

    QAction *openFolderAction = new QAction(tr("&Open Folder"), this);
    openFolderAction->setIcon(QIcon(":/images/folder-open.svg"));
    openFolderAction->setShortcut(QKeySequence::Open);
    openFolderAction->setStatusTip(tr("Open Folder"));
    connect(openFolderAction, SIGNAL(triggered()), this, SLOT(openFolder()));
    fileToolBar->addAction(openFolderAction);

    QAction *saveFileAction = new QAction(tr("&Save File"), this);
    saveFileAction->setIcon(QIcon(":/images/document-save.svg"));
    saveFileAction->setShortcut(QKeySequence::Save);
    saveFileAction->setStatusTip("Save File");
    connect(saveFileAction, SIGNAL(triggered()), this, SLOT(saveFile()));
    fileToolBar->addAction(saveFileAction);

    //right panel
    rightTabWidget = new RightTabWidget(this);
    rightTabWidget->tabBar()->setIconSize(QSize(20, 20));
    connect(this, SIGNAL(openFileRequested(QString)), rightTabWidget, SLOT(open(QString)));
    connect(this, SIGNAL(deleteFileRequested(QString)), rightTabWidget, SLOT(remove(QString)));
    connect(this, SIGNAL(deleteFolderRequested(QString)), rightTabWidget, SLOT(removeFolder(QString)));
    connect(this, SIGNAL(renameFileRequested(QString,QString)), rightTabWidget, SLOT(rename(QString, QString)));
    connect(this, SIGNAL(renameFolderRequested(QString,QString)), rightTabWidget, SLOT(renameFolder(QString, QString)));

    QToolBar *helpToolBar = new QToolBar(tr("&Help"), this);
    helpToolBar->setObjectName("helpToolBar");
    this->addToolBar(Qt::LeftToolBarArea, helpToolBar);

    QAction *keyboardShortcutsAction = new QAction(tr("&Keyboard Shortcuts"), this);
    keyboardShortcutsAction->setIcon(QIcon(":/images/preferences-desktop-keyboard-shortcuts.svg"));
    keyboardShortcutsAction->setStatusTip("Keyboard Shortcuts");
    connect(keyboardShortcutsAction, SIGNAL(triggered()), this, SLOT(keyboardShortcuts()));
    helpToolBar->addAction(keyboardShortcutsAction);

    QAction *aboutAction = new QAction(tr("&About NeoEditor"), this);
    aboutAction->setIcon(QIcon(":/images/neo.png"));
    aboutAction->setStatusTip("About NeoEditor");
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));
    helpToolBar->addAction(aboutAction);

    //left panel
    leftTabWidget = new LeftTabWidget(this);

    //layout
    splitter = new QSplitter(Qt::Horizontal);
    splitter->addWidget(leftTabWidget);
    splitter->addWidget(rightTabWidget);
    this->setCentralWidget(splitter);
    splitter->setStretchFactor(1, 1);
    QList<int> list;
    list << 256 << 1; //right panel takes all the extra space
    splitter->setSizes(list);
    splitter->setHandleWidth(1);

    readSettings();
}

void MainWindow::openFolder()
{
    QString folderPath = QFileDialog::getExistingDirectory(this, tr("Open Directory"), QDir::homePath(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if(folderPath != NULL)
    {
        leftTabWidget->showFolderTree(folderPath);
    }
}

void MainWindow::saveFile()
{
    QWidget *widget = rightTabWidget->currentWidget();
    if(widget == 0)
    {
        return;
    }
    WebView *webView = (WebView*)widget;
    webView->save();
}

void MainWindow::openFile(QModelIndex modelIndex)
{
    TreeView *treeView = (TreeView*)sender();
    QFileSystemModel *fileSystemModel = (QFileSystemModel*)treeView->model();
    emit openFileRequested(fileSystemModel->filePath(modelIndex));
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About NeoEditor"), tr("<strong>NeoEditor 0.2.0</strong><br/><br/>An extensible text editor for the 21st Century.<br/><br/>Copyright 2014 <a href=\"https://github.com/orgs/NeoEditor\">https://github.com/orgs/NeoEditor</a>. All rights reserved.<br/><br/>The program is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE."));
}

void MainWindow::keyboardShortcuts()
{
    QDesktopServices::openUrl(QUrl("https://github.com/ajaxorg/ace/wiki/Default-Keyboard-Shortcuts"));
}

void MainWindow::closeEvent(QCloseEvent *closeEvent)
{
    writeSettings();
    for(int i = rightTabWidget->count() - 1; i >= 0 ; i--)
    {
        emit rightTabWidget->tabCloseRequested(i);
    }
    if(rightTabWidget->count() == 0)
    {
        closeEvent->accept();
    }
    else
    {
        closeEvent->ignore();
    }
}

void MainWindow::writeSettings()
{
    QSettings settings("https://github.com/orgs/NeoEditor", "NeoEditor");

    //layout
    settings.setValue("geometry", saveGeometry());
    settings.setValue("mainWindowState", this->saveState());
    settings.setValue("splitterState", splitter->saveState());

    //left panel
    QStringList openedFolders;
    for(int i = 0; i < leftTabWidget->count(); i++)
    {
        openedFolders << leftTabWidget->tabToolTip(i);
    }
    settings.setValue("openedFolders", openedFolders);
    settings.setValue("currentFolder", leftTabWidget->tabToolTip(leftTabWidget->currentIndex()));

    //rightPanel
    QStringList openedFiles;
    for(int i = 0; i < rightTabWidget->count(); i++)
    {
        openedFiles << rightTabWidget->tabToolTip(i);
    }
    settings.setValue("openedFiles", openedFiles);
    settings.setValue("currentFile", rightTabWidget->tabToolTip(rightTabWidget->currentIndex()));
}

void MainWindow::readSettings()
{
    QSettings settings("https://github.com/orgs/NeoEditor", "NeoEditor");

    //layout
    restoreGeometry(settings.value("geometry").toByteArray());
    this->restoreState(settings.value("mainWindowState").toByteArray());
    splitter->restoreState(settings.value("splitterState").toByteArray());

    //left panel
    QStringList openedFolders = settings.value("openedFolders").toStringList();
    for(int i = 0; i < openedFolders.count(); i++)
    {
        leftTabWidget->showFolderTree(openedFolders[i]);
    }
    QString currentFolder = settings.value("currentFolder").toString();
    for(int i = 0; i < leftTabWidget->count(); i++)
    {
        if(currentFolder == leftTabWidget->tabToolTip(i))
        {
            leftTabWidget->setCurrentIndex(i);
            break;
        }
    }

    //right panel
    QStringList openedFiles = settings.value("openedFiles").toStringList();
    for(int i = 0; i < openedFiles.count(); i++)
    {
        emit openFileRequested(openedFiles[i]);
    }
    QString currentFile = settings.value("currentFile").toString();
    for(int i = 0; i< rightTabWidget->count(); i++)
    {
        if(currentFile == rightTabWidget->tabToolTip(i))
        {
            rightTabWidget->setCurrentIndex(i);
            break;
        }
    }
}

MainWindow* MainWindow::GetInstance()
{
    foreach(QWidget *widget, QApplication::topLevelWidgets())
    {
        if(typeid(*widget) == typeid(MainWindow))
        {
            return (MainWindow*)widget;
        }
    }
    return NULL;
}
