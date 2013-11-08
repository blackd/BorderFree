#-------------------------------------------------
#
# Project created by QtCreator 2013-11-07T12:54:41
#
#-------------------------------------------------

QT       += core

#QTPLUGIN += qpng

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BorderFree
TEMPLATE = app


SOURCES += main.cpp\
    borderfreeapp.cpp \
    qlineedithotkey.cpp \
    configdialog.cpp


HEADERS  += borderfreeapp.h \
    qlineedithotkey.h \
    configdialog.h

#FORMS    += mainwindow.ui

ICON += Crystal_Clear_action_view_remove.png

RESOURCES += resources.qrc


#CONFIG   -= windows
#CONFIG   += console static
CONFIG   += staticlibs

QMAKE_CXXFLAGS_RELEASE +=  -fdata-sections -ffunction-sections -Wl,--gc-sections -static -fvisibility=hidden -fvisibility-inlines-hidden
QMAKE_CXXFLAGS_RELEASE -= -lglu32 -lopengl32
QMAKE_LFLAGS_RELEASE += -static -Wl,--gc-sections -fwhole-program -Wl,--trace -Wl,--strip-discarded #-Wl,--strip-all -

FORMS += \
    configdialog.ui
