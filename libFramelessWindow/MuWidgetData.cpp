/**
 * 自定义无边框窗体、对话框和提示框并封装成库
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

MuWidgetData::MuWidgetData(MuFramelessHelperPrivate *_d, QWidget *pTopLevelWidget)
{
    d = _d;
    m_pWidget = pTopLevelWidget;
    m_bLeftButtonPressed = false;
    m_bCursorShapeChanged = false;
    m_bLeftButtonTitlePressed = false;
    m_pRubberBand = NULL;

    m_windowFlags = m_pWidget->windowFlags();
    m_pWidget->setMouseTracking(true);
    m_pWidget->setAttribute(Qt::WA_Hover, true);

    updateRubberBandStatus();
}

MuWidgetData::~MuWidgetData()
{
    m_pWidget->setMouseTracking(false);
    m_pWidget->setWindowFlags(m_windowFlags);
    m_pWidget->setAttribute(Qt::WA_Hover, false);

    delete m_pRubberBand;
    m_pRubberBand = NULL;
}

QWidget *MuWidgetData::widget()
{
    return m_pWidget;
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
    if (d->m_bRubberBandOnMove || d->m_bRubberBandOnResize)
    {
        if(NULL == m_pRubberBand)
            m_pRubberBand = new QRubberBand(QRubberBand::Rectangle);
    }
    else
    {
        delete m_pRubberBand;
        m_pRubberBand = NULL;
    }
}

void MuWidgetData::setShadowWidth(const int width)
{
    m_nShadowWidth = width;
}

void MuWidgetData::handleMousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_bLeftButtonPressed = true;
        m_bLeftButtonTitlePressed = event->pos().y() < m_moveMousePos.m_nTitleHeight;

        QRect frameRect = m_pWidget->frameGeometry();
        frameRect.setX(frameRect.x() + m_nShadowWidth);
        frameRect.setY(frameRect.y() + m_nShadowWidth);
        frameRect.setWidth(frameRect.width() - m_nShadowWidth);
        frameRect.setHeight(frameRect.height() - m_nShadowWidth);
        m_pressedMousePos.recalculate(event->globalPos(), frameRect);

        m_ptDragPos = event->globalPos() - frameRect.topLeft();
        m_dLeftScale = double(m_ptDragPos.x()) / double(frameRect.width());
        m_nRightLength = frameRect.width() - m_ptDragPos.x();

        if (m_pressedMousePos.m_bOnEdges) {
            if (d->m_bRubberBandOnResize) {
                m_pRubberBand->setGeometry(frameRect);
                m_pRubberBand->show();
            }
        }
        else if (d->m_bRubberBandOnMove) {
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
            m_pWidget->setGeometry(m_pRubberBand->geometry());
        }
    }
}

void MuWidgetData::handleMouseMoveEvent(QMouseEvent *event)
{
    if (m_bLeftButtonPressed) {
        if (d->m_bWidgetResizable && m_pressedMousePos.m_bOnEdges) {
            resizeWidget(event->globalPos());
        }
        else if (d->m_bWidgetMovable && m_bLeftButtonTitlePressed) {
            moveWidget(event->globalPos());
        }
    }
    else if (d->m_bWidgetResizable) {
        updateCursorShape(event->globalPos());
    }
}

void MuWidgetData::handleLeaveEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
    if (!m_bLeftButtonPressed) {
        m_pWidget->unsetCursor();
    }
}

void MuWidgetData::handleHoverMoveEvent(QMouseEvent *event)
{
    if (d->m_bWidgetResizable && !m_bLeftButtonPressed) {
        updateCursorShape(m_pWidget->mapToGlobal(event->pos()));
    }
}

void MuWidgetData::updateCursorShape(const QPoint &gMousePos)
{
    if (m_pWidget->isFullScreen() || m_pWidget->isMaximized()) {
        if(m_bCursorShapeChanged) {
            m_pWidget->unsetCursor();
        }
        return;
    }
    QRect rect = m_pWidget->frameGeometry();
    rect.setX(rect.x() + m_nShadowWidth);
    rect.setY(rect.y() + m_nShadowWidth);
    rect.setWidth(rect.width() - m_nShadowWidth);
    rect.setHeight(rect.height() - m_nShadowWidth);

    m_moveMousePos.recalculate(gMousePos, rect);

    if (m_moveMousePos.m_bOnTopLeftEdge || m_moveMousePos.m_bOnBottomRightEdge) {
        m_pWidget->setCursor( Qt::SizeFDiagCursor );
        m_bCursorShapeChanged = true;
    }
    else if(m_moveMousePos.m_bOnTopRightEdge || m_moveMousePos.m_bOnBottomLeftEdge) {
        m_pWidget->setCursor( Qt::SizeBDiagCursor );
        m_bCursorShapeChanged = true;
    }
    else if(m_moveMousePos.m_bOnLeftEdge || m_moveMousePos.m_bOnRightEdge) {
        m_pWidget->setCursor( Qt::SizeHorCursor );
        m_bCursorShapeChanged = true;
    }
    else if(m_moveMousePos.m_bOnTopEdge || m_moveMousePos.m_bOnBottomEdge) {
        m_pWidget->setCursor( Qt::SizeVerCursor );
        m_bCursorShapeChanged = true;
    }
    else {
        if (m_bCursorShapeChanged) {
            m_pWidget->unsetCursor();
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
        origRect = m_pWidget->frameGeometry();

    int left = origRect.left();
    int top = origRect.top();
    int right = origRect.right();
    int bottom = origRect.bottom();
    origRect.getCoords(&left, &top, &right, &bottom);

    int minWidth = m_pWidget->minimumWidth();
    int minHeight = m_pWidget->minimumHeight();

    if (m_pressedMousePos.m_bOnTopLeftEdge) {
        left = gMousePos.x() - m_nShadowWidth;
        top = gMousePos.y() - m_nShadowWidth;
    }
    else if (m_pressedMousePos.m_bOnBottomLeftEdge) {
        left = gMousePos.x() - m_nShadowWidth;
        bottom = gMousePos.y() + m_nShadowWidth;
    }
    else if (m_pressedMousePos.m_bOnTopRightEdge) {
        right = gMousePos.x() + m_nShadowWidth;
        top = gMousePos.y() - m_nShadowWidth;
    }
    else if (m_pressedMousePos.m_bOnBottomRightEdge) {
        right = gMousePos.x() + m_nShadowWidth;
        bottom = gMousePos.y() + m_nShadowWidth;
    }
    else if (m_pressedMousePos.m_bOnLeftEdge) {
        left = gMousePos.x() - m_nShadowWidth;
    }
    else if (m_pressedMousePos.m_bOnRightEdge) {
        right = gMousePos.x() + m_nShadowWidth;
    }
    else if (m_pressedMousePos.m_bOnTopEdge) {
        top = gMousePos.y() - m_nShadowWidth;
    }
    else if (m_pressedMousePos.m_bOnBottomEdge) {
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
        }
        else {
            m_pWidget->setGeometry(newRect);
        }
    }
}

void MuWidgetData::moveWidget(const QPoint &gMousePos)
{
    if (d->m_bRubberBandOnMove) {
        m_pRubberBand->move(gMousePos - m_ptDragPos);
    } else {
        // 如果全屏时移动窗口，窗口按点击位置还原
        if (m_pWidget->isMaximized() || m_pWidget->isFullScreen()) {
            if (m_dLeftScale <= 0.3) { }
            else if (m_dLeftScale > 0.3 && m_dLeftScale < 0.7) {
                m_ptDragPos.setX(m_pWidget->normalGeometry().width() * m_dLeftScale);
            } else if (m_dLeftScale >= 0.7) {
                m_ptDragPos.setX(m_pWidget->normalGeometry().width() - m_nRightLength);
            }

            m_pWidget->setGeometry(0, 0, m_pWidget->normalGeometry().width(), m_pWidget->normalGeometry().height());
        }
        m_pWidget->move(gMousePos - m_ptDragPos);
    }
}
