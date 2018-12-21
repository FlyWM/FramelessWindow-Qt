/**
 * 自定义无边框窗体、对话框和提示框
 *
 * MuFramelessHelperPrivate.h
 * 存储界面对应的数据集合，以及是否可移动、可缩放属性。
 *
 * FlyWM_
 * GitHub: https://github.com/FlyWM
 * CSDN: https://blog.csdn.net/a844651990
 *
 */

#ifndef MUFRAMELESSHELPERPRIVATE_H
#define MUFRAMELESSHELPERPRIVATE_H

#include <QHash>
#include <QWidget>
#include "MuWidgetData.h"

/**
 * @brief The FramelessHelperPrivate class
 *  存储界面对应的数据集合，以及是否可移动、可缩放属性
 */
class MuFramelessHelperPrivate
{
public:
    QHash<QWidget*, MuWidgetData*> m_widgetDataHash;
    int m_nShadowWidth;
    bool m_bWidgetMovable        : true;
    bool m_bWidgetResizable      : true;
    bool m_bRubberBandOnResize   : true;
    bool m_bRubberBandOnMove     : true;
};

#endif // MUFRAMELESSHELPERPRIVATE_H
