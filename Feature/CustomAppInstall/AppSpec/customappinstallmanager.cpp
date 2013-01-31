#include "customappinstallmanager.h"

#include <QUrl>
#include <QXmlSchema>
#include <QFile>
#include <QXmlSchemaValidator>
#include <QDomElement>

CustomAppInstallManager::CustomAppInstallManager(QObject *parent) :
    QObject(parent)
{
}

void CustomAppInstallManager::performByFile(QString customInstallFilePath)
{
    //
    // validation

//    bool isValid = true;
//    QUrl schemaUrl(QString(":/InstallXmlSchema"));
//    QXmlSchema schema;
//    schema.load(schemaUrl);
//    QFile schemaAsFile(QString(":/InstallXmlSchema"));
//    schemaAsFile.open(QIODevice::ReadOnly);
//    DLogS << schemaAsFile.readAll();
//    if (schema.isValid()) {
//        QFile file(customInstallFilePath);
//        file.open(QIODevice::ReadOnly);

//        QXmlSchemaValidator validator(schema);
//        if (validator.validate(&file, QUrl::fromLocalFile(file.fileName()))) {
//            isValid = true;
//        }
//        else {
//            isValid = false;
//        }
//    }
//    else {
//        WLog("Invalid Schema!");
//        isValid = false;
//    }

//    if(!isValid) {
//        Q_EMIT finishedWithError("Validation failed.");
//        return;
//    }

    CustomInstallStepsCollectionModel installStepsCollectionModel;
    QString fileProcessingErrorMessage = this->_processFile(customInstallFilePath, installStepsCollectionModel);
    if(!fileProcessingErrorMessage.isEmpty()) {
        Q_EMIT finishedWithError(QString("File processing error: %1").arg(fileProcessingErrorMessage));
    }

    Q_EMIT finishedWithSuccess();
}


QString CustomAppInstallManager::_processFile(QString customInstallFilePath, CustomInstallStepsCollectionModel &outCustomInstallStepsCollectionModel)
{
//    QString errorStr;
//    int errorLine;
//    int errorColumn;

//    if (!domDocument.setContent(device, true, &errorStr, &errorLine,
//                                &errorColumn)) {
//        return this->_createProcessingErrorMessage("Parser error");
//    }

//    QDomElement root = domDocument.documentElement();
//    if (root.tagName() != "install") {
//        return QString("Invalid root tag: %1 | %2 required.").arg(root.tagName()).arg("install");
//    }

//    //
//    // processing 'inargs'
//    QDomElement inargsRootElement = root.firstChildElement("inargs");
//    if(!inargsRootElement.isNull())
//    {
//        QDomElement inargElement = inargsRootElement.firstChildElement("inarg");

//        inargElement = inargElement.nextSiblingElement("inarg");
//    }

    return QString();
}

QString CustomAppInstallManager::_createProcessingErrorMessage(QString errorMessage, int errorLine, int errorColumn)
{
    return QString("Error at line %1, column %2: %3") .arg(errorLine).arg(errorColumn).arg(errorMessage);
}
