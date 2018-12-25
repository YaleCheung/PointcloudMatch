#-------------------------------------------------
#
# Project created by QtCreator 2014-06-30T20:40:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

target.path = /home/yale/Dev/PointcloudMatch/bin
TARGET = PointcloudMatch
INSTALLS += target
TEMPLATE = app


SOURCES += source/main.cc \
    source/openglwindow.cc \
    source/matchviewer.cpp

HEADERS  += \
    include/openglwindow.h \
    include/matchviewer.h

RESOURCES += \
    shader/vertshader.glsl \
    shader/fragshader.glsl
