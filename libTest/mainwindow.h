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

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
