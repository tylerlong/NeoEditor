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
    QString getSelectedText();
    void insert(QString text);

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
