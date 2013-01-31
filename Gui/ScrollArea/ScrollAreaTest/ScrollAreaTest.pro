#-------------------------------------------------
#
# Project created by QtCreator 2011-11-01T20:15:47
#
#-------------------------------------------------

QT       += core gui

TARGET = ScrollAreaTest
TEMPLATE = app

CONFIG += precompiled_header
PRECOMPILED_HEADER = Developer/macros.h

DEFINES += DEBUG


SOURCES += main.cpp\
        mainwindow.cpp \
    Common/Widgets/delegatingscrollarea.cpp \
    Common/Layouts/flowlayout.cpp \
    Common/Widgets/delegatebasedwidget.cpp \
    Common/Widgets/samesizehorizontalflowlayoutbasedscrollarea.cpp \
    Common/Widgets/multisectionsamesizehorizontalflowlayoutbasedscrollarea.cpp \
    Common/mousegrabscrolldelegate.cpp \
    Common/Layouts/samesizelayoutbase.cpp \
    Common/Layouts/samesizehorizontalflowlayout.cpp

HEADERS  += mainwindow.h \
    Common/Widgets/delegatingscrollarea.h \
    Common/Layouts/flowlayout.h \
    Developer/macros.h \
    Common/Widgets/delegatebasedwidget.h \
    Common/Widgets/samesizehorizontalflowlayoutbasedscrollarea.h \
    Common/Widgets/multisectionsamesizehorizontalflowlayoutbasedscrollarea.h \
    Common/Widgets/sectionbasedhorizontalflowlayoutpresenterdelegate.h \
    Common/mousegrabscrolldelegate.h \
    Common/Layouts/samesizelayoutbase.h \
    Common/Layouts/samesizehorizontalflowlayout.h














































