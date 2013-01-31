#-------------------------------------------------
#
# Project created by QtCreator 2011-09-11T16:36:25
#
#-------------------------------------------------

QT       += core gui sql

TARGET = SelfRepairingDatabase
TEMPLATE = app

CONFIG += precompile_header
PRECOMPILED_HEADER += Macros/macros.h

SOURCES += main.cpp\
        mainwindow.cpp \
    Common/Database/selfrepairingdatabase.cpp \
    Common/Database/basedatabase.cpp \
    AppSpec/Database/testdatabasemanager.cpp \
    Common/PathManager/pathmanager.cpp \
    Common/Database/databasetableschemedescription.cpp

HEADERS  += mainwindow.h \
    Common/Database/selfrepairingdatabase.h \
    Common/Database/basedatabase.h \
    AppSpec/Database/testdatabasemanager.h \
    Common/PathManager/pathmanager.h \
    Macros/macros.h \
    Common/Database/databasetableschemedescription.h

RESOURCES += \
    testResources.qrc

# enable debug logging
DEFINES += DEBUG
DEFINES += ENABLE_DATABASE_OPERATION_LOGGING
















