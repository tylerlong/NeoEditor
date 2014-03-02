#include "mainwindow.h"

MainWindow::MainWindow(QApplication *app)
{
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
    QWebView *webView = new QWebView(this);
    webView->load(QUrl("qrc:///html/index.html"));
    webView->page()->mainFrame()->addToJavaScriptWindowObject("mainWindow", this);
    webView->page()->mainFrame()->addToJavaScriptWindowObject("app", app);

    QSplitter *splitter = new QSplitter(Qt::Horizontal);
    splitter->addWidget(toolBox);
    splitter->addWidget(webView);
    this->setCentralWidget(splitter);
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
    QTreeView *treeView = new QTreeView(this);
    QFileSystemModel *fileSystemModel = new QFileSystemModel(this);
    fileSystemModel->setRootPath(folderPath);
    treeView->setModel(fileSystemModel);
    treeView->setRootIndex(fileSystemModel->index(folderPath));
    treeView->setColumnHidden(1, true);
    treeView->setColumnHidden(2, true);
    treeView->setColumnHidden(3, true);
    treeView->setHeaderHidden(true);
    toolBox->addItem(treeView, folderPath);
    toolBox->setCurrentWidget(treeView);
}
