#include <QtGlobal>

#ifdef Q_OS_WIN32
#include <QLabel>
#include "MuShadowWindow.h"
#include "MuWinDWMAPI.h"

MuWinAeroShadowWindow::MuWinAeroShadowWindow(QWidget *parent)
    :QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
    setContentsMargins(0, 0, 0, 0);
    resize(800, 600);
    m_titleBar = new MuTitleBar(this, this, this, true);
    m_pClientWidget = new QWidget(this);

    m_pClientLayout = new QVBoxLayout(m_pClientWidget);

    QVBoxLayout *pRootLayout = new QVBoxLayout(this);
    pRootLayout->addWidget(m_titleBar);
    pRootLayout->addWidget(m_pClientWidget);

    m_pHelper = new MuFramelessHelper(this);
    m_pHelper->setShadowWidth(0);
    m_pHelper->activateOn(this, this);
    m_pHelper->setTitleHeight(m_titleBar->height());
    m_pHelper->setWidgetResizable(true);
    m_pHelper->setWidgetMovable(true);

    QLabel *label = new QLabel(this);
    label->setFixedSize(400, 300);
    label->setPixmap(QPixmap(":/images/logo.jpg"));

    BOOL enabled = FALSE;
    enabled = MuWinDwmapi::instance()->dwmIsCompositionEnabledsEnabled();
    if (enabled) {
        HWND hwnd = (HWND)this->winId();
        DWORD style = ::GetWindowLong(hwnd, GWL_STYLE);
        ::SetWindowLong(hwnd, GWL_STYLE, style | WS_CAPTION);
        //保留一个像素的边框宽度，否则系统不会绘制边框阴影
        //we better left 1 piexl width of border untouch, so OS can draw nice shadow around it
        const MARGINS shadow = { -1, -1, -1, -1 };
        MuWinDwmapi::instance()->dwmExtendFrameIntoClientArea(HWND(winId()), &shadow);
        qDebug() << MuWinDwmapi::instance()->enableBlurBehind(hwnd);
//        MuWinDwmapi::instance()->dwmIsCompositionEnabledsEnabled();

        qDebug() << MuWinDwmapi::instance()->dwmEnableTransition(hwnd, true);
    }
}

bool MuWinAeroShadowWindow::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    MSG* msg = (MSG *)message;
    switch (msg->message) {
    case WM_NCCALCSIZE: {
        // this kills the window frame and title bar we added with WS_THICKFRAME and WS_CAPTION
        *result = 0;
        return true;
    }
    default:
        return QWidget::nativeEvent(eventType, message, result);
    }
}
#endif
