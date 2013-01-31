#include "apprunner.h"

#include <QProcess>
#include <QFile>
#include <QFileInfo>
#include <QDir>

AppRunner::AppRunner(QObject *parent) :
    QObject(parent)
{
}

QString AppRunner::runThisApp(QString appPath, QString workingDir, QStringList args)
{
    QString retLogText;
    retLogText.append( QString("Run app with path (%1) working dir (%2)\n").arg(appPath).arg(workingDir) );
    Q_FOREACH(QString arg, args) {
        retLogText.append( QString(" -arg: %1\n").arg(arg) );
    }

//    Q_UNUSED(workingDir);


    // perform some checking

//        if(appPath.isEmpty() || !QFile::exists(appPath)) {
//            WLog("The framework-checker app-path is empty or invalid! ") << 123 << "test";
//            return false;
//        }
//        if(frameworkCheckModel.getFrameworkResultFileDirPath().isEmpty()) {
//            WLog("Result file dir path is empty!");
//    //        return false;
//        }

//        QFileInfo checkerAppFileInfo(appPath);
//        QDir checkerAppDir = checkerAppFileInfo.absoluteDir();
//        QString checkerWorkingDirPath = checkerAppDir.canonicalPath();
//        if(!checkerAppDir.exists() || checkerWorkingDirPath.isEmpty()) {
//            WLog("The framework-checker working dir-path is empty or invalid! ") << 123 << "test" << "working dir path: " << checkerWorkingDirPath;
//            return false;
//        }




//        QString resultFileName = QString("%1-fwcheckresult.txt").arg(123);


//        QString frameworkResultFilePath = PathHelper::combineAndCleanPathes(frameworkCheckModel.getFrameworkResultFileDirPath(), resultFileName);

//        // test for the result file and remove it if exists
//        if(QFile::exists(frameworkResultFilePath))
//        {
//            QFile resultFile(frameworkResultFilePath);
//            if(!resultFile.remove()) {
//                WLog("Cannot remove the existing result file!");
//            }
//            else {
//                DLog("Succesfully removed the previous result file");
//            }
//        }

//    //    frameworkResultFilePath = PathHelper::makePathPlatformDependent(frameworkResultFilePath);
//        DLog("Result file path: ") << frameworkResultFilePath;

//        // run the related fw checker app
//        QStringList fwCheckerAppArgs;
//        fwCheckerAppArgs << "-outFilePath" << frameworkResultFilePath;

//        if(!frameworkCheckModel.getOptionalFrameworkCheckerArg().isEmpty()) {
//            // add optinal fw checker arg as well
//            fwCheckerAppArgs << "-checkerArg" << frameworkCheckModel.getOptionalFrameworkCheckerArg();
//        }

        DLog("Framework checker will start at path: ") << appPath << "| with working dir: " << workingDir << "| args: " << args;

        QProcess process;

        DLog("Process environment: ") << process.processEnvironment().toStringList();

        if(!workingDir.isEmpty()) {
            process.setWorkingDirectory(workingDir);
        }
        process.start(appPath, args, QProcess::ReadOnly);
        process.waitForFinished(50000);

        QString stdOutRes = process.readAllStandardOutput();
        DLog("Std out: ") << stdOutRes;
        retLogText.append( QString("Std out: %1\n").arg(stdOutRes) );

        QString stdErrRes = process.readAllStandardError();
        DLog("Std error: ") << stdErrRes;
        retLogText.append( QString("Std err: %1\n").arg(stdErrRes) );

        // check the result
        if(process.exitCode() != 0) {
            WLog("Exit code not 0: ") << process.exitCode();
            retLogText.append( QString("Exit code not 0: %1\n").arg(process.exitCode()) );
            return retLogText;
        }

        DLog("Exit code 0!");
        retLogText.append("Exit code is 0.\n");

//        QProcess::startDetached(appPath, args, workingDir);


        return retLogText;
}
