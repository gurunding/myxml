QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

DESTDIR += $$PWD/bin

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    mainwindow/main.cpp \
    mainwindow/mainwindow.cpp \
    options/options.cpp \
    shared/xmlsyntaxhighlighter.cpp

HEADERS += \
    mainwindow/mainwindow.h \
    options/options.h \
    shared/xmlsyntaxhighlighter.h

FORMS += \
    mainwindow/mainwindow.ui \
    options/options.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

RC_FILE += exeicon.rc
