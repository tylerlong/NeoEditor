#ifndef LEFTTABWIDGET_H
#define LEFTTABWIDGET_H


#include <QtWidgets>

class LeftTabWidget : public QTabWidget
{
    Q_OBJECT

public:
    LeftTabWidget(QWidget *parent);

private slots:
    void close(int index);
};


#endif // LEFTTABWIDGET_H
