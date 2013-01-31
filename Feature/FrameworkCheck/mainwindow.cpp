#include "mainwindow.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>

#include "AppSpec/SupportedFrameworks/supportedframeworkinfos.h"
#include "Common/Framework/availableframeworkchecker.h"
#include "Common/Framework/frameworkinstaller.h"

#include "Common/Helpers/pathhelper.h"
#include <QApplication>

// test
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *mainCentralWidget = new QWidget;
    this->setCentralWidget(mainCentralWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainCentralWidget->setLayout(mainLayout);

    _requiredFrameworksLineEdit = new QLineEdit;
    _requiredFrameworksLineEdit->setPlaceholderText(tr("Separate the frameworks' name with ';'"));
    mainLayout->addWidget(_requiredFrameworksLineEdit);

    _installFrameworksButton = new QPushButton(tr("Install required frameworks."));
    connect(_installFrameworksButton, SIGNAL(clicked()), this, SLOT(_installRequiredFrameworks()));
    mainLayout->addWidget(_installFrameworksButton);
    _installFrameworksButton->hide();

    _checkForFrameworksButton = new QPushButton(tr("Check for frameworks."));
    connect(_checkForFrameworksButton, SIGNAL(clicked()), this, SLOT(_checkForFrameworks()));
    mainLayout->addWidget(_checkForFrameworksButton);

    _supportedFrameworkInfos = new SupportedFrameworkInfos(this);
    _frameworkChecker = new AvailableFrameworkChecker(this);
    connect(_frameworkChecker, SIGNAL(finishedWithChecking()), this, SLOT(_frameworkCheckingFinished()));
    connect(_frameworkChecker, SIGNAL(frameworksAvailable(QList<FrameworkCheckModel>)), this, SLOT(_availableFrameworksFound(QList<FrameworkCheckModel>)));
    connect(_frameworkChecker, SIGNAL(frameworksNotFound(QList<FrameworkCheckModel>)), this, SLOT(_installTheseFrameworks(QList<FrameworkCheckModel>)));
    _frameworkInstaller = new FrameworkInstaller(this);
    connect(_frameworkInstaller, SIGNAL(frameworkInstalled(FrameworkInstallModel)), this, SLOT(_frameworkInstalled(FrameworkInstallModel)));
    connect(_frameworkInstaller, SIGNAL(frameworkInstallFailed(FrameworkInstallModel,QString)), this, SLOT(_frameworkInstallFailed(FrameworkInstallModel,QString)));

    // installer pathes for testing
    _frameworkIdToFrameworkInstallerPathMap.insert(SupportedFrameworkInfos::SFI_MSVC2005redist_x86, "./frameworks/inst/msvc2005/vcredist_x86.exe");
    _frameworkIdToFrameworkInstallerPathMap.insert(SupportedFrameworkInfos::SFI_DotNet40, "./frameworks/inst/dotNet4/dotNetFx40_Full_setup.exe");
}

MainWindow::~MainWindow()
{

}

void MainWindow::_installRequiredFrameworks()
{

}

void MainWindow::_checkForFrameworks()
{
    DLog("-- start checking");

    QString frameworkCheckResultDirPath = PathHelper::combineAndCleanPathes(QApplication::applicationDirPath(), "frameworks/checkresult");
    DLog("FW checker result dir path: ") << frameworkCheckResultDirPath;
    if(!PathHelper::ensureDirectoryCreated(frameworkCheckResultDirPath)) {
        WLog("Cannot create the check-result file's directory: ") << frameworkCheckResultDirPath;
        return;
    }

    QList<FrameworkCheckModel> frameworksForCheck;
    frameworksForCheck.append(FrameworkCheckModel(FrameworkInfo(SupportedFrameworkInfos::SFI_MSVC2005redist_x86, "MSVC 2005 redist (x86)"), _supportedFrameworkInfos->getFrameworkCheckerPathForFramework(SupportedFrameworkInfos::SFI_MSVC2005redist_x86), frameworkCheckResultDirPath));
    frameworksForCheck.append(FrameworkCheckModel(FrameworkInfo(SupportedFrameworkInfos::SFI_MSVC2008redist_x86, "MSVC 2008 redist (x86)"), _supportedFrameworkInfos->getFrameworkCheckerPathForFramework(SupportedFrameworkInfos::SFI_MSVC2008redist_x86), frameworkCheckResultDirPath));
    frameworksForCheck.append(FrameworkCheckModel(FrameworkInfo(SupportedFrameworkInfos::SFI_DotNet30, ".Net 3.0"), _supportedFrameworkInfos->getFrameworkCheckerPathForFramework(SupportedFrameworkInfos::SFI_DotNet30), frameworkCheckResultDirPath));
    frameworksForCheck.append(FrameworkCheckModel(FrameworkInfo(SupportedFrameworkInfos::SFI_DotNet40, ".Net 4.0"), _supportedFrameworkInfos->getFrameworkCheckerPathForFramework(SupportedFrameworkInfos::SFI_DotNet40), frameworkCheckResultDirPath));
    _frameworkChecker->checkForFrameworksAsync(frameworksForCheck);
}

void MainWindow::_installTheseFrameworks(QList<FrameworkCheckModel> frameworkCheckInfos)
{
    DLog("-- frameworks have to be installed");
    Q_FOREACH(FrameworkCheckModel frameworkCheckInfo, frameworkCheckInfos)
    {
        DLog("FW install: ") << frameworkCheckInfo.getFrameworkInfo().getFrameworkPrintableName();

        FrameworkInfo fwInfo = frameworkCheckInfo.getFrameworkInfo();
        QString fwInstallerPath(_frameworkIdToFrameworkInstallerPathMap.value(fwInfo.getFrameworkId(), QString()));
        _frameworkInstaller->startFrameworkInstallAsync(FrameworkInstallModel(fwInfo, fwInstallerPath));
    }
}

void MainWindow::_availableFrameworksFound(QList<FrameworkCheckModel> frameworkCheckInfos)
{
    DLog("-- available frameworks");
    Q_FOREACH(FrameworkCheckModel frameworkInfo, frameworkCheckInfos)
    {
        DLog("FW: ") << frameworkInfo.getFrameworkInfo().getFrameworkPrintableName();
    }
}

void MainWindow::_frameworkCheckingFinished()
{
    DLog("Framework checking finished");
}

void MainWindow::_frameworkInstalled(FrameworkInstallModel frameworkInstallModel)
{
    QMessageBox::information(this, "FW install Success", "Success: " + frameworkInstallModel.getFrameworkInfo().getFrameworkPrintableName());
    DLog("FW install success: ") << frameworkInstallModel.getFrameworkInfo().getFrameworkId() << frameworkInstallModel.getFrameworkInfo().getFrameworkPrintableName();
}

void MainWindow::_frameworkInstallFailed(FrameworkInstallModel frameworkInstallModel, QString errorMessage)
{
    QMessageBox::information(this, "FW install Failed", frameworkInstallModel.getFrameworkInfo().getFrameworkPrintableName() + " " + errorMessage);
    DLog("FW install failed: ") << frameworkInstallModel.getFrameworkInfo().getFrameworkId() << frameworkInstallModel.getFrameworkInfo().getFrameworkPrintableName() << " with error: " << errorMessage;
}
