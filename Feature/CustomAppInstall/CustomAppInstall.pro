#-------------------------------------------------
#
# Project created by QtCreator 2011-11-23T14:04:51
#
#-------------------------------------------------

QT       += core gui xmlpatterns xml

TARGET = CustomAppInstall
TEMPLATE = app

CONFIG += precompiled_header
PRECOMPILED_HEADER = Developer/macros.h

DEFINES += DEBUG


SOURCES += main.cpp\
        mainwindow.cpp \
    AppSpec/customappinstallmanager.cpp \
    AppSpec/custominstallstepmodel.cpp \
    AppSpec/custominstallstepscollectionmodel.cpp

HEADERS  += mainwindow.h \
    Developer/macros.h \
    AppSpec/customappinstallmanager.h \
    AppSpec/custominstallstepmodel.h \
    AppSpec/custominstallstepscollectionmodel.h

RESOURCES += \
    resources.qrc












