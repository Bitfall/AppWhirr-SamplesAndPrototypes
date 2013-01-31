#include <QtGui/QApplication>
#include "prototypebrowserwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PrototypeBrowserWindow w;
    w.show();

    return a.exec();
}
