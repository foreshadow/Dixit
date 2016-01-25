#-------------------------------------------------
#
# Project created by QtCreator 2016-01-25T13:06:45
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = Dixit
TEMPLATE = app


SOURCES += main.cpp\
    mainwindow.cpp \
    card.cpp \
    deck.cpp \
    tcpserver.cpp \
    tcpsocket.cpp

HEADERS  += mainwindow.h \
    card.h \
    deck.h \
    tcpserver.h \
    tcpsocket.h

FORMS    += mainwindow.ui
