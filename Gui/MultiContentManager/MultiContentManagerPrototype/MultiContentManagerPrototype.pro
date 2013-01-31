#-------------------------------------------------
#
# Project created by QtCreator 2011-11-20T18:13:56
#
#-------------------------------------------------

QT       += core gui

TARGET = MultiContentManagerPrototype
TEMPLATE = app

CONFIG += precompiled_header
PRECOMPILED_HEADER = Developer/macros.h

DEFINES += DEBUG

SOURCES += main.cpp\
        mainwindow.cpp \
    Common/multicontentmanager.cpp \
    Common/referencecountingidbasedcollection.cpp \
    Common/Widgets/idbasedwidget.cpp

HEADERS  += mainwindow.h \
    Common/multicontentmanager.h \
    Developer/macros.h \
    Common/idbasediteminterface.h \
    Common/referencecountingidbasedcollection.h \
    Common/Widgets/idbasedwidget.h















