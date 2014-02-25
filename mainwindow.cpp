#include "mainwindow.h"

MainWindow::MainWindow(QApplication *app)
{
    QDesktopWidget *desktop = app->desktop();
    this->resizeAndCenter(desktop->width(), desktop->height());

    webView = new QWebView(this);
    webView->load(QUrl("qrc:///html/index.html"));
    webView->page()->mainFrame()->addToJavaScriptWindowObject("mainWindow", this);
    webView->page()->mainFrame()->addToJavaScriptWindowObject("app", app);
    this->setCentralWidget(webView);
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
