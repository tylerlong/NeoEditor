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

protected slots:
    void debug(QString message);
    void change();

private slots:
    void init();

private:
    QString escapeJavascriptString(const QString &input);
    QString mFilePath;
    QTabWidget *mTabWidget;
};


#endif // WEBVIEW_H
