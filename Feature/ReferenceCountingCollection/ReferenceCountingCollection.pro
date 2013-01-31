#-------------------------------------------------
#
# Project created by QtCreator 2011-11-20T20:49:44
#
#-------------------------------------------------

QT       += core gui

TARGET = ReferenceCountingCollection
TEMPLATE = app

CONFIG += precompiled_header
PRECOMPILED_HEADER = Developer/macros.h

DEFINES += DEBUG


SOURCES += main.cpp\
        mainwindow.cpp \
    Common/referencecountingidbasedcollection.cpp

HEADERS  += mainwindow.h \
    Common/referencecountingidbasedcollection.h \
    Common/idbasediteminterface.h \
    Developer/macros.h



