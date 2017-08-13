#-------------------------------------------------
#
# Project created by QtCreator 2017-08-13T11:08:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ImagePlatform
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

INCLUDEPATH += D:\opencv3.1\opencv\build\include
INCLUDEPATH += D:\opencv3.1\opencv\build\include\opencv
INCLUDEPATH += D:\opencv3.1\opencv\build\include\opencv2

#LIBS +=D:\opencv3.1\opencv\build\x64\vc12\lib\opencv_world310.lib
LIBS +=D:\opencv3.1\opencv\build\x64\vc12\lib\opencv_world310d.lib
