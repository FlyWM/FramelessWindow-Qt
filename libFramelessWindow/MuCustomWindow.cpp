#include "MuCustomWindow.h"

MuCustomWindow::MuCustomWindow(QWidget *parent)
    : MuShadowWindow<QWidget>(true, parent)
{
    this->setWindowTitle("Custom Window");
    this->setWindowIcon(QIcon(":/images/logo.jpg"));
}
