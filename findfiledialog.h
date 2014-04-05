#ifndef FINDFILEDIALOG_H
#define FINDFILEDIALOG_H


#include <QtWidgets>

class FindFileDialog : public QDialog
{
    Q_OBJECT

public:
    FindFileDialog();

private:
    QLineEdit *lineEdit;
};


#endif // FINDFILEDIALOG_H
