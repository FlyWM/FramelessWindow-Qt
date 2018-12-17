#ifndef MUSHADOWWINDOW_H
#define MUSHADOWWINDOW_H

#include <QWidget>
#include <QVBoxLayout>
#include "MuShadowWidget.h"
#include "FramelessWindow_global.h"
#include "MuTitleBar.h"
#include "MuFramelessHelper.h"

class QPainter;
class QLineEdit;
class QLabel;

/*************************************
 * ----------------------------------
 * |shadowWindow                    |
 * |  ----------------------------  |
 * |  |ShadowWidget              |  |
 * |  |  ----------------------  |  |
 * |  |  |ShadowClientWidget  |  |  |
 * |  |  |                    |  |  |
 * |  |  |                    |  |  |
 * |  |  ----------------------  |  |
 * |  |                          |  |
 * |  ----------------------------  |
 * |                                |
 * ----------------------------------
 *************************************/
template <class Base>
class MuShadowWindow : public Base
{
public:
    explicit MuShadowWindow(bool canResize, QWidget *parent = nullptr)
        : Base(parent)
        , m_pShadowWidget(nullptr)
        , m_pClientWidget(nullptr)
    {
        Base *pT = this;
        pT->setAttribute(Qt::WA_TranslucentBackground);
        pT->setWindowFlags(Qt::FramelessWindowHint);
        pT->setContentsMargins(0, 0, 0, 0);

        QVBoxLayout *pWindowLayout = new QVBoxLayout(pT);
        pWindowLayout->setContentsMargins(0, 0, 0, 0);
        pWindowLayout->setSpacing(0);

        // 边框阴影
        int shadowSize = 20;
        m_pShadowWidget = new MuShadowWidget(shadowSize, canResize, this);
        m_pShadowWidget->setContentsMargins(shadowSize, shadowSize, shadowSize, shadowSize);
        m_pShadowWidget->setAutoFillBackground(true);
        pWindowLayout->addWidget(m_pShadowWidget);

        QVBoxLayout *pRootLayout = new QVBoxLayout(m_pShadowWidget);
        pRootLayout->setContentsMargins(0, 0, 0, 0);
        pRootLayout->setSpacing(0);

        // 窗口主要区域
        QWidget *pShadowClientWidget = new QWidget(m_pShadowWidget);
        pRootLayout->addWidget(pShadowClientWidget);
        pShadowClientWidget->setAutoFillBackground(true);
        QVBoxLayout *pShadowClientLayout = new QVBoxLayout(pShadowClientWidget);
        pShadowClientLayout->setContentsMargins(0, 0, 0, 0);
        pShadowClientLayout->setSpacing(0);

        MuTitleBar *pTitleBar = new MuTitleBar(pShadowClientWidget);
        pShadowClientLayout->addWidget(pTitleBar);

        m_pHelper = new MuFramelessHelper(this);
        m_pHelper->setTitleHeight(50);
        m_pHelper->setWidgetResizable(true);
        m_pHelper->setWidgetMovable(true);

//        setTitleHeight();

//        setWidgetMovalbe();
//        setWidgetResizable();
//        setRubberBandOnMove(false);
//        setRubberBandOnResize(false);
    }

private:
    MuShadowWidget *m_pShadowWidget;
    QWidget *m_pClientWidget;
    QLayout *m_pCLientLayout;
    MuFramelessHelper *m_pHelper;
};

typedef MuShadowWindow<QWidget> MuCustomWidgetWindow;
typedef MuShadowWindow<QDialog> MuCustonDialogWindow;

#endif // MUSHADOWWINDOW_H
