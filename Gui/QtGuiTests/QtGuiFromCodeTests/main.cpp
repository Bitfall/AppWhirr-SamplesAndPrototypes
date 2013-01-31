#include <QtGui/QApplication>
#include "mainwindow.h"

#include <QStyleFactory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qDebug("---");
    qDebug("Valid style keys:");
    QStringList keysList = QStyleFactory::keys();
    for(int i = keysList.count()-1; i > 0; i--)
    {
        qDebug(keysList.at(i).toAscii());
    }
    qDebug("---");

    qApp->setStyle( QStyleFactory::create( "Cleanlooks" ) );

    MainWindow w;
    w.show();

    return a.exec();
}
