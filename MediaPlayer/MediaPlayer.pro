QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

build_type =
CONFIG(debug, debug|release) {
    build_type = debug
} else {
    build_type = release
}

DESTDIR     = $$build_type/bin/out
OBJECTS_DIR = $$build_type/bin/obj
MOC_DIR     = $$build_type/bin/moc
RCC_DIR     = $$build_type/bin/rcc
UI_DIR      = $$build_type/bin/ui

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include(../Dependency/ffmpeg-n4.3-19/ffmpeg.pri)

SOURCES += \
    decoder.cpp \
    main.cpp \
    mainwindow.cpp \
    openglrenderwidget.cpp

HEADERS += \
    decoder.h \
    mainwindow.h    \
    openglrenderwidget.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
