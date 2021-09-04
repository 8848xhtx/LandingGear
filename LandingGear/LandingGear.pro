#-------------------------------------------------
#
# Project created by QtCreator 2021-03-27T17:39:49
#
#-------------------------------------------------

QT       += core gui quick quickwidgets network
QT += 3dcore 3drender 3dinput 3dextras


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LandingGear
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        analogswitch.cpp \
        controller.cpp \
        electricvalve.cpp \
        gear.cpp \
        hydraulicsystem.cpp \
        landinggearclock.cpp \
        landinggeardoor.cpp \
        main.cpp \
        signallight.cpp \
        swsystem.cpp \
        widget.cpp

HEADERS += \
        LandingGearContext.h \
        MachineVariables.h \
        analogswitch.h \
        controller.h \
        electricvalve.h \
        gear.h \
        hydraulicsystem.h \
        landinggearclock.h \
        landinggeardoor.h \
        signallight.h \
        swsystem.h \
        widget.h

FORMS += \
        widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    LandingGearQml.qml \
    LandingGearUI.qml \
    LandingGearUIForm.ui.qml

RESOURCES += \
    sources.qrc
