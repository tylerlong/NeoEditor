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

private:
    void resizeAndCenter(int screenWidth, int screenHeight);
    void showFolderTree(QString folderPath);
    QToolBox *leftPanel;
    QSplitter *splitter;
};


#endif // MAINWINDOW_H
