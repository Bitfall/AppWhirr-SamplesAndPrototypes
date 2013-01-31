#include "installprogressnotificationwidget.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QTimer>

// config
#include "Settings/guiconfigurations.h"

InstallProgressNotificationWidget::InstallProgressNotificationWidget(QString appId, QString appName, QWidget *parent) :
    SelfTimeoutingNotificationWidgetBase(parent),
    _appId(appId),
    _appName(appName),
    _isStateChanged(false)
{
    QHBoxLayout *mainLayout = new QHBoxLayout;
    this->setLayout(mainLayout);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    this->_statusLabel = new QLabel;
    this->_statusLabel->setText(_appName + " " + tr("grabbing..."));
    this->_statusLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    mainLayout->addWidget(_statusLabel);

    this->_finishedTimer = new QTimer(this);
    this->_finishedTimer->setSingleShot(true);
    this->_finishedTimer->setInterval(5000);
    this->_finishedTimer->stop();
    connect(this->_finishedTimer, SIGNAL(timeout()), this, SLOT(_finishTimerTimeout()));

    this->_stateUpdateTimer = new QTimer(this);
    _stateUpdateTimer->setSingleShot(true);
    _stateUpdateTimer->setInterval(2000);
    _stateUpdateTimer->stop();
    connect(_stateUpdateTimer, SIGNAL(timeout()), this, SLOT(_doStateUpdate()));

    this->setStyleSheet(GuiConfigurations::installProgressNotificationStyleSheetForPriorityHigh());
}

void InstallProgressNotificationWidget::_finishTimerTimeout() {
    Q_EMIT this->notificationFinished();
}

void InstallProgressNotificationWidget::setGrabbed()
{   
    this->_setNewState(_appName + " " + tr("grabbed!"), GuiConfigurations::installProgressNotificationStyleSheetForPriorityLow());
}

void InstallProgressNotificationWidget::setDownloading()
{
    this->_setNewState(_appName + " " + tr("downloading") + "...", GuiConfigurations::installProgressNotificationStyleSheetForPriorityNormal());
}

void InstallProgressNotificationWidget::setDownloadProgress(int progress)
{
    QString titleText;
    if(progress < 100) {
        titleText = _appName + " " + tr("downloading: ") + QString("%1%").arg(progress);
    }
    else {
        // finished downloading, waiting for installation
        titleText = _appName + " " + tr("installing...");
    }
    this->_setNewState(titleText, GuiConfigurations::installProgressNotificationStyleSheetForPriorityNormal());
}

void InstallProgressNotificationWidget::setInstallStarted()
{
    this->_setNewState(_appName + " " + tr("installing") + "...", GuiConfigurations::installProgressNotificationStyleSheetForPriorityLow());
}

void InstallProgressNotificationWidget::setInstalled()
{
    this->_setNewState(_appName + " " + tr("installed!"), GuiConfigurations::installProgressNotificationStyleSheetForPriorityHigh());
    this->_finishedTimer->start();
}

void InstallProgressNotificationWidget::setGrabFailedWithError(QString errorMessage)
{
    this->_setNewState(_appName + " " + tr("failed to grab! Error message: ") + errorMessage, GuiConfigurations::installProgressNotificationStyleSheetForPriorityCritical());
    this->_finishedTimer->start();
}

void InstallProgressNotificationWidget::setInstallFailedWithError(QString errorMessage)
{
    this->_setNewState(_appName + " " + tr("failed to install! Error message: ") + errorMessage, GuiConfigurations::installProgressNotificationStyleSheetForPriorityCritical());
    this->_finishedTimer->start();
}

void InstallProgressNotificationWidget::_doStateUpdate()
{
    if(!this->_isStateChanged) {
        return;
    }

    this->_isStateChanged = false;

    this->_statusLabel->setText(this->_currentStateInformation.getTitleText());
    this->setStyleSheet(this->_currentStateInformation.getStyleSheet());
}

void InstallProgressNotificationWidget::_setNewState(QString title, QString styleSheet)
{
    this->_currentStateInformation = InstallStateInformationModel(title, styleSheet);
    this->_isStateChanged = true;

    if(!this->_stateUpdateTimer->isActive()) {
        this->_stateUpdateTimer->start();
    }
}
