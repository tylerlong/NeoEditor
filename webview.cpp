#include "webview.h"

WebView::WebView(QWidget* parent, QString filePath) : QWebView(parent)
{
    this->mTabWidget = (QTabWidget*)parent;
    this->mFilePath = filePath;
}

QString WebView::filePath()
{
    return this->mFilePath;
}

void WebView::debug(QString message)
{
    qDebug() << message;
}

void WebView::change()
{
    int index = this->mTabWidget->indexOf(this);
    if(index == -1) // tab already closed
    {
        return;
    }
    this->mTabWidget->setTabText(index, "* " + this->mTabWidget->tabText(index));
    this->page()->mainFrame()->evaluateJavaScript(tr("editor.getSession().removeListener('change', qt.change);null;"));
}
