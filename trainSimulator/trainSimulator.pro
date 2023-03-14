#-------------------------------------------------
#
# Project created by QtCreator 2023-03-11T13:34:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = trainSimulator
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
        mainwindow.cpp \
    trackend.cpp \
    train.cpp \
    trainlocation.cpp \
    simplecontrolmodel.cpp \
    simplecontrolmodelwithbraking.cpp \
    tests/traintest.cpp \
    tests/testutils.cpp \
    lineartrack.cpp \
    tests/testutils.cpp \
    tests/traintest.cpp \
    lineartrack.cpp \
    main.cpp \
    mainwindow.cpp \
    simplecontrolmodel.cpp \
    simplecontrolmodelwithbraking.cpp \
    trackend.cpp \
    train.cpp \
    trainlocation.cpp \
    track_components/junctiontrack.cpp

HEADERS += \
        mainwindow.h \
    trackend.h \
    train.h \
    trainlocation.h \
    traincontrolmodel.h \
    simplecontrolmodel.h \
    simplecontrolmodelwithbraking.h \
    tests/traintest.h \
    itracksegment.h \
    lineartrack.h \
    tests/traintest.h \
    itracksegment.h \
    lineartrack.h \
    mainwindow.h \
    simplecontrolmodel.h \
    simplecontrolmodelwithbraking.h \
    trackend.h \
    train.h \
    traincontrolmodel.h \
    trainlocation.h \
    track_components/junctiontrack.h
