#-------------------------------------------------
#
# Project created by QtCreator 2014-06-30T20:40:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -std=c++17

target.path = /home/yale/Dev/PointcloudMatch/bin
TARGET = PointcloudMatch
INSTALLS += target
TEMPLATE = app


SOURCES += source/main.cc \
    source/openglwindow.cc \
    source/matchviewer.cc \
    source/camera.cc \
    source/cameracontroller.cc

HEADERS  += \
    include/noncopyable.h \
    include/openglwindow.h \
    include/matchviewer.h \
    include/camera.h \
    include/angle.h \
    include/point.h \
    include/cameracontroller.h

RESOURCES += \
    src.qrc
