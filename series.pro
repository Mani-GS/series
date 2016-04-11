#-------------------------------------------------
#
# Project created by QtCreator 2016-03-05T19:29:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = series
TEMPLATE = app

INCLUDEPATH += /usr/lib/x86_64-linux-gnu
DEPENDPATH += /usr/lib/x86_64-linux-gnu

SOURCES += main.cpp\
        mainwindow.cpp \
    series.cpp \
    manager.cpp \
    insertdialog.cpp \
    modifydialog.cpp \
    tutorialdialog.cpp

HEADERS  += mainwindow.h \
    series.h \
    manager.h \
    insertdialog.h \
    modifydialog.h \
    tutorialdialog.h

FORMS    += mainwindow.ui \
    insertdialog.ui \
    modifydialog.ui \
    tutorialdialog.ui

RESOURCES += \
    resources.qrc

TRANSLATIONS = series_it.ts

ICON = imgs/app.ico

unix|win32: LIBS += -lsqlite3

