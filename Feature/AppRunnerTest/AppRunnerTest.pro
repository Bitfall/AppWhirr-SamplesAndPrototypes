#-------------------------------------------------
#
# Project created by QtCreator 2012-03-04T22:26:54
#
#-------------------------------------------------

QT       += core gui

TARGET = AppRunnerTest
TEMPLATE = app

CONFIG += precompile_header
PRECOMPILED_HEADER = Developer/macros.h

DEFINES += DEBUG

SOURCES += main.cpp\
        mainwindow.cpp \
    apprunner.cpp

HEADERS  += mainwindow.h \
    apprunner.h \
    Developer/macros.h

FORMS    += mainwindow.ui
