#-------------------------------------------------
#
# Project created by QtCreator 2020-09-04T11:08:40
#
#-------------------------------------------------

QT       += core gui serialport
QT       += printsupport
QT       += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qt_get_code
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qrencode/bitstream.c \
    qrencode/mask.c \
    qrencode/mmask.c \
    qrencode/mqrspec.c \
    qrencode/qrencode.c \
    qrencode/qrinput.c \
    qrencode/qrspec.c \
    qrencode/rscode.c \
    qrencode/split.c \
    ajb_common/queue.cpp \
    ajb_qrcode/code.cpp \
    ajb_uart/uart.cpp \
    ajb_net/ajb_socket.cpp

HEADERS  += mainwindow.h \
    qrencode/bitstream.h \
    qrencode/config.h \
    qrencode/mask.h \
    qrencode/mmask.h \
    qrencode/mqrspec.h \
    qrencode/qrencode.h \
    qrencode/qrencode_inner.h \
    qrencode/qrinput.h \
    qrencode/qrspec.h \
    qrencode/rscode.h \
    qrencode/split.h \
    ajb_common/ma_type.h \
    ajb_common/queue.h \
    ajb_qrcode/code.h \
    ajb_uart/uart.h \
    ajb_net/ajb_socket.h

FORMS    += mainwindow.ui

#如果出现无论是头文件还是源文件中都有#include <qdebug.h>，程序中qdebug()<<的使用方法都正确，却在输出窗口中无法看到输出的信息。
#1.在工程文件.pro的最后添加：CONFIG += console
#2.如果你的工程文件中又包含多个工程文件，那么你需要在那几个工程文件最后也添加CONFIG += console
#3.将工程文件编译过的文件清除：make clean，或者在QT ide中：构建-》清理项目xxx
#4.执行qmake，重新编译XXX项目
#6.在需要用的头文件或者源文件中#include
