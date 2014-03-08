#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QtWidgets>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QApplication *app);

private slots:
    void openFolder();
    void saveFile();
    void openFile(QModelIndex modelIndex);
    void closeLeftTab(int index);
    void about();
    void keyboardShortcuts();

private:
    void showFolderTree(QString folderPath);
    QSplitter *splitter;
    QTabWidget *leftTabWidget;
    QTabWidget *rightTabWidget;
};


#endif // MAINWINDOW_H
