#-------------------------------------------------
#
# Project created by QtCreator 2011-12-01T18:38:00
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = JSonExample
CONFIG   += console
CONFIG   -= app_bundle

CONFIG += precompile_header
PRECOMPILED_HEADER = Developer/macros.h

DEFINES += DEBUG

TEMPLATE = app


SOURCES += main.cpp \
    Common/Json/json.cpp

HEADERS += \
    Common/Json/json.h \
    Developer/macros.h



