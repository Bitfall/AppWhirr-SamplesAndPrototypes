#-------------------------------------------------
#
# Project created by QtCreator 2011-10-31T17:18:28
#
#-------------------------------------------------

QT       += core gui
QT += svg
QT += xml
QT += network
QT += script
QT += sql
QT += webkit

TARGET = FlashWithQtWebKit
TEMPLATE = app

CONFIG += precompile_header
CONFIG += no_keywords

PRECOMPILED_HEADER = Developer/macros.h

DEFINES += DEBUG

SOURCES += main.cpp\
        mainwindow.cpp \
    Common/guiconfigurationmanager.cpp

HEADERS  += mainwindow.h \
    Common/guiconfigurationmanager.h \
    Developer/macros.h

RESOURCES += \
    resources.qrc
