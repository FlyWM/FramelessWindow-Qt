TEMPLATE = app

TARGET = libTest

include(../libFramelessWindow/libFramelessWindow.pri)

DESTDIR = $$PROJECT_BINDIR

unix:QMAKE_RPATHDIR += $$PROJECT_LIBDIR

QT += widgets

SOURCES += \
    main.cpp \
    MainWindow.cpp

HEADERS += \
    stylesheethelper.h \
    MainWindow.h

FORMS += \
    MainWindow.ui

