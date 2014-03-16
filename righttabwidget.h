#ifndef RIGHTTABWIDGET_H
#define RIGHTTABWIDGET_H


#include <QtWidgets>

class RightTabWidget : public QTabWidget
{
    Q_OBJECT

public:
    RightTabWidget(QWidget *parent);

public slots:
    void open(QString filePath);
    void remove(QString filePath);

private slots:
    void close();
    void close(int index);
    void closeOthers();
    void closeTabsToTheRight();
    void showContextMenu(const QPoint &point);
};


#endif // RIGHTTABWIDGET_H
