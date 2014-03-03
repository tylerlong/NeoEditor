#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QtWidgets>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QApplication *app);

protected slots:
    // javascript callable slots here

private slots:
    void openFolder();
    void openFile(QModelIndex modelIndex);
    void initACE();

private:
    void resizeAndCenter(int screenWidth, int screenHeight);
    void showFolderTree(QString folderPath);
    QString escapeJavascriptString(const QString &input);
    QToolBox *toolBox;
    QSplitter *splitter;
    QTabWidget *tabWidget;
};


#endif // MAINWINDOW_H
