#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QtWidgets>
#include "lefttabwidget.h"
#include "righttabwidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

signals:
    void openFileRequested(QString filePath);
    void deleteFileRequested(QString filePath);
    void deleteFolderRequested(QString folderPath);

public:
    MainWindow();
    static MainWindow* GetInstance();

protected:
    void closeEvent(QCloseEvent *closeEvent);

private slots:
    void openFolder();
    void saveFile();
    void openFile(QModelIndex modelIndex);
    void about();
    void keyboardShortcuts();

private:
    void writeSettings();
    void readSettings();
    QSplitter *splitter;
    LeftTabWidget *leftTabWidget;
    RightTabWidget *rightTabWidget;
};


#endif // MAINWINDOW_H
