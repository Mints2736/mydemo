######################################################################
# Automatically generated by qmake (2.01a) sab 24. mar 11:48:26 2007
######################################################################

TEMPLATE = app
TARGET = press
DEPENDPATH += . quazip
INCLUDEPATH += . quazip

CONFIG += qt warn_of release console
QT -= gui

DESTDIR	+= ./

######################################################################
#    DEFINES
######################################################################
unix:DEFINES  +=
win32:DEFINES += WIN32

# Input
HEADERS += quazip/crypt.h \
           quazip/ioapi.h \
           quazip/quazip.h \
           quazip/quazipfile.h \
           quazip/quazipfileinfo.h \
           quazip/quazipnewinfo.h \
           quazip/unzip.h \
           quazip/zconf.h \
           quazip/zip.h \
           quazip/gojobzip.h \
           quazip/zlib.h
SOURCES += main.cpp \
           quazip/ioapi.c \
           quazip/quazip.cpp \
           quazip/quazipfile.cpp \
           quazip/quazipnewinfo.cpp \
           quazip/unzip.c \
           quazip/zip.c
