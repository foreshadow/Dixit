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

INCLUDEPATH += \
    src/core \
    src/graphics \
    src/network \
    src/ui

SOURCES += \
    src/main.cpp \
    src/core/card.cpp \
    src/core/deck.cpp \
    src/core/handcards.cpp \
    src/core/player.cpp \
    src/graphics/graphicsbutton.cpp \
    src/graphics/graphicsheadline.cpp \
    src/network/clientdata.cpp \
    src/network/serverdata.cpp \
    src/network/tcpsocket.cpp \
    src/ui/chatform.cpp \
    src/ui/logindialog.cpp \
    src/ui/mainwindow.cpp \
    src/core/centerarea.cpp \
    src/core/dixitgame.cpp \
    src/graphics/graphicscountdown.cpp

HEADERS  += \
    src/core/card.h \
    src/core/deck.h \
    src/core/handcards.h \
    src/core/player.h \
    src/graphics/graphicsbutton.h \
    src/graphics/graphicsheadline.h \
    src/network/clientdata.h \
    src/network/serverdata.h \
    src/network/tcpsocket.h \
    src/ui/chatform.h \
    src/ui/logindialog.h \
    src/ui/mainwindow.h \
    src/core/centerarea.h \
    src/core/dixitgame.h \
    src/graphics/graphicscountdown.h

FORMS    += \
    src/ui/chatform.ui \
    src/ui/logindialog.ui \
    src/ui/mainwindow.ui
