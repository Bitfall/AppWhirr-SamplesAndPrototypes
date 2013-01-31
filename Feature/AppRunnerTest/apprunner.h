#ifndef APPRUNNER_H
#define APPRUNNER_H

#include <QObject>
#include <qstringlist.h>

class AppRunner : public QObject
{
    Q_OBJECT
public:
    explicit AppRunner(QObject *parent = 0);
    
    static QString runThisApp(QString appPath, QString workingDir, QStringList args);
    
};

#endif // APPRUNNER_H
