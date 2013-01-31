#include "globalobjectregistry.h"

#include "Common/Database/simplelogdatabasemanager.h"
#include "AppSpec/testdatabaseservermanager.h"

GlobalObjectRegistry::GlobalObjectRegistry()
{
    _simpleLogDbManager = new SimpleLogDatabaseManager;
    _testDbServer = new TestDatabaseServerManager;
}

GlobalObjectRegistry *GlobalObjectRegistry::sharedGlobalObjectRegistry()
{
    static GlobalObjectRegistry *globObjReg = NULL;

    if(globObjReg == NULL) {
        globObjReg = new GlobalObjectRegistry;
    }

    return globObjReg;
}

SimpleLogDatabaseManager *GlobalObjectRegistry::getSimpleLogDatabaseManager() const
{
    return this->_simpleLogDbManager;
}

TestDatabaseServerManager *GlobalObjectRegistry::getTestDatabaseServerManager() const {
    return this->_testDbServer;
}
