#ifndef LEFTTABWIDGET_H
#define LEFTTABWIDGET_H


#include <QtWidgets>

class LeftTabWidget : public QTabWidget
{
    Q_OBJECT

public:
    LeftTabWidget(QWidget *parent);
    void showFolderTree(QString folderPath);

private slots:
    void close(int index);

private:
    QMainWindow *mainWindow;
};


#endif // LEFTTABWIDGET_H
