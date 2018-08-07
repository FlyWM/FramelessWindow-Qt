/**
 * 自定义无边框窗体、对话框和提示框并封装成库
 *
 * main.cpp
 * 测试入口函数。
 *
 * FlyWM_
 * GitHub: https://github.com/FlyWM
 * CSDN: https://blog.csdn.net/a844651990
 *
 */

#include <QApplication>
#include "mainwindow.h"
#include "stylesheethelper.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    StyleSheetHelper::setStyle(":/style.qss");

    MainWindow w;
    w.show();

    return a.exec();
}
