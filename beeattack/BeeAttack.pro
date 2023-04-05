#-------------------------------------------------
#
# Project created by QtCreator
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QBeeAttack
TEMPLATE = app


SOURCES += main.cpp\
    Hfl.cpp \
    QSQLDbHelper.cpp \
    mypoi.cpp \
        widget.cpp \
    customscene.cpp \
           ball.cpp \
        tbee.cpp

HEADERS  += widget.h \
    Hfl.h \
    QSQLDbHelper.h \
    customscene.h \
    ball.h \
    mypoi.h \
    tbee.h

FORMS    += widget.ui

RESOURCES     = tooltips.qrc
