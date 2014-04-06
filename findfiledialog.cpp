#include "findfiledialog.h"
#include "mainwindow.h"

FindFileDialog::FindFileDialog(QString folderPath)
{
    this->folderPath = folderPath;
    this->setWindowFlags(Qt::WindowStaysOnTopHint);
    this->setWindowTitle(tr("Find File"));
    lineEdit = new QLineEdit();
    lineEdit->setFixedWidth(512);
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(lineEdit);
    this->setLayout(layout);

    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    move(screenGeometry.center() - rect().center());

    connect(lineEdit, SIGNAL(textChanged(const QString &)), this, SLOT(showFiles(const QString &)));

    listView = new QListView(lineEdit);
    listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(listView, SIGNAL(clicked(QModelIndex)), this, SLOT(openFile(QModelIndex)));
    layout->addWidget(listView);

    layout->setSpacing(0);
    this->adjustSize();
}

void FindFileDialog::showFiles(QString s)
{
    QStringListModel *stringListModel = new QStringListModel(listView);
    QStringList *stringList = new QStringList();

    QDirIterator directory_walker(folderPath, QDir::Files | QDir::NoSymLinks, QDirIterator::Subdirectories);
    while(directory_walker.hasNext())
    {
        directory_walker.next();
        QString fileName = directory_walker.filePath().mid(folderPath.length() + 1);
        if(fileName.contains(s))
        {
            stringList->append(fileName);
            if(stringList->size() > 8)
            {
                break;
            }
        }
    }

    stringListModel->setStringList(*stringList);
    listView->setModel(stringListModel);
}

void FindFileDialog::openFile(QModelIndex modelIndex)
{
    QString filePath = QString("%1/%2").arg(folderPath, ((QStringListModel*)listView->model())->stringList().at(modelIndex.row()));
    emit MainWindow::GetInstance()->openFileRequested(filePath);
    this->close();
}
