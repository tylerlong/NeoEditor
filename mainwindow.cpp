#include "mainwindow.h"

MainWindow::MainWindow(QApplication *app)
{
    QDesktopWidget *desktop = app->desktop();
    this->resizeAndCenter(desktop->width(), desktop->height());

    centralWidget = new QWidget(this);
    this->setCentralWidget(centralWidget);

    webView = new QWebView(this);
    webView->load(QUrl("qrc:///html/index.html"));
    webView->page()->mainFrame()->addToJavaScriptWindowObject("mainWindow", this);
    webView->page()->mainFrame()->addToJavaScriptWindowObject("app", app);

    treeView = new QTreeView(this);

    QHBoxLayout *layout = new QHBoxLayout();
    QVBoxLayout *leftLayout = new QVBoxLayout();
    QVBoxLayout *rightLayout = new QVBoxLayout();
    leftLayout->addWidget(treeView);
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
