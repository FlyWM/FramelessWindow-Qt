/**
 * 自定义无边框窗体、对话框和提示框
 *
 * MainWindow.h
 * 测试用例主要窗口
 *
 * FlyWM_
 * GitHub: https://github.com/FlyWM
 * CSDN: https://blog.csdn.net/a844651990
 *
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "MuCustomWindow.h"

namespace Ui {
class MainWindow;
class AeroCLientWidget;
}

class MainWindow : public MuCustomWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void onDialogBtnClicked();
    void onInformationBtnClicked();
    void onErrorBtnClicked();
    void onSuccessBtnClicked();
    void onWarningBtnClicked();
    void onWinWindow();

private:
#ifdef Q_OS_WIN32
    void initAreoWindow();
#endif

private:
    Ui::MainWindow *ui;
    Ui::AeroCLientWidget *aeroUI;
    MuCustomDialog *dialog;
#ifdef Q_OS_WIN32
    MuWinAeroShadowWindow *m_AeroWindow;
#endif
};

#endif // MAINWINDOW_H
