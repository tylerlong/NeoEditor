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

    //title and icon
    this->setWindowTitle(tr("NeoEditor"));
    this->setWindowIcon(QIcon(":/images/neo.png"));

    //style
    this->setStyleSheet("QTreeView { border: 0; } QTabWidget { border: 0; }");
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
        showFolderTree(folderPath);
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

void MainWindow::showFolderTree(QString folderPath)
{
    QDir dir(folderPath);
    if(!dir.exists() || !dir.isAbsolute() || !dir.isReadable())
    {
        return;
    }
    for(int i = 0; i < leftTabWidget->count(); i++)
    {
        if(folderPath == leftTabWidget->tabToolTip(i))
        {
            leftTabWidget->setCurrentIndex(i);
            return;
        }
    }

    TreeView *treeView = new TreeView(this);
    QFileSystemModel *fileSystemModel = new QFileSystemModel(this);
    fileSystemModel->setRootPath(folderPath);
    treeView->setModel(fileSystemModel);
    treeView->setRootIndex(fileSystemModel->index(folderPath));
    treeView->setColumnHidden(1, true);
    treeView->setColumnHidden(2, true);
    treeView->setColumnHidden(3, true);
    treeView->setHeaderHidden(true);
    connect(treeView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(openFile(QModelIndex)));
    int index = leftTabWidget->addTab(treeView, QDir(folderPath).dirName());
    treeView->setFocus();
    leftTabWidget->setTabToolTip(index, folderPath);
    leftTabWidget->setCurrentIndex(index);
}

void MainWindow::openFile(QModelIndex modelIndex)
{
    TreeView *treeView = (TreeView*)sender();
    QFileSystemModel *fileSystemModel = (QFileSystemModel*)treeView->model();
    openFile(fileSystemModel->filePath(modelIndex));
}

void MainWindow::openFile(QString filePath)
{
    QFileInfo fileInfo(filePath);
    if(!fileInfo.exists() || !fileInfo.isAbsolute() || !fileInfo.isFile() || !fileInfo.isReadable())
    {
        return;
    }
    for(int i = 0; i < rightTabWidget->count(); i++)
    {
        if(filePath == rightTabWidget->tabToolTip(i))
        {
            rightTabWidget->setCurrentIndex(i);
            return;
        }
    }

    WebView *webView = new WebView(rightTabWidget, filePath);
    int index = rightTabWidget->addTab(webView, fileInfo.fileName());
    webView->setFocus();
    rightTabWidget->setTabToolTip(index, filePath);
    rightTabWidget->setCurrentIndex(index);
    if(filePath.endsWith(".rb"))
    {
        rightTabWidget->setTabIcon(index, QIcon(":/images/ruby.png"));
    }
    else if(filePath.endsWith(".py"))
    {
        rightTabWidget->setTabIcon(index, QIcon(":/images/python.ico"));
    }
    else if(filePath.endsWith(".java"))
    {
        rightTabWidget->setTabIcon(index, QIcon(":/images/java.png"));
    }
    else if(filePath.endsWith(".js"))
    {
        rightTabWidget->setTabIcon(index, QIcon(":/images/javascript.png"));
    }
    else if(filePath.endsWith(".php"))
    {
        rightTabWidget->setTabIcon(index, QIcon(":/images/php.png"));
    }
    else if(filePath.endsWith(".css"))
    {
        rightTabWidget->setTabIcon(index, QIcon(":/images/css3.png"));
    }
    else if(filePath.endsWith(".as"))
    {
        rightTabWidget->setTabIcon(index, QIcon(":/images/flash.jpg"));
    }
    else if(filePath.endsWith(".html") || filePath.endsWith(".htm"))
    {
        rightTabWidget->setTabIcon(index, QIcon(":/images/html5.png"));
    }
    else if(filePath.endsWith(".xml"))
    {
        rightTabWidget->setTabIcon(index, QIcon(":/images/xml.png"));
    }
    else if(filePath.endsWith(".ts"))
    {
        rightTabWidget->setTabIcon(index, QIcon(":/images/typescript.ico"));
    }
    else if(filePath.endsWith(".md"))
    {
        rightTabWidget->setTabIcon(index, QIcon(":/images/markdown.png"));
    }
    else if(filePath.endsWith(".svg"))
    {
        rightTabWidget->setTabIcon(index, QIcon(":/images/svg.svg"));
    }
    else if(filePath.endsWith(".cpp") || filePath.endsWith(".h"))
    {
        rightTabWidget->setTabIcon(index, QIcon(":/images/cplusplus.png"));
    }
    else if(filePath.endsWith(".sql"))
    {
        rightTabWidget->setTabIcon(index, QIcon(":/images/sql.png"));
    }
    else if(filePath.endsWith(".ini"))
    {
        rightTabWidget->setTabIcon(index, QIcon(":/images/ini.png"));
    }
    else if(filePath.endsWith(".txt"))
    {
        rightTabWidget->setTabIcon(index, QIcon(":/images/txt.png"));
    }
    else
    {
        rightTabWidget->setTabIcon(index, QIcon(":/images/text-x-generic.svg"));
    }
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
        showFolderTree(openedFolders[i]);
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
        openFile(openedFiles[i]);
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
