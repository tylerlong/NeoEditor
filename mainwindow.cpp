#include "mainwindow.h"

MainWindow::MainWindow()
{
    webView = new QWebView(this);
    webView->load(QUrl("qrc:///html/index.html"));
    webView->page()->mainFrame()->addToJavaScriptWindowObject("qt", this);
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

void MainWindow::quit()
{
    this->quit();
}

QString MainWindow::openFileDialog()
{
    return QFileDialog::getOpenFileName(this, tr("Open Image"), ".", tr("All files (*.*)"));
}
