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
    tests/traintest.cpp \
    tests/testutils.cpp \
    track_components/junctiontrack.cpp \
    track_components/lineartrack.cpp \
    physics/simplecontrolmodel.cpp \
    physics/simplecontrolmodelwithbraking.cpp \
    train/train.cpp \
    train/trainlocation.cpp \
    track_components/junction.cpp \
    track_components/trackgeometry.cpp \
    track_system/tracksystem.cpp \
    track_system/signal.cpp \
    tests/tracksystemtest.cpp \
    track_components/tracksensor.cpp \
    track_components/basictracksegment.cpp \
    track_system/collisionchecker.cpp \
    path_planning/trackpathtable.cpp

HEADERS += \
        mainwindow.h \
    tests/traintest.h \
    track_components/junctiontrack.h \
    track_components/itracksegment.h \
    track_components/lineartrack.h \
    physics/simplecontrolmodel.h \
    physics/simplecontrolmodelwithbraking.h \
    physics/traincontrolmodel.h \
    train/train.h \
    train/trainlocation.h \
    track_components/junction.h \
    track_components/trackgeometry.h \
    track_system/tracksystem.h \
    track_system/signal.h \
    track_system/isignal.h \
    tests/tracksystemtest.h \
    tests/testutils.h \
    track_components/tracksensor.h \
    train/ivehicle.h \
    track_components/basictracksegment.h \
    track_system/collisionchecker.h \
    path_planning/trackpathtable.h
