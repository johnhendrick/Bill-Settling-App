#-------------------------------------------------
#
# Project created by QtCreator 2015-10-13T19:52:21
#
#-------------------------------------------------

QT       += core gui
CONFIG += c++11
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BillingApp
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    persondialog.cpp \
    person.cpp

HEADERS  += mainwindow.h \
    persondialog.h \
    person.h

FORMS    += mainwindow.ui \
    persondialog.ui
