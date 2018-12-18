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
#include <QPushButton>
#include "MainWindow.h"
#include "stylesheethelper.h"
#include "MuCustomWindow.h"
#include "MuShadowWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    StyleSheetHelper::setStyle(":/style_black.qss");

    MainWindow w;
    w.show();

    MuCustomDialog dialog;
    dialog.setModal(true);
    dialog.setWindowTitle("dialog");
    dialog.show();

    MuCustomMessageBox::showInformation(nullptr, "Title", "showInformation !");
    MuCustomMessageBox::showError(nullptr, "Title", "showError !");
    MuCustomMessageBox::showSuccess(nullptr, "Title", "showSuccess !");
    MuCustomMessageBox::showCritical(nullptr, "Title", "showCritical !");
    MuCustomMessageBox::showQuestion(nullptr, "Title", "showQuestion!");
    MuCustomMessageBox::showWarning(nullptr, "Title", "showWarning !");

    return a.exec();
}
