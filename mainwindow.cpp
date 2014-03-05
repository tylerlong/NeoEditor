#include "mainwindow.h"
#include "webview.h"

MainWindow::MainWindow(QApplication *app)
{
    //initial window size
    int width = 800;
    int height = 450;
    this->resize(width, height);
    QDesktopWidget *desktop = app->desktop();
    int marginLeft = (desktop->width() - width) / 2;
    int marginTop = (desktop->height() - height) / 2;
    this->move(marginLeft, marginTop);

    //tool bar
    QToolBar *fileToolBar = new QToolBar(tr("&File"), this);
    addToolBar(Qt::RightToolBarArea, fileToolBar);

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

    //left panel
    leftTabWidget = new QTabWidget(this);
    leftTabWidget->setTabPosition(QTabWidget::West);
    leftTabWidget->setTabsClosable(true);
    connect(leftTabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(closeLeftTab(int)));

    //right panel
    rightTabWidget = new QTabWidget(this);
    rightTabWidget->setTabsClosable(true);
    connect(rightTabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(closeRightTab(int)));

    //layout
    splitter = new QSplitter(Qt::Horizontal);
    splitter->addWidget(leftTabWidget);
    splitter->addWidget(rightTabWidget);
    this->setCentralWidget(splitter);
    splitter->setStretchFactor(1, 1);
    QList<int> list;
    list << 200 << 1; //right panel takes all the extra space
    splitter->setSizes(list);
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
    QString filePath = webView->filePath();
    QString content = webView->page()->mainFrame()->evaluateJavaScript(QString("editor.getValue()")).toString();
    QFile file(filePath);
    if(!file.open(QIODevice::WriteOnly))
    {
        return;
    }
    file.write(content.toUtf8());
    file.close();
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
    treeView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    connect(treeView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(openFile(QModelIndex)));
    int index = leftTabWidget->addTab(treeView, QDir(folderPath).dirName());
    leftTabWidget->setTabToolTip(index, folderPath);
    leftTabWidget->setCurrentWidget(treeView);
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

    WebView *webView = new WebView(this, filePath);
    webView->load(QUrl("qrc:///html/editor.html"));
    connect(webView, SIGNAL(loadFinished(bool)), this, SLOT(initACE()));
    int index = rightTabWidget->addTab(webView, fileInfo.fileName());
    rightTabWidget->setTabToolTip(index, filePath);
    rightTabWidget->setCurrentWidget(webView);
    if(filePath.endsWith(".rb"))
    {
        rightTabWidget->setTabIcon(index, QIcon(":/images/ruby.png"));
    }else if(filePath.endsWith(".py"))
    {
        rightTabWidget->setTabIcon(index, QIcon(":/images/python.ico"));
    }else if(filePath.endsWith(".java"))
    {
        rightTabWidget->setTabIcon(index, QIcon(":/images/java.png"));
    }else if(filePath.endsWith(".js"))
    {
        rightTabWidget->setTabIcon(index, QIcon(":/images/javascript.png"));
    }else if(filePath.endsWith(".php"))
    {
        rightTabWidget->setTabIcon(index, QIcon(":/images/php.png"));
    }else if(filePath.endsWith(".css"))
    {
        rightTabWidget->setTabIcon(index, QIcon(":/images/css3.png"));
    }else if(filePath.endsWith(".as"))
    {
        rightTabWidget->setTabIcon(index, QIcon(":/images/flash.png"));
    }else if(filePath.endsWith(".html") || filePath.endsWith(".htm"))
    {
        rightTabWidget->setTabIcon(index, QIcon(":/images/html5.png"));
    }else
    {
        rightTabWidget->setTabIcon(index, QIcon(":/images/accessories-text-editor.svg"));
    }
}

void MainWindow::initACE()
{
    WebView *webView = (WebView*)sender();
    QString filePath = webView->filePath();
    webView->page()->mainFrame()->evaluateJavaScript(QString("editor.getSession().setMode(modelist.getModeForPath('%1').mode);null;").arg(escapeJavascriptString(filePath)));
    QFile file(filePath);
    if(!file.open(QIODevice::ReadOnly))
    {
        return;
    }
    QString content = QString(file.readAll());
    file.close();
    webView->page()->mainFrame()->evaluateJavaScript(QString("editor.setValue('%1', -1);null;").arg(escapeJavascriptString(content)));
}

void MainWindow::closeLeftTab(int index)
{
    leftTabWidget->removeTab(index);
}

void MainWindow::closeRightTab(int index)
{
    rightTabWidget->removeTab(index);
}

QString MainWindow::escapeJavascriptString(const QString &input)
{
    QString output;
    QRegExp regExp("(\\r|\\n|\\\\|\')");
    int pos = 0, lastPos = 0;
    while ((pos = regExp.indexIn(input, pos)) != -1)
    {
        output += input.mid(lastPos, pos - lastPos);
        switch (regExp.cap(1).at(0).unicode())
        {
        case '\r':
            output += "\\r";
            break;
        case '\n':
            output += "\\n";
            break;
        case '\'':
            output += "\\\'";
            break;
        case '\\':
            output += "\\\\";
            break;
        }
        pos += 1;
        lastPos = pos;
    }
    output += input.mid(lastPos);
    return output;
}
