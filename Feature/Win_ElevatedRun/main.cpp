#include <QtGui/QApplication>

#include <QProcess>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setQuitOnLastWindowClosed(false);
    // start the application
    a.exec();

    if() {
        // mode == detached
        // start detached then return immediately
        QProcess::startDetached()
    }
    else {
        // mode == attached
        // wait for the end then return with the return of the app
    }

    return a.exec();
}
