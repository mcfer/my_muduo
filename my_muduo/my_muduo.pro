TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    tcpserver.cpp \
    channel.cpp \
    acceptor.cpp \
    tcpconnection.cpp

HEADERS += \
    tcpserver.h \
    channel.h \
    define.h \
    head.h \
    ichannelcallback.h \
    iacceptorcallback.h \
    acceptor.h \
    tcpconnection.h

