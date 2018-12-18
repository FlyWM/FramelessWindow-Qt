#ifndef MUCUSTOMWINDOW_H
#define MUCUSTOMWINDOW_H


#include "MuShadowWindow.h"

class FRAMELESSWINDOWSHARED_EXPORT MuCustomWindow : public MuShadowWindow<QWidget>
{
public:
    explicit MuCustomWindow(QWidget *parent = nullptr);
};

#endif // MUCUSTOMWINDOW_H
