/**
 * 自定义无边框窗体、对话框和提示框
 *
 * FramelessWindow_Global.h
 *
 * FlyWM_
 * GitHub: https://github.com/FlyWM
 * CSDN: https://blog.csdn.net/a844651990
 *
 */

#ifndef FRAMELESSWINDOW_GLOBAL_H
#define FRAMELESSWINDOW_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(FRAMELESSWINDOW_LIBRARY)
#  define FRAMELESSWINDOWSHARED_EXPORT Q_DECL_EXPORT
#else
#  define FRAMELESSWINDOWSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // FRAMELESSWINDOW_GLOBAL_H
