#---------------------------------------------
# 自定义无边框窗体、对话框和提示框
#
# libTest.pri
# 工程文件 测试程序
#
# FlyWM_
# GitHub: https://github.com/FlyWM
# CSDN: https://blog.csdn.net/a844651990
#
#---------------------------------------------

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

