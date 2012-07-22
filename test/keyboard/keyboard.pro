#-------------------------------------------------
#
# Project created by QtCreator 2012-07-22T11:06:55
#
#-------------------------------------------------

QT       += core
QT       -= gui

TARGET = keyboard
CONFIG   += console
CONFIG   -= app_bundle

INCLUDEPATH += /usr/local/includes/qtermbox
TEMPLATE = app

SOURCES += main.cpp \
    keyboard.cpp \
    key.cpp \
    keycontainer.cpp

LIBS += -lQTermbox
LIBS += -L$$PWD/../../lib/ -ltermbox

INCLUDEPATH += $$PWD/../../
DEPENDPATH += $$PWD/../../
PRE_TARGETDEPS += $$PWD/../../lib/libtermbox.a

HEADERS += \
    keyboard.h \
    key.h \
    keycontainer.h
