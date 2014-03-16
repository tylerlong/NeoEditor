#include "righttabwidget.h"
#include "webview.h"

RightTabWidget::RightTabWidget(QWidget *parent) : QTabWidget(parent)
{
    this->setTabsClosable(true);
    connect(this, SIGNAL(tabCloseRequested(int)), this, SLOT(close(int)));

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
