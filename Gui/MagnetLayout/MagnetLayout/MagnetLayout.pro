#-------------------------------------------------
#
# Project created by QtCreator 2011-11-10T23:16:54
#
#-------------------------------------------------

QT       += core gui

TARGET = MagnetLayout
TEMPLATE = app

CONFIG += precompiled_header
PRECOMPILED_HEADER = Macros/macros.h

DEFINES += DEBUG


SOURCES += main.cpp\
        mainwindow.cpp \
    MagnetLayoutSystem/magnetmanager.cpp \
    MagnetLayoutSystem/magnetlink.cpp \
    MagnetLayoutSystem/magnetwidget.cpp \
    MagnetLayoutSystem/magnetpoint.cpp \
    MagnetLayoutSystem/Events/magnetpointaddedevent.cpp

HEADERS  += mainwindow.h \
    MagnetLayoutSystem/magnetmanager.h \
    MagnetLayoutSystem/magnetlink.h \
    MagnetLayoutSystem/magnetwidget.h \
    MagnetLayoutSystem/magnetpoint.h \
    Macros/macros.h \
    MagnetLayoutSystem/Events/magnetpointaddedevent.h \
    MagnetLayoutSystem/Events/magneteventbase.h




















