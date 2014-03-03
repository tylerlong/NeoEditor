#ifndef WEBVIEW_H
#define WEBVIEW_H


#include <QtWebKitWidgets>

class QWebView;

class WebView : public QWebView
{
    Q_OBJECT

public:
    WebView(QWidget* parent, QString filePath);
    QString filePath();

private:
    QString mFilePath;
};


#endif // WEBVIEW_H
