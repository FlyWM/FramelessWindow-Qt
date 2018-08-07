/**
 * 自定义无边框窗体、对话框和提示框并封装成库
 *
 * stylesheethelper.h
 * 加载qss文件。
 *
 * FlyWM_
 * GitHub: https://github.com/FlyWM
 * CSDN: https://blog.csdn.net/a844651990
 *
 */

#ifndef LSSTYLESHEETHELPER_H
#define LSSTYLESHEETHELPER_H

#include <QFile>
#include <QApplication>

class StyleSheetHelper
{
public:
    static void setStyle(const QString &qssFile)
    {
        QFile qss(qssFile);
        qss.open(QFile::ReadOnly);
        qApp->setStyleSheet(qss.readAll());
        qss.close();
    }
};

#endif // LSSTYLESHEETHELPER_H
