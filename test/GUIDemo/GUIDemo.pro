#-------------------------------------------------
#
# Project created by QtCreator 2012-12-03T18:13:43
#
#-------------------------------------------------

QT       += core
QT       -= gui

TARGET = GUIDemo
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp

LIBS += -L$$PWD/../../bin/build-qtermbox-Desktop-Debug/ -lQTermbox
LIBS += -L$$PWD/../../lib/ -ltermbox

INCLUDEPATH += $$PWD/../../src
INCLUDEPATH += /usr/local/includes/qtermbox
DEPENDPATH += $$PWD/../../bin/Qt_4_8_2_Release
PRE_TARGETDEPS += $$PWD/../../lib/libtermbox.a
