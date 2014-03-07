#ifndef RIGHTTABWIDGET_H
#define RIGHTTABWIDGET_H


#include <QtWidgets>

class RightTabWidget : public QTabWidget
{
    Q_OBJECT

public:
    RightTabWidget(QWidget *parent, QApplication *app);

private slots:
    void close(int index);
    void copy();
    void paste();

private:
    QApplication *app;
};


#endif // RIGHTTABWIDGET_H
