#-------------------------------------------------
#
# Project created by QtCreator 2018-01-19T18:34:20
#
#-------------------------------------------------

QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PelvicOrgansExaminationProtocolForm
TEMPLATE = app
CONFIG += c++1z

LIBS+= E:\VIDEO\qt\5.9.4\mingw53_32\lib\libQt5WebKit.dll.a \
      E:\VIDEO\qt\5.9.4\mingw53_32\lib\libQt5WebKitWidgets.dll.a

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
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
    mainapplication.cpp \
    abstractmainwindow.cpp \
    abstractmainapplication.cpp \
    form.cpp \
    keyparser.cpp \
    abstractform.cpp \
    abstractfactoryparser.cpp \
    abstracmyactionpool.cpp

HEADERS += \
        mainwindow.h \
    mainapplication.h \
    asktype.h \
    abstractmainwindow.h \
    abstractmainapplication.h \
    form.h \
    keyparser.h \
    abstractform.h \
    abstractfactoryparser.h \
    abstracmyactionpool.h

FORMS += \
        mainwindow.ui
