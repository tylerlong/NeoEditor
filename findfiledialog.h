#ifndef FINDFILEDIALOG_H
#define FINDFILEDIALOG_H


#include <QtWidgets>

class FindFileDialog : public QDialog
{
    Q_OBJECT

public:
    FindFileDialog(QString folderPath);

private slots:
    void showFiles(QString s);
    void openFile(QModelIndex modelIndex);

private:
    QLineEdit *lineEdit;
    QListView *listView;
    QString folderPath;
};


#endif // FINDFILEDIALOG_H
