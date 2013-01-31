#-------------------------------------------------
#
# Project created by QtCreator 2012-03-30T13:12:29
#
#-------------------------------------------------

QT       += core gui network script

TARGET = LargeFileDownloader
TEMPLATE = app

CONFIG += precompile_header
CONFIG += no_keywords

PRECOMPILED_HEADER = Developer/macros.h

DEFINES += ENABLE_APPWHIRR_LOGGING

SOURCES += main.cpp\
        mainwindow.cpp \
    Common/bufferedtransmitter.cpp \
    Common/File/streamtofile.cpp \
    Common/File/streamtofilemanager.cpp \
    Common/backgroundworkerqueue.cpp \
    Common/Communication/communicationresourcegateway.cpp \
    Common/Communication/basenetworkresponse.cpp \
    Common/Communication/basenetworkrequest.cpp \
    Common/Communication/resourcedownloadstreamtofile.cpp \
    Common/Communication/resourcedownloadstreamtomemory.cpp

HEADERS  += mainwindow.h \
    Developer/macros.h \
    Common/bufferedtransmitter.h \
    Common/File/streamtofile.h \
    Common/runnableitem.h \
    Common/File/streamtofilemanager.h \
    Common/backgroundworkerqueue.h \
    Common/Communication/resourcedownloadnetworkrequest.h \
    Common/Communication/communicationresourcegateway.h \
    Common/Communication/basenetworkresponse.h \
    Common/Communication/basenetworkrequest.h \
    Common/Communication/basenetworkentity.h \
    Common/Communication/resourcedownloadstreamtofile.h \
    Common/Communication/resourcedownloadstreamtomemory.h \
    Common/Communication/networkrequestcachedelegate.h

FORMS    += mainwindow.ui
