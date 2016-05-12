#-------------------------------------------------
#
# Project created by QtCreator 2016-03-05T19:29:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = series
VERSION = 1.2
TEMPLATE = app
CONFIG += warn_on

DESTDIR = bin
MOC_DIR = build/moc
RCC_DIR = build/rcc
UI_DIR = build/ui
OBJECTS_DIR = build/o

SOURCES += main.cpp\
        mainwindow.cpp \
    series.cpp \
    manager.cpp \
    insertdialog.cpp \
    modifydialog.cpp \
    tutorialdialog.cpp \
    aboutdialog.cpp 

win32: SOURCES += sqlite3.c

HEADERS  += mainwindow.h \
    series.h \
    manager.h \
    insertdialog.h \
    modifydialog.h \
    tutorialdialog.h \
    aboutdialog.h 

win32: HEADERS += sqlite3.h

# Fervor autoupdater
!include("fervor/Fervor.pri") {
    error("Unable to include Fervor autoupdater.")
}

FORMS    += mainwindow.ui \
    insertdialog.ui \
    modifydialog.ui \
    tutorialdialog.ui \
    aboutdialog.ui

RESOURCES += \
    resources.qrc

TRANSLATIONS = series_it.ts

macx: ICONS = imgs/series.icns

win32: RC_FILE = series.rc

unix: LIBS += -lsqlite3
