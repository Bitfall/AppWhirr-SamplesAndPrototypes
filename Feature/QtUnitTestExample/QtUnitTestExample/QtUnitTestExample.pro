#-------------------------------------------------
#
# Project created by QtCreator 2011-06-18T12:32:18
#
#-------------------------------------------------

QT       += core gui

TARGET = QtUnitTestExample
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    TestClasses/testclass1.cpp

HEADERS  += mainwindow.h \
    TestClasses/testclass1.h

FORMS    += mainwindow.ui


#
# unit test related

# with this additional config you can enable the unit-tests
#   Note: changing this requires Rebuild
CONFIG += qtestlib

qtestlib {
    DEFINES += UNIT_TEST_ENABLED

    SOURCES += UnitTests/testexample.cpp \
        UnitTests/testclass1unittest.cpp

    HEADERS += UnitTests/testexample.h \
        UnitTests/testclass1unittest.h
}

OTHER_FILES += \
    README.txt
