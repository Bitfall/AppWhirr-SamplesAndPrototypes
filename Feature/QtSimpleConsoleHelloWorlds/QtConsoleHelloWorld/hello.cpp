#include <QTextStream>
#include "hello.h"

void Hello::world() {
    QTextStream qout(stdout);
    qout << "Hello, world!\n";
    emit done();
}
