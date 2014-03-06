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
    QTabWidget *tabWidget = this->mTabWidget;
    int index = tabWidget->indexOf(this);
    if(index == -1) // tab already closed
    {
        return;
    }
    tabWidget->setTabText(index, "* " + tabWidget->tabText(index));
    this->page()->mainFrame()->evaluateJavaScript(tr("editor.getSession().removeListener('change', qt.change);null;"));
}

void WebView::save()
{
    QString filePath = this->mFilePath;
    QTabWidget *tabWidget = this->mTabWidget;
    QFile file(filePath);
    if(!file.open(QIODevice::WriteOnly))
    {
        return;
    }
    this->page()->mainFrame()->evaluateJavaScript(QString("whitespace.trimTrailingSpace(editor.getSession(), true);null;"));
    this->page()->mainFrame()->evaluateJavaScript(QString("ensure_newline_at_eof();null;"));
    QString content = this->page()->mainFrame()->evaluateJavaScript(QString("editor.getValue();")).toString();
    file.write(content.toUtf8());
    file.close();
    int index = tabWidget->indexOf(this);
    QString tabText = tabWidget->tabText(index);
    if(tabText.startsWith("* "))
    {
        tabWidget->setTabText(index, tabText.mid(2));
    }
    this->page()->mainFrame()->evaluateJavaScript(tr("editor.getSession().on('change', qt.change);null;"));
}
