#include "findfiledialog.h"

FindFileDialog::FindFileDialog()
{
    this->setWindowFlags(Qt::WindowStaysOnTopHint);
    this->setWindowTitle(tr("Find File"));
    lineEdit = new QLineEdit();
    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(lineEdit);
    this->setLayout(layout);

    this->adjustSize();
    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    move(screenGeometry.center() - rect().center());
}
