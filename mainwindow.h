#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QtWidgets>
#include <QtWebKitWidgets>

class QWebView;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    void resizeAndCenter(int screenWidth, int screenHeight);

protected slots:
    void quit();
    void openFileDialog();

private:
    QWebView * webView;
};


#endif // MAINWINDOW_H
