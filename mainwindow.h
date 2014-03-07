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
    void initACE();
    void closeLeftTab(int index);
    void about();

private:
    void showFolderTree(QString folderPath);
    QString escapeJavascriptString(const QString &input);
    QSplitter *splitter;
    QTabWidget *leftTabWidget;
    QTabWidget *rightTabWidget;
};


#endif // MAINWINDOW_H
