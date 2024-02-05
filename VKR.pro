#-------------------------------------------------
#
# Project created by QtCreator 2023-05-09T14:12:57
#
#-------------------------------------------------

QT       += core gui sql axcontainer printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VKR
TEMPLATE = app
VERSION = 1.0.0.1
QMAKE_TARGET_COPYRIGHT = Danila Akhaimov
QMAKE_TARGET_PRODUCT = Modul SPO

SOURCES += main.cpp\
        mainwindow.cpp \
    methods.cpp \
    settings.cpp \
    res.cpp \
    equip.cpp \
    gosts.cpp \
    norms.cpp \
    archive.cpp \
    about.cpp \
    qcustomplot.cpp \
    graphics.cpp \
    etc.cpp \
    norms17.cpp \
    norms19.cpp

HEADERS  += mainwindow.h \
    methods.h \
    settings.h \
    res.h \
    equip.h \
    gosts.h \
    norms.h \
    archive.h \
    about.h \
    qcustomplot.h \
    graphics.h \
    etc.h \
    norms17.h \
    norms19.h

FORMS    += mainwindow.ui \
    methods.ui \
    settings.ui \
    res.ui \
    equip.ui \
    gosts.ui \
    norms.ui \
    archive.ui \
    about.ui \
    graphics.ui \
    etc.ui \
    norms17.ui \
    norms19.ui

RC_ICONS = wifi.ico
#RC_FILE = icoFile.rc

RESOURCES += \
    resources.qrc

