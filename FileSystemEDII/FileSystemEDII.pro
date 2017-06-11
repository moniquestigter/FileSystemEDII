#-------------------------------------------------
#
# Project created by QtCreator 2017-06-08T22:44:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FileSystemEDII
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


SOURCES += main.cpp\
        mainwindow.cpp \
    api.cpp \
    archivo.cpp \
    bloquearchivo.cpp \
    discovirtual.cpp \
    fileentry.cpp \
    masterblock.cpp \
    bloquefolder.cpp \
    idxentry.cpp \
    lista.cpp \
    hashtable.cpp


HEADERS  += mainwindow.h \
    api.h \
    archivo.h \
    bloquearchivo.h \
    discovirtual.h \
    fileentry.h \
    masterblock.h \
    bloquefolder.h \
    idxentry.h \
    lista.h \
    hashtable.h


FORMS    += mainwindow.ui

RESOURCES += \
    imagenes.qrc

DISTFILES += \
    save-128.png \
    remove-icon-png-24.png \
    pencil_and_paper-512.png \
    jixzMaA5T.png \
    Cancel_Icon-128.png \
    901 (1).png \
    901 (1) - copia.png
