#ifndef BACKGROUNDFRAMEWORKINSTALLER_H
#define BACKGROUNDFRAMEWORKINSTALLER_H

#include <QObject>

#include "frameworkinstallmodel.h"

/*! Framework installer designed to be used with QThread in a background thread

    Specify the required installer information in the constructor, then you can start the install with the \a startInstall() method (slot) and it will emit the result.

    @note When the \a finished() signal emitted the object is safe to release. This signal will be emitted in every case the installer finishes. When the \a finishedWith..() signals emitted it's NOT safe to relese the object, only when the \a finished() signal emitted!
*/
class BackgroundFrameworkInstaller : public QObject
{
    Q_OBJECT
public:
    explicit BackgroundFrameworkInstaller(FrameworkInstallModel frameworkInstallModel);

public Q_SLOTS:
    void startFrameworkInstall();

Q_SIGNALS:
    void finishedWithSuccess(FrameworkInstallModel frameworkInstallModel);
    void finishedWitError(FrameworkInstallModel frameworkInstallModel, QString error);
    void finished();

private:
    void _emitFailedWithError(QString errorMessage);
    
private:
    FrameworkInstallModel _frameworkInstallModel;
};

#endif // BACKGROUNDFRAMEWORKINSTALLER_H
