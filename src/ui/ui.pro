#-------------------------------------------------
#
# Project created by QtCreator 2017-08-23T12:34:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ui
TEMPLATE = app

INCLUDEPATH += /usr/local/include/opencv
INCLUDEPATH += /home/bob/dlib-19.4
LIBS += -L/usr/local/lib -lopencv_core -lopencv_highgui -ldlib


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
        CMainWindow.cpp \
    CDialogBox.cpp \
    CDrawingBoard.cpp \
    CRubberBand.cpp \
    ../vision/CObjectDatabase.cpp \
    ../logger/Logger.cpp \
    ../state_events/CEventBuffer.cpp \
    CObjectDetails.cpp \
    CObjectXmlParser.cpp \
    ../config/Constants.cpp \
    CHelper.cpp \
    ../vision/CVisionController.cpp \
    CToastMsg.cpp

HEADERS += \
        CMainWindow.h \
    CDialogBox.h \
    CDrawingBoard.h \
    CRubberBand.h \
    ../vision/CObjectDatabase.h \
    ../logger/Logger.h \
    ../state_events/CEventBuffer.h \
    CObjectDetails.h \
    CObjectXmlParser.h \
    ../config/Constants.h \
    CHelper.h \
    ../vision/CVisionController.h \
    CToastMsg.h

FORMS += \
        mainwindow.ui
