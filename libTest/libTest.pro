TEMPLATE = app

TARGET = libTest

include(../libFramelessWindow/libFramelessWindow.pri)

DESTDIR = $$PROJECT_BINDIR

unix:QMAKE_RPATHDIR += $$PROJECT_LIBDIR

QT += widgets

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h \
    stylesheethelper.h

RESOURCES += \
    style.qrc

