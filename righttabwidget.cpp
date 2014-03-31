#include "righttabwidget.h"
#include "webview.h"
#include "tabbar.h"

RightTabWidget::RightTabWidget(QWidget *parent) : QTabWidget(parent)
{
    QTabBar *tabBar = new TabBar();
    this->setTabBar(tabBar);
    this->setTabsClosable(true);
    connect(this, SIGNAL(tabCloseRequested(int)), this, SLOT(close(int)));
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
                                     QString("%1 has been modified.\n Do you want to save your changes?").arg(this->tabToolTip(index)),
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

void RightTabWidget::rename(QString oldFilePath, QString newFilePath)
{
    for(int i = this->count() - 1; i >= 0; i--)
    {
        if(this->tabToolTip(i) == oldFilePath)
        {
            this->setTabToolTip(i, newFilePath);
            QString tabText = QFileInfo(newFilePath).fileName();
            if(this->tabText(i).startsWith("* "))
            {
                tabText = "* " + tabText;
            }
            this->setTabText(i, tabText);
            break;
        }
    }
}

void RightTabWidget::removeFolder(QString folderPath)
{
    for(int i = this->count() - 1; i >= 0; i--)
    {
        if(this->tabToolTip(i).startsWith(folderPath))
        {
            this->removeTab(i);
        }
    }
}

void RightTabWidget::renameFolder(QString oldFolderPath, QString newFolderPath)
{
    for(int i = this->count() - 1; i >= 0; i--)
    {
        if(this->tabToolTip(i).startsWith(oldFolderPath))
        {
            this->setTabToolTip(i, newFolderPath + this->tabToolTip(i).mid(oldFolderPath.length()));
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

    WebView *webView = new WebView(this);
    int index = this->addTab(webView, fileInfo.fileName());
    webView->setFocus();
    this->setTabToolTip(index, filePath);
    this->setCurrentIndex(index);
    if(filePath.endsWith(".rb"))
    {
        this->setTabIcon(index, QIcon(":/images/languages/ruby.png"));
    }
    else if(filePath.endsWith(".py"))
    {
        this->setTabIcon(index, QIcon(":/images/languages/python.ico"));
    }
    else if(filePath.endsWith(".java"))
    {
        this->setTabIcon(index, QIcon(":/images/languages/java.png"));
    }
    else if(filePath.endsWith(".js"))
    {
        this->setTabIcon(index, QIcon(":/images/languages/javascript.png"));
    }
    else if(filePath.endsWith(".php"))
    {
        this->setTabIcon(index, QIcon(":/images/languages/php.png"));
    }
    else if(filePath.endsWith(".css"))
    {
        this->setTabIcon(index, QIcon(":/images/languages/css3.png"));
    }
    else if(filePath.endsWith(".as"))
    {
        this->setTabIcon(index, QIcon(":/images/languages/flash.jpg"));
    }
    else if(filePath.endsWith(".html") || filePath.endsWith(".htm"))
    {
        this->setTabIcon(index, QIcon(":/images/languages/html5.png"));
    }
    else if(filePath.endsWith(".xml"))
    {
        this->setTabIcon(index, QIcon(":/images/languages/xml.png"));
    }
    else if(filePath.endsWith(".ts"))
    {
        this->setTabIcon(index, QIcon(":/images/languages/typescript.ico"));
    }
    else if(filePath.endsWith(".md"))
    {
        this->setTabIcon(index, QIcon(":/images/languages/markdown.png"));
    }
    else if(filePath.endsWith(".svg"))
    {
        this->setTabIcon(index, QIcon(":/images/languages/svg.svg"));
    }
    else if(filePath.endsWith(".cpp") || filePath.endsWith(".h"))
    {
        this->setTabIcon(index, QIcon(":/images/languages/cplusplus.svg"));
    }
    else if(filePath.endsWith(".sql"))
    {
        this->setTabIcon(index, QIcon(":/images/languages/sql.png"));
    }
    else if(filePath.endsWith(".ini"))
    {
        this->setTabIcon(index, QIcon(":/images/languages/ini.png"));
    }
    else if(filePath.endsWith(".txt"))
    {
        this->setTabIcon(index, QIcon(":/images/languages/txt.png"));
    }
    else
    {
        this->setTabIcon(index, QIcon(":/images/languages/generic.svg"));
    }
}
