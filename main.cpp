#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow *mainWindow = new MainWindow();
    QDesktopWidget *desktop = app.desktop();
    mainWindow->resizeAndCenter(desktop->width(), desktop->height());
    mainWindow->show();
    return app.exec();
}
