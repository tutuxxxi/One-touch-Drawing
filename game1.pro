#-------------------------------------------------
#
# Project created by QtCreator 2019-08-21T15:39:00
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = game1
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainscene.cpp \
    box.cpp \
    mybutton.cpp \
    choosescene.cpp \
    gamesence.cpp \
    mylabel.cpp

HEADERS += \
        mainscene.h \
    box.h \
    mybutton.h \
    choosescene.h \
    direction.h \
    gamesence.h \
    pic.h \
    mylabel.h

FORMS += \
        mainscene.ui

RESOURCES += \
    res.qrc

DISTFILES += \
    image/choose_backgroung.png \
    image/exit.png
