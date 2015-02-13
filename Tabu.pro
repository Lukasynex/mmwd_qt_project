#-------------------------------------------------
#
# Project created by QtCreator 2015-01-14T08:32:24
#
#-------------------------------------------------

QT       += core gui
QT += printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Tabu
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    qcustomplot.cpp \
    Algorytm.cpp \
    Dane.cpp \
    TabuList.cpp

HEADERS  += widget.h \
    qcustomplot.h \
    Algorytm.h \
    Dane.h \
    Punkt.h \
    TabuList.h

FORMS    += widget.ui
