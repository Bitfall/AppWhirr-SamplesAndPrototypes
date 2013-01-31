#-------------------------------------------------
#
# Project created by QtCreator 2011-11-23T14:12:41
#
#-------------------------------------------------

QT       += core gui

TARGET = FrameworkCheck
TEMPLATE = app

CONFIG += precompiled_header
PRECOMPILED_HEADER = Developer/macros.h

DEFINES += DEBUG

SOURCES += main.cpp\
        mainwindow.cpp \
    AppSpec/SupportedFrameworks/supportedframeworkinfos.cpp \
    Common/Helpers/pathhelper.cpp \
    Common/Framework/frameworkinstaller.cpp \
    Common/Framework/frameworkinfo.cpp \
    Common/Framework/frameworkcheckmodel.cpp \
    Common/Framework/backgroundframeworkinstaller.cpp \
    Common/Framework/backgroundframeworkcheck.cpp \
    Common/Framework/availableframeworkchecker.cpp \
    Common/Framework/frameworkinstallmodel.cpp

HEADERS  += \
    Developer/macros.h \
    mainwindow.h \
    AppSpec/SupportedFrameworks/supportedframeworkinfos.h \
    Common/Helpers/pathhelper.h \
    Common/Framework/frameworkinstaller.h \
    Common/Framework/frameworkinfo.h \
    Common/Framework/frameworkcheckmodel.h \
    Common/Framework/backgroundframeworkinstaller.h \
    Common/Framework/backgroundframeworkcheck.h \
    Common/Framework/availableframeworkchecker.h \
    Common/Framework/frameworkinstallmodel.h

RESOURCES += \
    resources.qrc





