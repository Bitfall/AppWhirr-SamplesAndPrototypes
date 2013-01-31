#-------------------------------------------------
#
# Project created by QtCreator 2012-01-12T18:53:05
#
#-------------------------------------------------

QT       += core gui

TARGET = ZipTesterGui
TEMPLATE = app


CONFIG += precompile_header
CONFIG += no_keywords
PRECOMPILED_HEADER = Developer/macros.h


# 3rd-party and depending
INCLUDEPATH += ../3rdParty/quazip
win32:INCLUDEPATH += "$$(QT_SRC_REFERENCE_ROOT_DIR)/3rdparty/zlib"

DEFINES += DEBUG
DEFINES += ENABLE_COMPRESSION_LOGGING


SOURCES += main.cpp\
        mainwindow.cpp \
    Common/Uncompressor/uncompressor.cpp \
    Common/Helpers/pathhelper.cpp

HEADERS  += mainwindow.h \
    Developer/macros.h \
    Common/Uncompressor/uncompressor.h \
    Common/Uncompressor/gojobzip.h \
    Common/Helpers/pathhelper.h


# ===================
# -- MAC
mac {
# icon
#    ICON = ApplicationLauncher.icns
    LIBS+=/System/Library/Frameworks/Carbon.framework/Carbon
#    LIBS += -framework AppKit
    LIBS+=/System/Library/Frameworks/ApplicationServices.framework/ApplicationServices

# depending libs
    LIBS += -L"./../../ZipTest-build-desktop/3rdParty/quazip" -lquazip

    QMAKE_POST_LINK += ./../../ZipTest/ZipTesterGui/deploy.sh

#copy dynlib
# NOTE: every QMAKE_POST_LINK will be fired in one line!! here are the tips / tricks if you want to run more than 1 post-link action: http://www.qtforum.org/article/14932/qmake-post-link-in-pro.html
    #QMAKE_POST_LINK += ./../../../../UsefulScriptsAndTools/mac/dynlib/deploy.sh
    #QMAKE_INFO_PLIST += ./MacResources/Info.plist
# TODO
#   DESTDIR = "./../../EasyAppsClientProject-build-desktop/EasyAppsClient"
}

win32 {
# build (debug / release) specific
    CONFIG( debug, debug|release ) {
# debug mode

        LIBS += -L"./../../ZipTest-build-desktop/debug" -lquazip

# destination / build dir
        DESTDIR = "./../debug"
    }

    CONFIG( release, debug|release ) {
# release mode

        LIBS += -L"./../../ZipTest-build-desktop/BIN/release" -lquazip

# destination / build dir
        DESTDIR = "./../release"
    }
}
