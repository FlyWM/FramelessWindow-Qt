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
    HEADERS += cursorposcalculator.h \
        framelesshelper.h \
        framelesshelperprivate.h \
        framelesswindow.h \
        framelesswindow_global.h \
        stylesheethelper.h \
        widgetdata.h\
        titlebar.h

    SOURCES += \
        cursorposcalculator.cpp \
        framelesshelper.cpp \
        framelesswindow.cpp \
        widgetdata.cpp\
        titlebar.cpp

    RESOURCES += \
        images.qrc \
        style.qrc

    QT += widgets

}else{
    LIBS += -L$$PROJECT_LIBDIR -l$$LIBFRAMELESSWINDOW_NAME
}
