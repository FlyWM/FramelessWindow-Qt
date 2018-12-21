/**
 * 自定义无边框窗体、对话框和提示框
 *
 * MuCursorPosCalculator.h
 * 计算鼠标是否位于左、上、右、下、左上角、左下角、右上角、右下角
 *
 * FlyWM_
 * GitHub: https://github.com/FlyWM
 * CSDN: https://blog.csdn.net/a844651990
 *
 */

#ifndef MUCURSORPOSCALCULATOR_H
#define MUCURSORPOSCALCULATOR_H

/**
 * @brief The CursorPosCalculator class
 *  计算鼠标是否位于左、上、右、下、左上角、左下角、右上角、右下角
 */
class QPoint;
class QRect;
class MuCursorPosCalculator
{
public:
    explicit MuCursorPosCalculator();
    void reset();
    void recalculate(const QPoint &gMousePos, const QRect &frameRect);

public:
    bool m_bOnEdges             : true;
    bool m_bOnLeftEdge          : true;
    bool m_bOnRightEdge         : true;
    bool m_bOnTopEdge           : true;
    bool m_bOnBottomEdge        : true;
    bool m_bOnTopLeftEdge       : true;
    bool m_bOnBottomLeftEdge    : true;
    bool m_bOnTopRightEdge      : true;
    bool m_bOnBottomRightEdge   : true;

    static int m_nBorderWidth;
    static int m_nTitleHeight;
    static int m_nShadowWidth;
};

#endif // MuCURSORPOSCALCULATOR_H
