#-------------------------------------------------
#
# Project created by QtCreator 2011-01-18T11:07:28
#
#-------------------------------------------------

QT       += core gui

TARGET = QtGuiFromCodeTests
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

#changing defines sometimes requires a ReCompile
Debug:DEFINES += DO_IT_ONLY_IN_DEBUG
