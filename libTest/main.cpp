/**
 * 自定义无边框窗体、对话框和提示框
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
#include <QPushButton>
#include "MainWindow.h"
#include "StyleSheetHelper.h"
#include "MuCustomWindow.h"
#include "MuShadowWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    StyleSheetHelper::setStyle(":/style.qss");

    MainWindow w;
    w.show();

    MuWinAeroShadowWindow w1;
    w1.show();

    return a.exec();
}
