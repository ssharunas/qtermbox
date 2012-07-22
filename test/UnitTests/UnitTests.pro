#-------------------------------------------------
#
# Project created by QtCreator 2012-07-14T20:53:34
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_unitteststest
CONFIG   += console
CONFIG   += qtestlib
CONFIG   -= app_bundle

TEMPLATE = app

DEPENDPATH += . ../../src
INCLUDEPATH += . ../../src

include(../../src/qtermbox.pri)

SOURCES += tst_celltests.cpp\
tst_styletests.cpp \
tst_coretests.cpp \
tst_eventtests.cpp \
tst_cellFactorytests.cpp\
    main.cpp


DEFINES += SRCDIR=\\\"$$PWD/\\\"

LIBS += -L$$PWD/../../lib/ -ltermbox
INCLUDEPATH += $$PWD/../../
DEPENDPATH += $$PWD/../../
PRE_TARGETDEPS += $$PWD/../../lib/libtermbox.a

HEADERS += \
    AutoTest.h
