#ifndef MUSHADOWWINDOW_H
#define MUSHADOWWINDOW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QIcon>
#include <QDebug>
#include <QPushButton>
#include <QDialog>
#include <QMessageBox>
#include "MuShadowWidget.h"
#include "FramelessWindow_Global.h"
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
 * |  |  | ------------------ |  |  |
 * |  |  | |TitleBar        | |  |  |
 * |  |  | ------------------ |  |  |
 * |  |  | ------------------ |  |  |
 * |  |  | |ClientWidget    | |  |  |
 * |  |  | |                | |  |  |
 * |  |  | ------------------ |  |  |
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
    explicit MuShadowWindow(bool canResize, int shadowSize, QWidget *parent = nullptr)
        : Base(parent)
        , m_shadowSize(shadowSize)
        , m_pShadowWidget(nullptr)
        , m_pClientWidget(nullptr)
    {
        Base *pT = this;
        pT->setAttribute(Qt::WA_TranslucentBackground, true);
        pT->setWindowFlags(Qt::FramelessWindowHint);
        pT->setContentsMargins(0, 0, 0, 0);

        QVBoxLayout *pWindowLayout = new QVBoxLayout(pT);
        pWindowLayout->setContentsMargins(0, 0, 0, 0);
        pWindowLayout->setSpacing(0);

        // 边框阴影widget
        m_pShadowWidget = new MuShadowWidget(m_shadowSize, canResize, this);
        m_pShadowWidget->setContentsMargins(m_shadowSize, m_shadowSize, m_shadowSize, m_shadowSize);
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

        m_titleBar =  new MuTitleBar(pShadowClientWidget, this, m_pShadowWidget, canResize);
        this->installEventFilter(m_titleBar);
        pShadowClientLayout->addWidget(m_titleBar);

        m_pClientWidget = new QWidget(pShadowClientWidget);
        pShadowClientLayout->addWidget(m_pClientWidget);

        m_pClientLayout = new QVBoxLayout;
        m_pClientWidget->setLayout(m_pClientLayout);

        m_pHelper = new MuFramelessHelper(this);
        m_pHelper->setShadowWidth(m_shadowSize);
        m_pHelper->activateOn(this, m_pShadowWidget);
        m_pHelper->setTitleHeight(50);
        m_pHelper->setWidgetResizable(true);
        m_pHelper->setWidgetMovable(true);
    }

public:
    QWidget* rootWidget() const { return m_pShadowWidget; }
    QWidget *clientWidget() const { return m_pClientWidget; }
    QLayout* clientLayout() const { return m_pClientLayout; }
    MuTitleBar *titleBar() const { return m_titleBar; }
    void setResizable(bool resizable) { m_pHelper->setWidgetResizable(resizable); }
    void setMovable(bool movable) {m_pHelper->setWidgetMovable(movable); }

protected:
    virtual void resizeEvent(QResizeEvent *e) {
        Q_UNUSED(e)
        if (Qt::WindowMaximized == this->windowState()) {
            m_pHelper->setShadowWidth(0);
        } else {
            m_pHelper->setShadowWidth(m_shadowSize);
        }
    }

private:
    int m_shadowSize;
    MuShadowWidget *m_pShadowWidget;
    QWidget *m_pClientWidget;
    QVBoxLayout *m_pClientLayout;
    MuFramelessHelper *m_pHelper;
    MuTitleBar *m_titleBar;
};

typedef MuShadowWindow<QWidget> MuCustomWindowWidget;
typedef MuShadowWindow<QDialog> MuCustomDialogWidget;
typedef MuShadowWindow<QMessageBox> MuCustomMessageBoxWidget;

#ifdef Q_OS_WIN32
class FRAMELESSWINDOWSHARED_EXPORT MuWinAeroShadowWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MuWinAeroShadowWindow(QWidget *parent = nullptr);

    QWidget *clientWidget() const { return m_pClientWidget; }
    QVBoxLayout *clientLayout() const { return m_pClientLayout; }

protected:
    virtual bool nativeEvent(const QByteArray &eventType, void *message, long *result);

private:
    MuTitleBar *m_titleBar;
    QWidget *m_pClientWidget;
    QVBoxLayout *m_pClientLayout;
    MuFramelessHelper *m_pHelper;
};
#endif

#endif // MUSHADOWWINDOW_H
