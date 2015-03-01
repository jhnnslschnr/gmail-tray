#-------------------------------------------------
#
# Project created by QtCreator 2015-02-26T16:07:33
#
#-------------------------------------------------

QT       += core gui network xmlpatterns

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gmail-tray
TEMPLATE = app


SOURCES += main.cpp\
        configdialog.cpp \
    trayicon.cpp \
    checker.cpp \
    entryevaluator.cpp \
    entry.cpp \
    trayiconnotificator.cpp \
    watcher.cpp \
    control.cpp

HEADERS  += configdialog.h \
    trayicon.h \
    checker.h \
    entryevaluator.h \
    entry.h \
    trayiconnotificator.h \
    watcher.h \
    control.h

FORMS    += configdialog.ui

RESOURCES += \
    icons.qrc
