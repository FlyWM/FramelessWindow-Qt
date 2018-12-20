#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "MuCustomWindow.h"

namespace Ui {
class MainWindow;
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
    void onAeroBtnClicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
