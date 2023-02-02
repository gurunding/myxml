QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    help/aboutmyxml.cpp \
    highlight/highlighter.cpp \
    linenumber/linenumber.cpp \
    mainwindow/main.cpp \
    mainwindow/mainwindow.cpp \
    options/options.cpp

HEADERS += \
    help/aboutmyxml.h \
    highlight/highlighter.h \
    linenumber/linenumber.h \
    mainwindow/mainwindow.h \
    options/options.h

FORMS += \
    help/aboutmyxml.ui \
    mainwindow/mainwindow.ui \
    options/options.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DESTDIR += $$PWD/bin

RESOURCES += \
    resource.qrc

RC_FILE += exeicon.rc
