#---------------------------------------------
# 自定义无边框窗体、对话框和提示框
#
# libFramelessWindow.pro
# 工程文件
#
# FlyWM_
# GitHub: https://github.com/FlyWM
# CSDN: https://blog.csdn.net/a844651990
#
#---------------------------------------------

TEMPLATE = lib

CONFIG += FramelessWindow-buildlib

include(libFramelessWindow.pri)

TARGET = $$LIBFRAMELESSWINDOW_NAME

DESTDIR = $$PROJECT_LIBDIR

win32{
    DLLDESTDIR = $$PROJECT_BINDIR
    QMAKE_DISTCLEAN += $$PROJECT_BINDIR/$${LIBFRAMELESSWINDOW_NAME}.dll
}

CONFIG += debug_and_release build_all

# 宏定义
DEFINES += FRAMELESSWINDOW_LIBRARY HAVE_WINDOW_AERO





