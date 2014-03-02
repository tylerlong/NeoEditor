#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QtWidgets>
#include <QtWebKitWidgets>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QApplication *app);

protected slots:
    QString openFileDialog();

private slots:
    void openFolder();
    void openFile(QModelIndex);
    void initACE();

private:
    void resizeAndCenter(int screenWidth, int screenHeight);
    void showFolderTree(QString folderPath);
    QToolBox *toolBox;
    QSplitter *splitter;
    QTabWidget *tabWidget;
};


#endif // MAINWINDOW_H
