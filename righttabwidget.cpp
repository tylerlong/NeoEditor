#include "righttabwidget.h"
#include "webview.h"

RightTabWidget::RightTabWidget(QWidget *parent, QApplication *app) : QTabWidget(parent)
{
    this->app = app;
    this->setTabsClosable(true);
    connect(this, SIGNAL(tabCloseRequested(int)), this, SLOT(close(int)));

    QToolBar *editToolBar = new QToolBar(tr("&Edit"), this);

    QAction *cutAction = new QAction(tr("Cu&t"), this);
    cutAction->setIcon(QIcon(":/images/edit-cut.svg"));
    cutAction->setShortcut(QKeySequence::Cut);
    cutAction->setStatusTip(tr("Cut"));
    connect(cutAction, SIGNAL(triggered()), this, SLOT(cut()));
    editToolBar->addAction(cutAction);

    QAction *copyAction = new QAction(tr("&Copy"), this);
    copyAction->setIcon(QIcon(":/images/edit-copy.svg"));
    copyAction->setShortcut(QKeySequence::Copy);
    copyAction->setStatusTip(tr("Copy"));
    connect(copyAction, SIGNAL(triggered()), this, SLOT(copy()));
    editToolBar->addAction(copyAction);

    QAction *pasteAction = new QAction(tr("&Paste"), this);
    pasteAction->setIcon(QIcon(":/images/edit-paste.svg"));
    pasteAction->setShortcut(QKeySequence::Paste);
    pasteAction->setStatusTip(tr("Paste"));
    connect(pasteAction, SIGNAL(triggered()), this, SLOT(paste()));
    editToolBar->addAction(pasteAction);

    QMainWindow *mainWindow = (QMainWindow*) parent;
    mainWindow->addToolBar(Qt::LeftToolBarArea, editToolBar);
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
    QString text = webView->copy();
    if(text.isEmpty())
    {
        return;
    }
    this->app->clipboard()->setText(text);
}

void RightTabWidget::paste()
{
    QWidget *widget = this->currentWidget();
    if(widget == 0)
    {
        return;
    }
    WebView *webView = (WebView*)widget;
    webView->paste(this->app->clipboard()->text());
}

void RightTabWidget::cut()
{
    QWidget *widget = this->currentWidget();
    if(widget == 0)
    {
        return;
    }
    WebView *webView = (WebView*)widget;
    QString text = webView->cut();
    if(text.isEmpty())
    {
        return;
    }
    this->app->clipboard()->setText(text);
}
