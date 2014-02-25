#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow *mainWindow = new MainWindow(&app);
    mainWindow->show();
    return app.exec();
}
