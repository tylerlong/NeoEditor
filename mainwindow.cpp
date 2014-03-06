#include "mainwindow.h"
#include "webview.h"

MainWindow::MainWindow(QApplication *app)
{
    //initial window size
    int width = 1024;
    int height = 576;
    this->resize(width, height);
    QDesktopWidget *desktop = app->desktop();
    int marginLeft = (desktop->width() - width) / 2;
    int marginTop = (desktop->height() - height) / 2;
    this->move(marginLeft, marginTop);

    //title and icon
    this->setWindowTitle(tr("NeoEditor"));
    this->setWindowIcon(QIcon(":/images/neo.png"));

    //style
    this->setStyleSheet("QTreeView { border: 0; } QTabWidget { border: 0; }");

    //tool bar
    QToolBar *fileToolBar = new QToolBar(tr("&File"), this);
    addToolBar(Qt::LeftToolBarArea, fileToolBar);

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

    QAction *aboutAction = new QAction(tr("&About NeoEditor"), this);
    aboutAction->setIcon(QIcon(":/images/neo.png"));
    aboutAction->setStatusTip("About NeoEditor");
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));
    fileToolBar->addAction(aboutAction);

    //left panel
    leftTabWidget = new QTabWidget(this);
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
    list << 256 << 1; //right panel takes all the extra space
    splitter->setSizes(list);
    splitter->setHandleWidth(1);
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
    QFile file(filePath);
    if(!file.open(QIODevice::WriteOnly))
    {
        return;
    }
    webView->page()->mainFrame()->evaluateJavaScript(QString("whitespace.trimTrailingSpace(editor.getSession(), true);null;"));
    webView->page()->mainFrame()->evaluateJavaScript(QString("ensure_newline_at_eof();null;"));
    QString content = webView->page()->mainFrame()->evaluateJavaScript(QString("editor.getValue();")).toString();
    file.write(content.toUtf8());
    file.close();
    int index = rightTabWidget->currentIndex();
    QString tabText = rightTabWidget->tabText(index);
    if(tabText.startsWith("* "))
    {
        rightTabWidget->setTabText(index, tabText.mid(2));
    }
    webView->page()->mainFrame()->evaluateJavaScript(tr("editor.getSession().on('change', qt.change);null;"));
}

void MainWindow::showFolderTree(QString folderPath)
{
    for(int i = 0; i < leftTabWidget->count(); i++)
    {
        QTreeView *treeView = (QTreeView*)leftTabWidget->widget(i);
        QFileSystemModel *fileSystemModel = (QFileSystemModel*)treeView->model();
        if(folderPath == fileSystemModel->rootPath())
        {
            leftTabWidget->setCurrentIndex(i);
            return;
        }
    }

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
    int index = leftTabWidget->addTab(treeView, QDir(folderPath).dirName());
    treeView->setFocus();
    leftTabWidget->setTabToolTip(index, folderPath);
    leftTabWidget->setCurrentIndex(index);
}

void MainWindow::openFile(QModelIndex modelIndex)
{
    QTreeView *treeView = (QTreeView*)sender();
    QFileSystemModel *fileSystemModel = (QFileSystemModel*)treeView->model();
    QFileInfo fileInfo = fileSystemModel->fileInfo(modelIndex);
    if(!fileInfo.isFile() || !fileInfo.isReadable())
    {
        return;
    }
    QString filePath = fileInfo.absoluteFilePath();

    for(int i = 0; i < rightTabWidget->count(); i++)
    {
        WebView *webView = (WebView*)rightTabWidget->widget(i);
        if(filePath == webView->filePath())
        {
            rightTabWidget->setCurrentIndex(i);
            return;
        }
    }

    WebView *webView = new WebView(this, filePath);
    webView->load(QUrl("qrc:///html/editor.html"));
    connect(webView, SIGNAL(loadFinished(bool)), this, SLOT(initACE()));
    int index = rightTabWidget->addTab(webView, fileInfo.fileName());
    webView->setFocus();
    rightTabWidget->setTabToolTip(index, filePath);
    rightTabWidget->setCurrentIndex(index);
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
        rightTabWidget->setTabIcon(index, QIcon(":/images/flash.jpg"));
    }else if(filePath.endsWith(".html") || filePath.endsWith(".htm"))
    {
        rightTabWidget->setTabIcon(index, QIcon(":/images/html5.png"));
    }else
    {
        rightTabWidget->setTabIcon(index, QIcon(":/images/neo.png"));
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
    webView->page()->mainFrame()->evaluateJavaScript(tr("editor.focus();null;"));
    webView->page()->mainFrame()->addToJavaScriptWindowObject("qt", this);
    webView->page()->mainFrame()->evaluateJavaScript(tr("editor.getSession().on('change', qt.change);null;"));
}

void MainWindow::closeLeftTab(int index)
{
    leftTabWidget->removeTab(index);
}

void MainWindow::closeRightTab(int index)
{
    rightTabWidget->removeTab(index);
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About NeoEditor"), tr("<strong>NeoEditor 0.1.0</strong><br/><br/>An extensible text editor for the 21st Century.<br/><br/>Copyright 2014 <a href=\"https://github.com/tylerlong\">Tyler Long</a> (tyler4long@gmail.com). All rights reserved.<br/><br/>The program is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE."));
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

void MainWindow::debug(QString message)
{
    qDebug() << message;
}

void MainWindow::change()
{
    int index = rightTabWidget->currentIndex();
    rightTabWidget->setTabText(index, "* " + rightTabWidget->tabText(index));
    WebView *webView = (WebView*)rightTabWidget->currentWidget();
    webView->page()->mainFrame()->evaluateJavaScript(tr("editor.getSession().removeListener('change', qt.change);null;"));
}
