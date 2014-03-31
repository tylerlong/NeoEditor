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
    void removeFolder(QString folderPath);
    void rename(QString oldFilePath, QString newFilePath);
    void renameFolder(QString oldFolderPath, QString newFolderPath);

private slots:
    void close();
    void close(int index);
    void closeOthers();
    void closeTabsToTheRight();
};


#endif // RIGHTTABWIDGET_H
