#ifndef WEBVIEW_H
#define WEBVIEW_H


#include <QtWebKitWidgets>

class WebView : public QWebView
{
    Q_OBJECT

public:
    WebView(QWidget* parent);
    void save();

protected:
    void contextMenuEvent(QContextMenuEvent *contextMenuEvent);

protected slots:
    void debug(QString message);
    void change();

private slots:
    void init();

private:
    QString escapeJavascriptString(const QString &input);
    QTabWidget *mTabWidget;
};


#endif // WEBVIEW_H
