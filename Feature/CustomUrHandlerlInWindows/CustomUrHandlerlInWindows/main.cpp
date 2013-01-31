#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString initialStatusMessage("No args.");
    if(argc == 2) {
        // args found
        initialStatusMessage = QString(argv[1]);
    }
    MainWindow w(initialStatusMessage);
    w.show();

    return a.exec();
}
