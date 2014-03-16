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

void RightTabWidget::remove(QString filePath)
{
    for(int i = this->count() - 1; i >= 0; i--)
    {
        if(this->tabToolTip(i) == filePath)
        {
            this->removeTab(i);
            break;
        }
    }
}

void RightTabWidget::open(QString filePath)
{
    QFileInfo fileInfo(filePath);
    if(!fileInfo.exists() || !fileInfo.isAbsolute() || !fileInfo.isFile() || !fileInfo.isReadable())
    {
        return;
    }
    for(int i = 0; i < this->count(); i++)
    {
        if(filePath == this->tabToolTip(i))
        {
            this->setCurrentIndex(i);
            return;
        }
    }

    WebView *webView = new WebView(this, filePath);
    int index = this->addTab(webView, fileInfo.fileName());
    webView->setFocus();
    this->setTabToolTip(index, filePath);
    this->setCurrentIndex(index);
    if(filePath.endsWith(".rb"))
    {
        this->setTabIcon(index, QIcon(":/images/ruby.png"));
    }
    else if(filePath.endsWith(".py"))
    {
        this->setTabIcon(index, QIcon(":/images/python.ico"));
    }
    else if(filePath.endsWith(".java"))
    {
        this->setTabIcon(index, QIcon(":/images/java.png"));
    }
    else if(filePath.endsWith(".js"))
    {
        this->setTabIcon(index, QIcon(":/images/javascript.png"));
    }
    else if(filePath.endsWith(".php"))
    {
        this->setTabIcon(index, QIcon(":/images/php.png"));
    }
    else if(filePath.endsWith(".css"))
    {
        this->setTabIcon(index, QIcon(":/images/css3.png"));
    }
    else if(filePath.endsWith(".as"))
    {
        this->setTabIcon(index, QIcon(":/images/flash.jpg"));
    }
    else if(filePath.endsWith(".html") || filePath.endsWith(".htm"))
    {
        this->setTabIcon(index, QIcon(":/images/html5.png"));
    }
    else if(filePath.endsWith(".xml"))
    {
        this->setTabIcon(index, QIcon(":/images/xml.png"));
    }
    else if(filePath.endsWith(".ts"))
    {
        this->setTabIcon(index, QIcon(":/images/typescript.ico"));
    }
    else if(filePath.endsWith(".md"))
    {
        this->setTabIcon(index, QIcon(":/images/markdown.png"));
    }
    else if(filePath.endsWith(".svg"))
    {
        this->setTabIcon(index, QIcon(":/images/svg.svg"));
    }
    else if(filePath.endsWith(".cpp") || filePath.endsWith(".h"))
    {
        this->setTabIcon(index, QIcon(":/images/cplusplus.png"));
    }
    else if(filePath.endsWith(".sql"))
    {
        this->setTabIcon(index, QIcon(":/images/sql.png"));
    }
    else if(filePath.endsWith(".ini"))
    {
        this->setTabIcon(index, QIcon(":/images/ini.png"));
    }
    else if(filePath.endsWith(".txt"))
    {
        this->setTabIcon(index, QIcon(":/images/txt.png"));
    }
    else
    {
        this->setTabIcon(index, QIcon(":/images/text-x-generic.svg"));
    }
}
