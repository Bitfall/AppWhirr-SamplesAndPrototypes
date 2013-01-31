#ifndef INSTALLPROGRESSNOTIFICATIONWIDGET_H
#define INSTALLPROGRESSNOTIFICATIONWIDGET_H

#include "Browser/Notification/selftimeoutingnotificationwidgetbase.h"

QT_BEGIN_NAMESPACE
class QLabel;
class QTimer;
QT_END_NAMESPACE

class InstallProgressNotificationWidget : public SelfTimeoutingNotificationWidgetBase
{
    Q_OBJECT

private:
    class InstallStateInformationModel {
    public:
        explicit InstallStateInformationModel() {}
        explicit InstallStateInformationModel(QString titleText, QString styleSheet) : titleText(titleText), styleSheet(styleSheet) {}

        QString getTitleText() const { return titleText; }
        QString getStyleSheet() const { return styleSheet; }

    private:
        QString titleText;
        QString styleSheet;
    };

public:
    explicit InstallProgressNotificationWidget(QString appId, QString appName, QWidget *parent = 0);

public Q_SLOTS:
    void setGrabbed();
    void setDownloading();
    void setDownloadProgress(int progress);
    void setInstallStarted();
    void setInstalled();

    void setGrabFailedWithError(QString errorMessage);
    void setInstallFailedWithError(QString errorMessage);

private Q_SLOTS:
    void _finishTimerTimeout();
    void _doStateUpdate();

private:
    void _setNewState(QString title, QString styleSheet);

private:
    QLabel *_statusLabel;
    QTimer *_finishedTimer;

    QString _appId;
    QString _appName;

    bool _isStateChanged;
    InstallStateInformationModel _currentStateInformation;
    QTimer *_stateUpdateTimer;
};

#endif // INSTALLPROGRESSNOTIFICATIONWIDGET_H
