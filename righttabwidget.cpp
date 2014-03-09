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

    QTabBar *tabBar = this->tabBar();
    tabBar->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(tabBar, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(showContextMenu(const QPoint &)));
}

void RightTabWidget::showContextMenu(const QPoint &point)
{
    QTabBar *tabBar = this->tabBar();
    int index = tabBar->tabAt(point);
    if(index == -1)
    {
        return;
    }
    QWidget *selectedWidget = this->widget(index);

    QMenu menu(this);

    QAction closeAction(tr("&Close"), selectedWidget);
    connect(&closeAction, SIGNAL(triggered()), this, SLOT(close()));
    menu.addAction(&closeAction);

    QAction closeOthersAction(tr("Close &Others"), selectedWidget);
    connect(&closeOthersAction, SIGNAL(triggered()), this, SLOT(closeOthers()));
    if(this->count() > 1)
    {
        menu.addAction(&closeOthersAction);
    }

    QAction closeTabsToTheRightAction(tr("Close Tabs to the &Right"), selectedWidget);
    connect(&closeTabsToTheRightAction, SIGNAL(triggered()), this, SLOT(closeTabsToTheRight()));
    if(this->count() > index + 1)
    {
        menu.addAction(&closeTabsToTheRightAction);
    }

    menu.exec(tabBar->mapToGlobal(point));
}

void RightTabWidget::close()
{
    QObject *object = sender(); //action
    QObject *parent = object->parent(); //webview
    int index = this->indexOf((QWidget*)parent);
    this->close(index);
}

void RightTabWidget::closeOthers()
{
    QObject *object = sender(); //action
    QObject *parent = object->parent(); //webview
    int index = this->indexOf((QWidget*)parent);
    for(int i = this->count() - 1; i >= 0; i--)
    {
        if(i == index)
        {
            continue;
        }
        this->close(i);
    }
}

void RightTabWidget::closeTabsToTheRight()
{
    QObject *object = sender(); //action
    QObject *parent = object->parent(); //webview
    int index = this->indexOf((QWidget*)parent);
    for(int i = this->count() - 1; i > index; i--)
    {
        this->close(i);
    }
}

void RightTabWidget::close(int index)
{
    if(this->widget(index) == 0)
    {
        return;
    }
    if(this->tabText(index).startsWith("* "))
    {
        int r = QMessageBox::warning(this, tr("NeoEditor"),
                                     QString("%1 has been modified.\n Do you want to save your changes?").arg(((WebView*)this->widget(index))->filePath()),
                                     QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
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
