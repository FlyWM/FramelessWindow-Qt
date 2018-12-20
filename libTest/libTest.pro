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
    MainWindow.h \
    MainWindow.h \
    StyleSheetHelper.h

FORMS += \
    MainWindow.ui \
    AeroClientWidget.ui

RESOURCES += \
    qss.qrc \
    images.qrc

