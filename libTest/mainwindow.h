/**
 * 自定义无边框窗体、对话框和提示框并封装成库
 *
 * mainwindow.h
 * 测试窗体。
 *
 * FlyWM_
 * GitHub: https://github.com/FlyWM
 * CSDN: https://blog.csdn.net/a844651990
 *
 */


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <framelesswindow.h>

class MainWindow : public FramelessWindow
{
public:
    MainWindow(QWidget *parent = nullptr);
};

#endif // MAINWINDOW_H
