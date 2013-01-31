#ifndef GLOBALOBJECTREGISTRY_H
#define GLOBALOBJECTREGISTRY_H

class SimpleLogDatabaseManager;
class TestDatabaseServerManager;

class GlobalObjectRegistry
{
private:
    GlobalObjectRegistry();

public:
    static GlobalObjectRegistry *sharedGlobalObjectRegistry();

    SimpleLogDatabaseManager *getSimpleLogDatabaseManager() const;
    TestDatabaseServerManager *getTestDatabaseServerManager() const;

private:
    SimpleLogDatabaseManager *_simpleLogDbManager;
    TestDatabaseServerManager *_testDbServer;
};

#endif // GLOBALOBJECTREGISTRY_H
