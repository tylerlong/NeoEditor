#ifndef WEBVIEW_H
#define WEBVIEW_H


#include <QtWebKitWidgets>

class WebView : public QWebView
{
    Q_OBJECT

public:
    WebView(QWidget* parent, QString filePath);
    QString filePath();
    void save();
    QString copy();
    void paste(QString text);
    QString cut();

public slots:
    void init();

protected slots:
    void debug(QString message);
    void change();

private:
    QString escapeJavascriptString(const QString &input);
    QString mFilePath;
    QTabWidget *mTabWidget;
};


#endif // WEBVIEW_H
