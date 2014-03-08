#ifndef RIGHTTABWIDGET_H
#define RIGHTTABWIDGET_H


#include <QtWidgets>

class RightTabWidget : public QTabWidget
{
    Q_OBJECT

public:
    RightTabWidget(QWidget *parent, QApplication *app);

private slots:
    void close();
    void close(int index);
    void copy();
    void paste();
    void cut();
    void showContextMenu(const QPoint &point);

private:
    QApplication *app;
};


#endif // RIGHTTABWIDGET_H
