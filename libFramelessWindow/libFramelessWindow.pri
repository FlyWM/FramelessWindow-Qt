#---------------------------------------------
# 自定义无边框窗体、对话框和提示框
#
# libFramelessWindow.pri
# 工程文件
#
# FlyWM_
# GitHub: https://github.com/FlyWM
# CSDN: https://blog.csdn.net/a844651990
#
#---------------------------------------------

INCLUDEPATH += $$PWD

DEPENDPATH += $$PWD

TEMPLATE += fakelib

# qtLibraryTarget确保windows下debug模式生成的动态库可以自动加个d
# 用来区分 release 和 debug 模式下的库, 这里知识为了设置LIBFRAMELESSWINDOW_NAME的值，
# 所以 TEMPLATE -= fakelib，不然 qtLibraryTarget 获取不到值
LIBFRAMELESSWINDOW_NAME = $$qtLibraryTarget(FramelessWindow)

TEMPLATE -= fakelib

include(../common.pri)

# FramelessWindow-buildlib 标志用来区分是 libFramelessWindow调用
# 还是 libTest调用, 所以需要在 libFramelessWindow.pro中
# 设置 CONFIG += FramelessWindow-buidlib
FramelessWindow-buildlib{
# 不要加$$PWD
    HEADERS += \
        MuFramelessHelper.h \
        MuFramelessHelperPrivate.h \
        MuCursorPosCalculator.h \
        MuTitleBar.h \
        MuWidgetData.h \
        MuWinDWMAPI.h \
        MuShadowWidget.h \
        MuShadowWindow.h \
        MuCustomWindow.h \
        FramelessWindow_Global.h

    SOURCES += \
        MuFramelessHelper.cpp \
        MuWidgetData.cpp\
        MuCursorPosCalculator.cpp \
        MuTitleBar.cpp \
        MuWinDWMAPI.cpp \
        MuShadowWidget.cpp \
        MuCustomWindow.cpp

    RESOURCES += \
        images.qrc

    QT += widgets

    win32: {
        QT += winextras
        LIBS += -lDwmapi
    }
}else{
    LIBS += -L$$PROJECT_LIBDIR -l$$LIBFRAMELESSWINDOW_NAME

}





