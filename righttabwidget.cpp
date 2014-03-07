#include "righttabwidget.h"
#include "webview.h"

RightTabWidget::RightTabWidget(QWidget *parent, QApplication *app) : QTabWidget(parent)
{
    this->app = app;
    this->setTabsClosable(true);
    connect(this, SIGNAL(tabCloseRequested(int)), this, SLOT(close(int)));

    QAction *copyAction = new QAction(tr("&Copy"), this);
    copyAction->setShortcut(QKeySequence::Copy);
    connect(copyAction, SIGNAL(triggered()), this, SLOT(copy()));
    this->addAction(copyAction);

    QAction *pasteAction = new QAction(tr("&Paste"), this);
    pasteAction->setShortcut(QKeySequence::Paste);
    connect(pasteAction, SIGNAL(triggered()), this, SLOT(paste()));
    this->addAction(pasteAction);
}

void RightTabWidget::close(int index)
{
    if(this->tabText(index).startsWith("* "))
    {
        int r = QMessageBox::warning(this, tr("NeoEditor"), tr("The file has been modified.\n Do you want to save your changes?"), QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        if(r == QMessageBox::Cancel)
        {
            return;
        }
        else if(r == QMessageBox::Save)
        {
            WebView *webView = (WebView*) this->widget(index);
            webView->save();
        }
    }
    this->removeTab(index);
}

void RightTabWidget::copy()
{
    QWidget *widget = this->currentWidget();
    if(widget == 0)
    {
        return;
    }
    WebView *webView = (WebView*)widget;
    QString selectedText = webView->getSelectedText();
    if(selectedText.isEmpty())
    {
        return;
    }
    this->app->clipboard()->setText(selectedText);
}

void RightTabWidget::paste()
{
    QWidget *widget = this->currentWidget();
    if(widget == 0)
    {
        return;
    }
    WebView *webView = (WebView*)widget;
    webView->insert(this->app->clipboard()->text());
}
