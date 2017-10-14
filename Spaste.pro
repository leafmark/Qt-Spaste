#-------------------------------------------------
#
# Project created by QtCreator 2017-09-16T21:59:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Spaste
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
        dialog_set.cpp \
        screenshot.cpp \
        paintarea.cpp

HEADERS += \
        dialog_set.h \
        screenshot.h \
        paintarea.h \
        main.h

win32 {
    HEADERS += \
        win32/getimage.h \
        win32/ShortCut.h

    SOURCES += \
        win32/getimage.cpp \
        win32/ShortCut.cpp
}
unix {
    QT += x11extras

    HEADERS += \
        unix/getimage.h \
        unix/ShortCut.h

    SOURCES += \
        unix/getimage.cpp \
        unix/ShortCut.cpp

    LIBS +=  -Wl,--rpath=./,--rpath=./lib/,--enable-new-dtags   #运行时链接库的路径
    LIBS +=  -lX11
 #   LIBS +=  -L./  -ld     #编译时动态链接库的路径：./  ，文件：libd.so
 #   LIBS += -z nodefaultlib #不搜索默认lib
}
FORMS += \
        dialog_set.ui
