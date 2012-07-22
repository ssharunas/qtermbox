#-------------------------------------------------
#
# Project created by QtCreator 2012-07-14T20:13:25
#
#-------------------------------------------------

QT       -= gui

TARGET = QTermbox
TEMPLATE = lib

DEFINES += QTERMBOX_LIBRARY

DEPENDPATH += .
INCLUDEPATH += .

include(qtermbox.pri)

VERSION = 0.5

target.path = /usr/local/lib
includes.files += $$HEADERS
includes.path = /usr/local/includes/qtermbox
INSTALLS += target
INSTALLS += includes

#LIBS += -L$$PWD/../lib/ -ltermbox
#INCLUDEPATH += $$PWD/../
#DEPENDPATH += $$PWD/../
#PRE_TARGETDEPS += $$PWD/../lib/libtermbox.a
