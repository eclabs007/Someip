#-------------------------------------------------
#
# Project created by QtCreator 2018-08-27T06:57:59
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VehicleSimulator
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    communication.cpp

HEADERS  += mainwindow.h \
    communication.h

FORMS    += mainwindow.ui

DISTFILES += \
    nature_1.jpg

QMAKE_CXXFLAGS += -std=c++0x -pthread
LIBS += -pthread
LIBS +=  -lvsomeip  -lboost_system -lboost_thread -lboost_log -lboost_filesystem
#INCLUDEPATH += /home/vagrant/QT/inc/interface
#DEPENDPATH += /home/vagrant/QT/libv

QMAKE_LFLAGS +=  -lvsomeip
