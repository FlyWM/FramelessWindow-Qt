/**
 * 自定义无边框窗体、对话框和提示框
 *
 * MuCursorPosCalculator.cpp
 * 计算鼠标是否位于左、上、右、下、左上角、左下角、右上角、右下角
 *
 * FlyWM_
 * GitHub: https://github.com/FlyWM
 * CSDN: https://blog.csdn.net/a844651990
 *
 */

#include <QPoint>
#include <QRect>
#include "MuCursorPosCalculator.h"

/**
 * @brief MuCursorPosCalculator::m_nBorderWidth
 *  \warning
 *  如果是WinAeroWindow,那么m_nBorderWidth的大小需要和
 *  titleBar的rigtMargin一致，不然会造成拖放和关闭按钮的冲突
 */
int MuCursorPosCalculator::m_nBorderWidth = 5;

int MuCursorPosCalculator::m_nTitleHeight = 30;
int MuCursorPosCalculator::m_nShadowWidth = 0;

MuCursorPosCalculator::MuCursorPosCalculator()
{
    reset();
}

void MuCursorPosCalculator::reset()
{
    m_bOnEdges = false;
    m_bOnLeftEdge = false;
    m_bOnRightEdge = false;
    m_bOnTopEdge = false;
    m_bOnBottomEdge = false;
    m_bOnTopLeftEdge = false;
    m_bOnBottomLeftEdge = false;
    m_bOnTopRightEdge  = false;
    m_bOnBottomRightEdge = false;
}

void MuCursorPosCalculator::recalculate(const QPoint &gMousePos, const QRect &frameRect)
{
    int globalMouseX = gMousePos.x();
    int globalMouseY = gMousePos.y();

    int frameX = frameRect.x();
    int frameY = frameRect.y();

    int frameWidth = frameRect.width();
    int frameHeight = frameRect.height();

    // 边框边缘触发光标变化
    //
    m_bOnLeftEdge = (globalMouseX >= frameX - m_nBorderWidth &&
                     globalMouseX <= frameX + m_nBorderWidth);
    m_bOnRightEdge = (globalMouseX >= frameX + frameWidth - m_nBorderWidth &&
                      globalMouseX <= frameX + frameWidth + m_nBorderWidth);
    m_bOnTopEdge = (globalMouseY >= frameY - m_nBorderWidth &&
                     globalMouseY <= frameY + 5);
    m_bOnBottomEdge = (globalMouseY >= frameY + frameHeight - m_nBorderWidth &&
                    globalMouseY <= frameY + frameHeight + m_nBorderWidth);

    m_bOnTopLeftEdge = m_bOnTopEdge && m_bOnLeftEdge;
    m_bOnBottomLeftEdge = m_bOnBottomEdge && m_bOnLeftEdge;
    m_bOnTopRightEdge = m_bOnTopEdge && m_bOnRightEdge;
    m_bOnBottomRightEdge = m_bOnBottomEdge && m_bOnRightEdge;

    m_bOnEdges = m_bOnLeftEdge || m_bOnRightEdge || m_bOnTopEdge || m_bOnBottomEdge;
}
