#-------------------------------------------------
#
# Project created by QtCreator 2020-06-09T19:35:24
#
#-------------------------------------------------

QT       += core gui network
QT += core-private
CONFIG += c++11
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MQTest
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



SOURCES += \
        main.cpp \
        mainwindow.cpp \
    QtMqtt/qmqttauthenticationproperties.cpp \
    QtMqtt/qmqttclient.cpp \
    QtMqtt/qmqttconnection.cpp \
    QtMqtt/qmqttconnectionproperties.cpp \
    QtMqtt/qmqttcontrolpacket.cpp \
    QtMqtt/qmqttmessage.cpp \
    QtMqtt/qmqttpublishproperties.cpp \
    QtMqtt/qmqttsubscription.cpp \
    QtMqtt/qmqttsubscriptionproperties.cpp \
    QtMqtt/qmqtttopicfilter.cpp \
    QtMqtt/qmqtttopicname.cpp \
    QtMqtt/qmqtttype.cpp

HEADERS += \
        mainwindow.h \
    QtMqtt/qmqttauthenticationproperties.h \
    QtMqtt/qmqttclient.h \
    QtMqtt/qmqttclient_p.h \
    QtMqtt/qmqttconnection_p.h \
    QtMqtt/qmqttconnectionproperties.h \
    QtMqtt/qmqttconnectionproperties_p.h \
    QtMqtt/qmqttcontrolpacket_p.h \
    QtMqtt/qmqttglobal.h \
    QtMqtt/qmqttmessage.h \
    QtMqtt/qmqttmessage_p.h \
    QtMqtt/qmqttpublishproperties.h \
    QtMqtt/qmqttpublishproperties_p.h \
    QtMqtt/qmqttsubscription.h \
    QtMqtt/qmqttsubscription_p.h \
    QtMqtt/qmqttsubscriptionproperties.h \
    QtMqtt/qmqtttopicfilter.h \
    QtMqtt/qmqtttopicname.h \
    QtMqtt/qmqtttype.h

FORMS += \
        mainwindow.ui

