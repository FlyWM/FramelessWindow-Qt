#include "MuWinWindow.h"

#ifdef Q_OS_WIN32

#include <QLayout>
#include <QPainter>
#include <QIcon>
#include <QDebug>

#include <QtWinExtras/QtWin>
#include <dwmapi.h>

#include "MuWinTitlebar.h"

#pragma comment (lib, "user32.lib")

#ifndef GET_X_LPARAM
#define GET_X_LPARAM(lParam)    ((int)(short)LOWORD(lParam))
#endif
#ifndef GET_Y_LPARAM
#define GET_Y_LPARAM(lParam)    ((int)(short)HIWORD(lParam))
#endif

MuWinWindow::MuWinWindow(QWidget *parent) :
    QWidget(parent),
    clientWidget_(new QWidget(this))
{
    setWindowFlags(Qt::FramelessWindowHint);
    setMinimumSize(800, 600);

    HWND hwnd = reinterpret_cast<HWND>(this->winId());
    DWORD style = GetWindowLong(hwnd, GWL_STYLE);
    SetWindowLongPtr(hwnd, GWL_STYLE, style | WS_MAXIMIZEBOX | WS_THICKFRAME | WS_CAPTION);

    bool enabled = QtWin::isCompositionEnabled();
    if (enabled) {
        HWND hwnd = (HWND)this->winId();
        DWORD style = ::GetWindowLong(hwnd, GWL_STYLE);
        ::SetWindowLong(hwnd, GWL_STYLE, style | WS_THICKFRAME | WS_CAPTION | WS_BORDER);
        QtWin::extendFrameIntoClientArea(this, 1, 1, 1, 1);
    }

    // 其实是设置的标题栏的颜色
    setStyleSheet("background-color: #52baff");
    clientWidget_->setStyleSheet("background-color: #FFFFFF");

    MuWinTitlebar *titleBar = new MuWinTitlebar(this);
    titleBar->setFixedHeight(50);

    mainLayout_ = new QVBoxLayout(this);
    mainLayout_->addWidget(titleBar);
    mainLayout_->addWidget(clientWidget_);
    mainLayout_->setContentsMargins(0, 0, 0, 0);

    installEventFilter(titleBar);

    setWindowIcon(":/images/winwindow/1.jpg");
    setWindowTitle("WinWindow");

    connect(titleBar, &MuWinTitlebar::ShowMinimized, this, &MuWinWindow::showMinimized);
    connect(titleBar, &MuWinTitlebar::ShowMaximized, this, &MuWinWindow::showMaximized);
    connect(titleBar, &MuWinTitlebar::ShowRestoreSize, this, &MuWinWindow::showNormal);
    connect(titleBar, &MuWinTitlebar::Close, this, &MuWinWindow::close);
}

MuWinWindow::~MuWinWindow()
{
}

///
/// \brief MuWinWindow::paintEvent 通过paintEvent绘制图标和标题，如果用MuTitleBar来显示的图标和标题的话,
///                                当鼠标点击图标和标题时无法移动窗体
/// \param e
///
void MuWinWindow::paintEvent(QPaintEvent *e)
{
    QPainter p(this);

    // 绘制窗口图标
    QRect imgTarget(10, 10, 30, 30);
    QImage img(iconFileName_);
    p.drawImage(imgTarget, img.scaled(30, 30, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    // 绘制标题
    QFont font;
    font.setPixelSize(14);
    QFontMetrics fm(font);
    QRect titleTarget(45, 10, fm.width(title_), 30);

    p.setFont(font);
    p.setPen(Qt::white);
    p.drawText(titleTarget, title_, QTextOption(Qt::AlignCenter));

    QWidget::paintEvent(e);
}

QString MuWinWindow::iconFileName() const
{
    return iconFileName_;
}

void MuWinWindow::setWindowIcon(const QString &fileName)
{
    iconFileName_ = fileName;
    this->QWidget::setWindowIcon(QIcon(fileName));
}

void MuWinWindow::setWindowTitle(const QString &title)
{
    title_ = title;
    this->QWidget::setWindowTitle(title);
}

bool MuWinWindow::nativeEvent(const QByteArray &eventType,
                              void *message,
                              long *result)
{

#ifdef Q_OS_WIN
    if (eventType != "windows_generic_MSG")
        return false;

    MSG* msg = static_cast<MSG*>(message);

    QWidget* widget = QWidget::find(reinterpret_cast<WId>(msg->hwnd));
    if (!widget)
        return false;

    switch (msg->message) {
    case WM_NCCALCSIZE: {
        *result = 0;
        return true;
    }

    case WM_NCHITTEST: {
        int x = GET_X_LPARAM(msg->lParam);
        int y = GET_Y_LPARAM(msg->lParam);

        QPoint pt = mapFromGlobal(QPoint(x, y));
        *result = calculateBorder(pt);
        if (*result == HTCLIENT) {
            QWidget* tempWidget = this->childAt(pt.x(), pt.y());
            if (tempWidget == NULL) {
                *result = HTCAPTION;
            }
        }
        return true;
    }

    case WM_GETMINMAXINFO: {
        if (::IsZoomed(msg->hwnd)) {
            isMaximized_ = true;
            RECT frame = { 0, 0, 0, 0 };
            AdjustWindowRectEx(&frame, WS_OVERLAPPEDWINDOW, FALSE, 0);
            frame.left = abs(frame.left);
            frame.top = abs(frame.bottom);
            widget->setContentsMargins(frame.left, frame.top, frame.right, frame.bottom);
        }
        else {
            widget->setContentsMargins(0, 0, 0, 0);
            isMaximized_ = false;
        }

        *result = ::DefWindowProc(msg->hwnd, msg->message, msg->wParam, msg->lParam);
        return true;
    }
    break;

    default:
        break;
    }

#endif

    return QWidget::nativeEvent(eventType, message, result);
}

LRESULT MuWinWindow::calculateBorder(const QPoint &pt)
{
    if (::IsZoomed((HWND)this->winId())) {
        return HTCLIENT;
    }
    int borderSize = 4;
    int cx = this->size().width();
    int cy = this->size().height();

    QRect rectTopLeft(0, 0, borderSize, borderSize);
    if (rectTopLeft.contains(pt)) {
        return HTTOPLEFT;
    }

    QRect rectLeft(0, borderSize, borderSize, cy - borderSize * 2);
    if (rectLeft.contains(pt)) {
        return HTLEFT;
    }

    QRect rectTopRight(cx - borderSize, 0, borderSize, borderSize);
    if (rectTopRight.contains(pt)) {
        return HTTOPRIGHT;
    }

    QRect rectRight(cx - borderSize, borderSize, borderSize, cy - borderSize * 2);
    if (rectRight.contains(pt)) {
        return HTRIGHT;
    }

    QRect rectTop(borderSize, 0, cx - borderSize * 2, borderSize);
    if (rectTop.contains(pt)) {
        return HTTOP;
    }

    QRect rectBottomLeft(0, cy - borderSize, borderSize, borderSize);
    if (rectBottomLeft.contains(pt)) {
        return HTBOTTOMLEFT;
    }

    QRect rectBottomRight(cx - borderSize, cy - borderSize, borderSize, borderSize);
    if (rectBottomRight.contains(pt)) {
        return HTBOTTOMRIGHT;
    }

    QRect rectBottom(borderSize, cy - borderSize, cx - borderSize * 2, borderSize);
    if (rectBottom.contains(pt)) {
        return HTBOTTOM;
    }

    return HTCLIENT;
}

#endif
