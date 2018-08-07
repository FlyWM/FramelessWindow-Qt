/**
 * 自定义无边框窗体、对话框和提示框并封装成库
 *
 * framelesshelper.cpp
 * 实现了FramelessHelper类。设置窗体是否可移动、缩放、橡皮筋等属性。
 *
 * FlyWM_
 * GitHub: https://github.com/FlyWM
 * CSDN: https://blog.csdn.net/a844651990
 *
 */

#include "framelesshelper.h"
#include "framelesshelperprivate.h"
#include "cursorposcalculator.h"
#include <QEvent>

FramelessHelper::FramelessHelper(QObject *parent)
    : QObject(parent)
    , d(new FramelessHelperPrivate())
{
    d->m_bWidgetMovable = true;
    d->m_bWidgetResizable = true;
    d->m_bRubberBandOnMove = false;
    d->m_bRubberBandOnResize = false;
}

FramelessHelper::~FramelessHelper()
{
    QList<QWidget*> keys = d->m_widgetDataHash.keys();
    int size = keys.size();
    for (int i = 0; i < size; ++i)
    {
        delete d->m_widgetDataHash.take(keys[i]);
    }

    delete d;
}

void FramelessHelper::activateOn(QWidget *topLevelWidget)
{
    if (!d->m_widgetDataHash.contains(topLevelWidget))
    {
       WidgetData *data = new WidgetData(d, topLevelWidget);
       d->m_widgetDataHash.insert(topLevelWidget, data);

       topLevelWidget->installEventFilter(this);
    }
}

void FramelessHelper::removeFrom(QWidget *topLevelWidget)
{
    WidgetData *data = d->m_widgetDataHash.take(topLevelWidget);
    if (data)
    {
        topLevelWidget->removeEventFilter(this);
        delete data;
    }
}

void FramelessHelper::setWidgetMovable(bool movable)
{
    d->m_bWidgetMovable = movable;
}

void FramelessHelper::setWidgetResizable(bool resizable)
{
    d->m_bWidgetResizable = resizable;
}

void FramelessHelper::setRubberBandOnMove(bool movable)
{
    d->m_bRubberBandOnMove = movable;
    QList<WidgetData*> list = d->m_widgetDataHash.values();
    foreach (WidgetData *data, list)
    {
        data->updateRubberBandStatus();
    }
}

void FramelessHelper::setRubberBandOnResize(bool resizable)
{
    d->m_bRubberBandOnResize = resizable;
    QList<WidgetData*> list = d->m_widgetDataHash.values();
    foreach (WidgetData *data, list)
    {
        data->updateRubberBandStatus();
    }
}

void FramelessHelper::setBorderWidth(uint width)
{
    if (width > 0)
    {
        CursorPosCalculator::m_nBorderWidth = width;
    }
}

void FramelessHelper::setTitleHeight(uint height)
{
    if (height > 0)
    {
        CursorPosCalculator::m_nTitleHeight = height;
    }
}

bool FramelessHelper::widgetResizable() const
{
    return d->m_bWidgetResizable;
}

bool FramelessHelper::widgetMoable() const
{
    return d->m_bWidgetMovable;
}

bool FramelessHelper::rubberBandOnMove() const
{
    return d->m_bRubberBandOnMove;
}

bool FramelessHelper::rubberBandOnResize() const
{
    return d->m_bRubberBandOnResize;
}

uint FramelessHelper::borderWidth() const
{
    return CursorPosCalculator::m_nBorderWidth;
}

uint FramelessHelper::titleHeight() const
{
    return CursorPosCalculator::m_nTitleHeight;
}

bool FramelessHelper::eventFilter(QObject *watched, QEvent *event)
{
    switch (event->type()) {
    case QEvent::MouseMove:
    case QEvent::HoverMove:
    case QEvent::MouseButtonPress:
    case QEvent::MouseButtonRelease:
    case QEvent::Leave:
    {
        WidgetData *data = d->m_widgetDataHash.value(static_cast<QWidget *>(watched));
        if (data)
        {
            data->handleWidgetEvent(event);
            return true;
        }
    }
    default:
        return QObject::eventFilter(watched, event);
    }
}
