/**
 * 自定义无边框窗体、对话框和提示框
 *
 * MuWidgetData.cpp
 * 处理鼠标事件。
 *
 * FlyWM_
 * GitHub: https://github.com/FlyWM
 * CSDN: https://blog.csdn.net/a844651990
 *
 */

#include <QEvent>
#include <QMouseEvent>
#include <QRubberBand>
#include <QPoint>
#include <QDesktopWidget>
#include <QDebug>
#include "MuWidgetData.h"
#include "MuFramelessHelperPrivate.h"
#include "MuCursorPosCalculator.h"
#include "MuShadowWindow.h"

MuWidgetData::MuWidgetData(MuFramelessHelperPrivate *_d, QWidget *window, QWidget *shadowContainerWidget)
    : d(_d)
    , m_window(window)
    , m_oldShadowWidth(0)
    , m_shadowContainerWidget(shadowContainerWidget)
{
    m_bLeftButtonPressed = false;
    m_bCursorShapeChanged = false;
    m_bLeftButtonTitlePressed = false;
    m_pRubberBand = NULL;

    m_windowFlags = m_window->windowFlags();
    m_window->setMouseTracking(true);
    m_window->setAttribute(Qt::WA_Hover, true);

    if (shadowContainerWidget != nullptr)
        m_oldContentsMargin = shadowContainerWidget->contentsMargins();

    updateRubberBandStatus();
}

MuWidgetData::~MuWidgetData()
{
    m_window->setMouseTracking(false);
    m_window->setWindowFlags(m_windowFlags);
    m_window->setAttribute(Qt::WA_Hover, false);

    delete m_pRubberBand;
    m_pRubberBand = NULL;
}

QWidget *MuWidgetData::widget()
{
    return m_window;
}

void MuWidgetData::handleWidgetEvent(QEvent *event)
{
    switch (event->type()) {
    case QEvent::MouseButtonPress:
        handleMousePressEvent(static_cast<QMouseEvent *>(event));
        break;

    case QEvent::MouseButtonRelease:
        handleMouseReleaseEvent(static_cast<QMouseEvent *>(event));
        break;

    case QEvent::MouseMove:
        handleMouseMoveEvent(static_cast<QMouseEvent *>(event));
        break;

    case QEvent::Leave:
        handleLeaveEvent(static_cast<QMouseEvent *>(event));
        break;

    case QEvent::HoverMove:
        handleHoverMoveEvent(static_cast<QMouseEvent *>(event));
        break;

    default:
        break;
    }
}

void MuWidgetData::updateRubberBandStatus()
{
    if (d->m_bRubberBandOnMove || d->m_bRubberBandOnResize) {
        if(nullptr == m_pRubberBand)
            m_pRubberBand = new QRubberBand(QRubberBand::Rectangle);
    } else {
        delete m_pRubberBand;
        m_pRubberBand = nullptr;
    }
}

void MuWidgetData::setShadowWidth(const int width)
{
    if (width > 0)
        m_oldShadowWidth = width;
    m_nShadowWidth = width;
}

void MuWidgetData::handleMousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_bLeftButtonPressed = true;
        m_bLeftButtonTitlePressed = event->pos().y() < m_moveMousePos.m_nTitleHeight + m_oldShadowWidth;

        QRect frameRect = m_window->frameGeometry();
        frameRect.setX(frameRect.x() + m_nShadowWidth);
        frameRect.setY(frameRect.y() + m_nShadowWidth);
        frameRect.setWidth(frameRect.width() - m_nShadowWidth);
        frameRect.setHeight(frameRect.height() - m_nShadowWidth);
        if (Qt::WindowMaximized != m_window->windowState())
            m_pressedMousePos.recalculate(event->globalPos(), frameRect);

        m_ptDragPos = event->globalPos() - frameRect.topLeft();
        m_ptDragPos.setX(m_ptDragPos.x() + m_nShadowWidth);
        m_ptDragPos.setY(m_ptDragPos.y() + m_nShadowWidth);
        m_dLeftScale = double(m_ptDragPos.x()) / double(frameRect.width());
        m_nRightLength = frameRect.width() - m_ptDragPos.x();

        if (m_pressedMousePos.m_bOnEdges) {
            if (d->m_bRubberBandOnResize) {
                m_pRubberBand->setGeometry(frameRect);
                m_pRubberBand->show();
            }
        }
        // 当全屏的时候先不显示橡皮筋，先还原大小，再显示橡皮筋
        else if (d->m_bRubberBandOnMove && Qt::WindowMaximized != m_window->windowState()) {
            m_pRubberBand->setGeometry(frameRect);
            m_pRubberBand->show();
        }
    }
}

void MuWidgetData::handleMouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_bLeftButtonPressed = false;
        m_bLeftButtonTitlePressed = false;
        m_pressedMousePos.reset();
        if (m_pRubberBand && m_pRubberBand->isVisible()) {
            m_pRubberBand->hide();
            QRect rectTemp = m_pRubberBand->geometry();
            QRect windowRect = QRect(rectTemp.x() - m_nShadowWidth,
                                     rectTemp.y() - m_nShadowWidth,
                                     rectTemp.width() + m_nShadowWidth * 2,
                                     rectTemp.height() + m_nShadowWidth * 2);
            m_window->setGeometry(windowRect);
        }
    }
}

void MuWidgetData::handleMouseMoveEvent(QMouseEvent *event)
{
    if (m_bLeftButtonPressed) {
        if (d->m_bWidgetResizable && m_pressedMousePos.m_bOnEdges && !m_window->isMaximized()) {
            resizeWidget(event->globalPos());
        } else if (d->m_bWidgetMovable && m_bLeftButtonTitlePressed) {
            moveWidget(event->globalPos());
        }
    } else if (d->m_bWidgetResizable) {
        updateCursorShape(event->globalPos());
    }
}

void MuWidgetData::handleLeaveEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
    if (!m_bLeftButtonPressed) {
        m_window->unsetCursor();
    }
}

void MuWidgetData::handleHoverMoveEvent(QMouseEvent *event)
{
    if (d->m_bWidgetResizable && !m_bLeftButtonPressed) {
        updateCursorShape(m_window->mapToGlobal(event->pos()));
    }
}

void MuWidgetData::updateCursorShape(const QPoint &gMousePos)
{
    if (m_window->isFullScreen() || m_window->isMaximized()) {
        if(m_bCursorShapeChanged) {
            m_window->unsetCursor();
        }
        return;
    }
    QRect rect = m_window->frameGeometry();
    rect.setX(rect.x() + m_nShadowWidth);
    rect.setY(rect.y() + m_nShadowWidth);
    rect.setWidth(rect.width() - m_nShadowWidth);
    rect.setHeight(rect.height() - m_nShadowWidth);

    m_moveMousePos.recalculate(gMousePos, rect);

    if (m_moveMousePos.m_bOnTopLeftEdge || m_moveMousePos.m_bOnBottomRightEdge) {
        m_window->setCursor( Qt::SizeFDiagCursor );
        m_bCursorShapeChanged = true;
    } else if(m_moveMousePos.m_bOnTopRightEdge || m_moveMousePos.m_bOnBottomLeftEdge) {
        m_window->setCursor( Qt::SizeBDiagCursor );
        m_bCursorShapeChanged = true;
    } else if(m_moveMousePos.m_bOnLeftEdge || m_moveMousePos.m_bOnRightEdge) {
        m_window->setCursor( Qt::SizeHorCursor );
        m_bCursorShapeChanged = true;
    } else if(m_moveMousePos.m_bOnTopEdge || m_moveMousePos.m_bOnBottomEdge) {
        m_window->setCursor( Qt::SizeVerCursor );
        m_bCursorShapeChanged = true;
    } else {
        if (m_bCursorShapeChanged) {
            m_window->unsetCursor();
            m_bCursorShapeChanged = false;
        }
    }
}

void MuWidgetData::resizeWidget(const QPoint &gMousePos)
{
    QRect origRect;

    if (d->m_bRubberBandOnResize)
        origRect = m_pRubberBand->frameGeometry();
    else
        origRect = m_window->frameGeometry();

    int left = origRect.left();
    int top = origRect.top();
    int right = origRect.right();
    int bottom = origRect.bottom();
    origRect.getCoords(&left, &top, &right, &bottom);

    int minWidth = m_window->minimumWidth();
    int minHeight = m_window->minimumHeight();

    if (m_pressedMousePos.m_bOnTopLeftEdge) {
        left = gMousePos.x() - m_nShadowWidth;
        top = gMousePos.y() - m_nShadowWidth;
    } else if (m_pressedMousePos.m_bOnBottomLeftEdge) {
        left = gMousePos.x() - m_nShadowWidth;
        bottom = gMousePos.y() + m_nShadowWidth;
    } else if (m_pressedMousePos.m_bOnTopRightEdge) {
        right = gMousePos.x() + m_nShadowWidth;
        top = gMousePos.y() - m_nShadowWidth;
    } else if (m_pressedMousePos.m_bOnBottomRightEdge) {
        right = gMousePos.x() + m_nShadowWidth;
        bottom = gMousePos.y() + m_nShadowWidth;
    } else if (m_pressedMousePos.m_bOnLeftEdge) {
        left = gMousePos.x() - m_nShadowWidth;
    } else if (m_pressedMousePos.m_bOnRightEdge) {
        right = gMousePos.x() + m_nShadowWidth;
    } else if (m_pressedMousePos.m_bOnTopEdge) {
        top = gMousePos.y() - m_nShadowWidth;
    } else if (m_pressedMousePos.m_bOnBottomEdge) {
        bottom = gMousePos.y() + m_nShadowWidth;
    }

    QRect newRect(QPoint(left, top), QPoint(right, bottom));

    if (newRect.isValid()) {
        if (minWidth > newRect.width()) {
            if (left != origRect.left())
                newRect.setLeft(origRect.left());
            else
                newRect.setRight(origRect.right());
        }
        if (minHeight > newRect.height()) {
            if (top != origRect.top())
                newRect.setTop(origRect.top());
            else
                newRect.setBottom(origRect.bottom());
        }

        if (d->m_bRubberBandOnResize) {
            m_pRubberBand->setGeometry(newRect);
        } else {
            m_window->setGeometry(newRect);
        }
    }
}

void MuWidgetData::moveWidget(const QPoint &gMousePos)
{
    if (d->m_bRubberBandOnMove && Qt::WindowMaximized != m_window->windowState()) {
        m_pRubberBand->move(gMousePos - m_ptDragPos);
    } else {
        // 如果全屏时移动窗口，窗口按点击位置还原
        if (Qt::WindowMaximized == m_window->windowState()) {
            if (m_dLeftScale <= 0.3) { }
            else if (m_dLeftScale > 0.3 && m_dLeftScale < 0.7) {
                m_ptDragPos.setX(m_window->normalGeometry().width() * m_dLeftScale);
            } else if (m_dLeftScale >= 0.7) {
                m_ptDragPos.setX(m_window->normalGeometry().width() - m_nRightLength);
            }
            m_ptDragPos.setY(m_oldShadowWidth + m_ptDragPos.y());
            m_shadowContainerWidget->setContentsMargins(m_oldContentsMargin);            
            MuShadowWindow<QWidget> *pWindow = static_cast<MuShadowWindow<QWidget> *>(m_window);

            if (typeid(m_window).name() == "MuWinAeroShadowWindow") {
                m_window->resize(m_window->normalGeometry().size());
            } else {
#ifdef Q_OS_LINUX
                m_window->setWindowState(Qt::WindowNoState);
                m_window->resize(pWindow->oldSize());
#endif
                // 先resize一下，不然Aero窗体会有明显的误差
                m_window->resize(pWindow->normalGeometry().size());
            }
            m_window->showNormal();


            // 当全屏的时候先不显示橡皮筋，先还原大小，再显示橡皮筋
            if (d->m_bRubberBandOnMove) {
                m_pRubberBand->setGeometry(m_window->geometry());
                m_pRubberBand->move(gMousePos - m_ptDragPos);
                m_pRubberBand->show();
            }
        } else {
            m_oldContentsMargin = m_shadowContainerWidget->contentsMargins();
        }
        m_window->move(gMousePos - m_ptDragPos);
    }
}
