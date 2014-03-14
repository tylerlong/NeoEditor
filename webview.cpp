#include "webview.h"

WebView::WebView(QWidget* parent, QString filePath) : QWebView(parent)
{
    this->mTabWidget = (QTabWidget*)parent;
    this->mFilePath = filePath;
    this->load(QUrl("qrc:///html/editor.html"));
    connect(this, SIGNAL(loadFinished(bool)), this, SLOT(init()));
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

void WebView::init()
{
    QString filePath = this->mFilePath;
    this->page()->mainFrame()->evaluateJavaScript(QString("setTimeout(function(){editor.getSession().setMode(modelist.getModeForPath('%1').mode);}, 50);null;").arg(escapeJavascriptString(filePath)));
    QFile file(filePath);
    if(!file.open(QIODevice::ReadOnly))
    {
        return;
    }
    QString content = QString(file.readAll());
    file.close();
    this->page()->mainFrame()->evaluateJavaScript(QString("setTimeout(function(){editor.setValue('%1', -1);}, 50);null;").arg(escapeJavascriptString(content)));
    this->page()->mainFrame()->evaluateJavaScript(tr("editor.focus();null;"));
    this->page()->mainFrame()->addToJavaScriptWindowObject("qt", this);
    this->page()->mainFrame()->evaluateJavaScript(tr("setTimeout(function(){editor.getSession().on('change', qt.change);}, 100);null;"));
}

void WebView::contextMenuEvent(QContextMenuEvent *contextMenuEvent)
{
    QMenu menu;
    QString selected = this->page()->mainFrame()->evaluateJavaScript(tr("editor.getSelectedText();")).toString();
    if(selected.isEmpty())
    {
        menu.addAction(this->pageAction(QWebPage::SelectAll));
    }
    else
    {
        menu.addAction(this->pageAction(QWebPage::Copy));
        menu.addAction(this->pageAction(QWebPage::Cut));
    }
    menu.addAction(this->pageAction(QWebPage::Paste));
    menu.exec(mapToGlobal(contextMenuEvent->pos()));
}

QString WebView::escapeJavascriptString(const QString &input)
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
