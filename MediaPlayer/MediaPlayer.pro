QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MediaPlayer
TEMPLATE = app

CONFIG += c++11
CONFIG += console

build_type =
CONFIG(debug, debug|release) {
    build_type = $$PWD/../bin/MediaPlayer/debug/
} else {
    build_type = $$PWD/../bin/MediaPlayer/release/
}

DESTDIR     = $${build_type}/out
OBJECTS_DIR = $${build_type}/obj
MOC_DIR     = $${build_type}/moc
RCC_DIR     = $${build_type}/rcc
UI_DIR      = $${build_type}/ui

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include(../Dependency/ffmpeg-n4.3-19/ffmpeg.pri)

SOURCES += \
    decoder.cpp \
    main.cpp \
    mainwindow.cpp \
    ffmpeg_util.cpp \
    openglrenderwidget.cpp  \
    stream_base.cpp \
    stream_normal.cpp    \
    stream.cpp  \
    decode_base.cpp 

HEADERS += \
    decoder.h \
    mainwindow.h    \
    ffmpeg_util.h   \
    openglrenderwidget.h    \
    stream_base.h   \
    stream_normal.h  \
    stream.h    \
    decode_base.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
