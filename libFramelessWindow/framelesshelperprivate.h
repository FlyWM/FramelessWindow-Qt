/**
 * 自定义无边框窗体、对话框和提示框并封装成库
 *
 * framelesshelperprivate.h
 * 存储界面对应的数据集合，以及是否可移动、可缩放属性。
 *
 * FlyWM_
 * GitHub: https://github.com/FlyWM
 * CSDN: https://blog.csdn.net/a844651990
 *
 */

#ifndef FRAMELESSHELPERPRIVATE_H
#define FRAMELESSHELPERPRIVATE_H

#include "widgetdata.h"
#include <QHash>
#include <QWidget>
/**
 * @brief The FramelessHelperPrivate class
 *  存储界面对应的数据集合，以及是否可移动、可缩放属性
 */
class FramelessHelperPrivate
{
public:
    QHash<QWidget*, WidgetData*> m_widgetDataHash;
    bool m_bWidgetMovable        : true;
    bool m_bWidgetResizable      : true;
    bool m_bRubberBandOnResize   : true;
    bool m_bRubberBandOnMove     : true;
};

#endif // FRAMELESSHELPERPRIVATE_H
