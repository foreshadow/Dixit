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
    tcpsocket.cpp \
    logindialog.cpp \
    chatform.cpp \
    player.cpp \
    handcards.cpp \
    serverdata.cpp \
    clientdata.cpp \
    graphicsbutton.cpp

HEADERS  += mainwindow.h \
    card.h \
    deck.h \
    tcpsocket.h \
    logindialog.h \
    chatform.h \
    player.h \
    handcards.h \
    serverdata.h \
    clientdata.h \
    graphicsbutton.h

FORMS    += mainwindow.ui \
    logindialog.ui \
    chatform.ui
