#include <QCoreApplication>
#include <QTimer>
#include <QTextStream>

int main(int argc, char** argv) {
    QCoreApplication app(argc, argv);

    QTextStream cout(stdout, QIODevice::WriteOnly);

    cout << "Hello World (presented for 4 seconds, then it will exit automatically)\n";
    cout.flush();

    QTimer::singleShot(4000, &app, SLOT(quit()));
    return app.exec();
}



#if 0

#include <QCoreApplication>
#include <QTimer>

#include "hello.h"

int main(int argc, char** argv) {
    QCoreApplication app(argc, argv);
    Hello hello;
    QObject::connect(&hello, SIGNAL(done()), &app, SLOT(quit()));
    QTimer::singleShot(1000, &hello, SLOT(world()));
    return app.exec();
}

#endif


#if 0

#include <iostream>
using namespace std;

int main(int argc, char **argv){
   cout << "Hello World!" << endl;

   cin.get();

   return 0;
}

#endif




#if 0

#include <QTextStream>

int main(int argc, char **argv){
  QTextStream cout(stdout, QIODevice::WriteOnly);

  cout << "Hello World\n";

  return 0;
}

#endif
