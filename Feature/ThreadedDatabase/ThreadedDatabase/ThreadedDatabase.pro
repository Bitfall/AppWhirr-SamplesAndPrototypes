#-------------------------------------------------
#
# Project created by QtCreator 2011-09-21T18:57:31
#
#-------------------------------------------------

QT       += core gui sql

TARGET = ThreadedDatabase
TEMPLATE = app

CONFIG += precompile_header
PRECOMPILED_HEADER = Macros/macros.h


SOURCES += main.cpp\
        mainwindow.cpp \
    Common/Database/simplelogdatabasemanager.cpp \
    Common/Database/basedatabase.cpp \
    Common/Database/databasetableschemedescriptor.cpp \
    AppSpec/testmasslogger.cpp \
    AppSpec/globalobjectregistry.cpp \
    AppSpec/testmassloggerwithqthread_worker.cpp \
    AppSpec/testdatabaseservermanager.cpp \
    AppSpec/testdatabaseworker.cpp

HEADERS  += mainwindow.h \
    Common/Database/simplelogdatabasemanager.h \
    Common/Database/basedatabase.h \
    Common/Database/databasetableschemedescriptor.h \
    Macros/macros.h \
    AppSpec/testmasslogger.h \
    AppSpec/globalobjectregistry.h \
    AppSpec/testmassloggerwithqthread_worker.h \
    AppSpec/testdatabaseservermanager.h \
    AppSpec/testdatabaseworker.h \
    AppSpec/test_addtodatabaseserver.h

DEFINES += DEBUG
DEFINES += ENABLE_DATABASE_OPERATION_LOGGING
























