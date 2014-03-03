#include "webview.h"

WebView::WebView(QWidget* parent, QString filePath) : QWebView(parent)
{
    this->mFilePath = filePath;
}

QString WebView::filePath()
{
    return this->mFilePath;
}
