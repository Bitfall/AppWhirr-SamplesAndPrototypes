#include <QtCore/QCoreApplication>

#include "Common/Json/json.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    DLog("Hello world");

    QVariantMap map;
    map["name"] = "Name";
    map["age"] = 22;

    DLog("Serialize map: ") << QtJson::Json::serialize(map);

    // ---

    QVariantList listOfMaps;
    for(int i = 0; i < 10; ++i) {
        QVariantMap iMap;
        iMap["applicationID"] = QString::number(i);
        listOfMaps.append(iMap);
    }

    DLog("Serialize list of maps: ") << QtJson::Json::serialize(listOfMaps);

    return a.exec();
}
