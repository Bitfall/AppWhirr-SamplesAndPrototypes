#-------------------------------------------------
#
# Project created by QtCreator 2012-01-30T19:12:09
#
#-------------------------------------------------

QT       += core gui

TARGET = CopyAndDeleteTest
TEMPLATE = app

CONFIG += precompile_header
CONFIG += no_keywords

PRECOMPILED_HEADER = Developer/macros.h

DEFINES += DEBUG


SOURCES += main.cpp\
        mainwindow.cpp \
    Common/Helpers/pathhelper.cpp

HEADERS  += mainwindow.h \
    Developer/macros.h \
    Common/Helpers/pathhelper.h
