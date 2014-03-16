#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QtWidgets>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

protected:
    void closeEvent(QCloseEvent *closeEvent);

private slots:
    void openFolder();
    void saveFile();
    void openFile(QModelIndex modelIndex);
    void about();
    void keyboardShortcuts();

private:
    void showFolderTree(QString folderPath);
    void openFile(QString filePath);
    void writeSettings();
    void readSettings();
    QSplitter *splitter;
    QTabWidget *leftTabWidget;
    QTabWidget *rightTabWidget;
};


#endif // MAINWINDOW_H
