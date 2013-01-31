#-------------------------------------------------
#
# Project created by QtCreator 2011-05-20T15:08:58
#
#-------------------------------------------------

QT       += core gui
QT += svg

TARGET = IntelligentSeparatedMultifunctionButton
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Common/Widgets/IntelligentSeparatedMultifunctionalButtonWidget/intelligentseparatedmultifunctionalbuttonwidget.cpp \
    Common/Widgets/IntelligentSeparatedMultifunctionalButtonWidget/intelligentseparatedmultifunctionalbuttonoptionitemwidget.cpp \
    Common/Widgets/IntelligentSeparatedMultifunctionalButtonWidget/intelligentseparatedmultifunctionalbuttonoptionitemmodel.cpp \
    Common/Widgets/SimpleImageWidget/simpleimagepresenterwidget.cpp \
    Common/SvgToPixmapRenderer/svgtopixmaprenderer.cpp \
    Common/ImageToPixmapConverter/imagetopixmapconverter.cpp \
    Common/BorderImageRenderer/borderimagerenderer.cpp \
    Common/Widgets/BaseWidgets/AnimatedTwoFixedSizeWidgetBase/animatedtwofixedsizewidgetbase.cpp \
    Common/Helpers/SizeHelper/sizehelper.cpp \
    Common/Helpers/TextSizeHelper/textsizehelper.cpp

HEADERS  += mainwindow.h \
    Common/Widgets/IntelligentSeparatedMultifunctionalButtonWidget/intelligentseparatedmultifunctionalbuttonwidget.h \
    Common/Widgets/IntelligentSeparatedMultifunctionalButtonWidget/intelligentseparatedmultifunctionalbuttonoptionitemwidget.h \
    Common/Widgets/IntelligentSeparatedMultifunctionalButtonWidget/intelligentseparatedmultifunctionalbuttonoptionitemmodel.h \
    Common/Widgets/SimpleImageWidget/simpleimagepresenterwidget.h \
    Common/SvgToPixmapRenderer/svgtopixmaprenderer.h \
    Common/ImageToPixmapConverter/imagetopixmapconverter.h \
    Common/BorderImageRenderer/borderimagerenderer.h \
    Common/Widgets/BaseWidgets/AnimatedTwoFixedSizeWidgetBase/animatedtwofixedsizewidgetbase.h \
    Common/Helpers/SizeHelper/sizehelper.h \
    Common/Helpers/TextSizeHelper/textsizehelper.h

FORMS    += mainwindow.ui

RESOURCES += \
    testResources.qrc
