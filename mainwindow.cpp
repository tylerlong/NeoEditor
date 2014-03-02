#include "mainwindow.h"

MainWindow::MainWindow(QApplication *app)
{
    //initial window size
    QDesktopWidget *desktop = app->desktop();
    this->resizeAndCenter(desktop->width(), desktop->height());

    //tool bar
    QAction *openFolderAction = new QAction(tr("&Open Folder"), this);
    openFolderAction->setIcon(QIcon(":/images/folder-open.svg"));
    openFolderAction->setShortcut(QKeySequence::Open);
    openFolderAction->setStatusTip(tr("Open Folder"));
    connect(openFolderAction, SIGNAL(triggered()), this, SLOT(openFolder()));
    QToolBar *fileToolbar = addToolBar(tr("&File"));
    fileToolbar->addAction(openFolderAction);

    //left panel
    toolBox = new QToolBox(this);

    //right panel
    tabWidget = new QTabWidget(this);

    //layout
    splitter = new QSplitter(Qt::Horizontal);
    splitter->addWidget(toolBox);
    splitter->addWidget(tabWidget);
    this->setCentralWidget(splitter);
    splitter->setVisible(false);
}

void MainWindow::resizeAndCenter(int screenWidth, int screenHeight)
{
    int marginLeft = 200;
    int marginTop = 100;
    if(screenWidth < screenHeight)
    {
        marginLeft = 100;
        marginTop = 200;
    }
    this->resize(screenWidth - marginLeft * 2, screenHeight - marginTop * 2);
    this->move(marginLeft, marginTop);
}

QString MainWindow::openFileDialog()
{
    return QFileDialog::getOpenFileName(this, tr("Open Image"), ".", tr("All files (*.*)"));
}

void MainWindow::openFolder()
{
    QString folderPath = QFileDialog::getExistingDirectory(this, tr("Open Directory"), QDir::homePath(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if(folderPath != NULL)
    {
        showFolderTree(folderPath);
    }
}

void MainWindow::showFolderTree(QString folderPath)
{
    splitter->setVisible(true);
    QTreeView *treeView = new QTreeView(this);
    QFileSystemModel *fileSystemModel = new QFileSystemModel(this);
    fileSystemModel->setRootPath(folderPath);
    treeView->setModel(fileSystemModel);
    treeView->setRootIndex(fileSystemModel->index(folderPath));
    treeView->setColumnHidden(1, true);
    treeView->setColumnHidden(2, true);
    treeView->setColumnHidden(3, true);
    treeView->setHeaderHidden(true);
    connect(treeView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(openFile(QModelIndex)));
    toolBox->addItem(treeView, folderPath);
    if(toolBox->count() == 1)
    {
        QList<int> list = splitter->sizes();
        list[0] = 100;
        list[1] = 400;
        splitter->setSizes(list);
    }
    toolBox->setCurrentWidget(treeView);
}

void MainWindow::openFile(QModelIndex modelIndex)
{
    splitter->setVisible(true);
    QTreeView *treeView = (QTreeView*)sender();
    QFileSystemModel *fileSystemModel = (QFileSystemModel*)treeView->model();
    QFileInfo fileInfo = fileSystemModel->fileInfo(modelIndex);
    if(!fileInfo.isFile() || !fileInfo.isReadable())
    {
        return;
    }
    QString filePath = fileInfo.absoluteFilePath();

    QWebView *webView = new QWebView(this);
    webView->load(QUrl("qrc:///html/editor.html"));
    connect(webView, SIGNAL(loadFinished(bool)), this, SLOT(initACE()));
    tabWidget->addTab(webView, filePath);
    tabWidget->setCurrentWidget(webView);

//    QFile file(filePath);
//    if(!file.open(QIODevice::ReadOnly))
//    {
//        return;
//    }
//    QString result = QString(file.readAll());
//    file.close();
}

void MainWindow::initACE()
{
    QWebView *webView = (QWebView*)sender();
    webView->page()->mainFrame()->evaluateJavaScript(QString("var editor = ace.edit('editor');editor.setValue('hello world')"));
}
