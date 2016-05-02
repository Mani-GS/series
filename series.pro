#-------------------------------------------------
#
# Project created by QtCreator 2016-03-05T19:29:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = series
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    series.cpp \
    manager.cpp \
    insertdialog.cpp \
    modifydialog.cpp \
    tutorialdialog.cpp \
    aboutdialog.cpp \
#    sqlite3.c			#only for Windows

HEADERS  += mainwindow.h \
    series.h \
    manager.h \
    insertdialog.h \
    modifydialog.h \
    tutorialdialog.h \
    aboutdialog.h \
#    sqlite3.h			#only for Windows

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
