#include "mainwindow.h"

MainWindow::MainWindow(QApplication *app)
{
    QDesktopWidget *desktop = app->desktop();
    this->resizeAndCenter(desktop->width(), desktop->height());

    QWidget *centralWidget = new QWidget(this);
    this->setCentralWidget(centralWidget);

    QWebView *webView = new QWebView(this);
    webView->load(QUrl("qrc:///html/index.html"));
    webView->page()->mainFrame()->addToJavaScriptWindowObject("mainWindow", this);
    webView->page()->mainFrame()->addToJavaScriptWindowObject("app", app);

    QTreeView *treeView1 = new QTreeView(this);
    QFileSystemModel *fileSystemModel = new QFileSystemModel(this);
    fileSystemModel->setRootPath(QDir::homePath());
    treeView1->setModel(fileSystemModel);
    treeView1->setRootIndex(fileSystemModel->index(QDir::homePath()));
    treeView1->setColumnHidden(1, true);
    treeView1->setColumnHidden(2, true);
    treeView1->setColumnHidden(3, true);
    treeView1->setHeaderHidden(true);

    QTreeView *treeView2 = new QTreeView(this);

    QToolBox *toolBox = new QToolBox(this);
    toolBox->addItem(treeView1, QDir::homePath());
    toolBox->addItem(treeView2, tr("test2"));

    QHBoxLayout *layout = new QHBoxLayout();
    QVBoxLayout *leftLayout = new QVBoxLayout();
    QVBoxLayout *rightLayout = new QVBoxLayout();
    leftLayout->addWidget(toolBox);
    rightLayout->addWidget(webView);
    layout->addLayout(leftLayout);
    layout->addLayout(rightLayout);
    centralWidget->setLayout(layout);
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
