/**
 * 自定义无边框窗体、对话框和提示框
 *
 * MuFramelessHelper.cpp
 * 实现了FramelessHelper类。设置窗体是否可移动、缩放、橡皮筋等属性。
 *
 * FlyWM_
 * GitHub: https://github.com/FlyWM
 * CSDN: https://blog.csdn.net/a844651990
 *
 */

#include <QEvent>
#include <QDebug>
#include "MuFramelessHelper.h"
#include "MuFramelessHelperPrivate.h"
#include "MuCursorPosCalculator.h"

MuFramelessHelper::MuFramelessHelper(QObject *parent)
    : QObject(parent)
    , d(new MuFramelessHelperPrivate())
{
    d->m_bWidgetMovable = true;
    d->m_bWidgetResizable = true;
    d->m_bRubberBandOnMove = false;
    d->m_bRubberBandOnResize = false;
}

MuFramelessHelper::~MuFramelessHelper()
{
    QList<QWidget*> keys = d->m_widgetDataHash.keys();
    int size = keys.size();
    for (int i = 0; i < size; ++i) {
        delete d->m_widgetDataHash.take(keys[i]);
    }

    delete d;
}

void MuFramelessHelper::activateOn(QWidget *topLevelWidget, QWidget *shadowContainerWidget)
{
    if (!d->m_widgetDataHash.contains(topLevelWidget)) {
       MuWidgetData *data = new MuWidgetData(d, topLevelWidget, shadowContainerWidget);
       data->setShadowWidth(d->m_nShadowWidth);
       d->m_widgetDataHash.insert(topLevelWidget, data);
       topLevelWidget->installEventFilter(this);
    }
}

void MuFramelessHelper::removeFrom(QWidget *topLevelWidget)
{
    MuWidgetData *data = d->m_widgetDataHash.take(topLevelWidget);
    if (data) {
        topLevelWidget->removeEventFilter(this);
        delete data;
    }
}

void MuFramelessHelper::setWidgetMovable(bool movable)
{
    d->m_bWidgetMovable = movable;
}

void MuFramelessHelper::setWidgetResizable(bool resizable)
{
    d->m_bWidgetResizable = resizable;
}

void MuFramelessHelper::setRubberBandOnMove(bool movable)
{
    d->m_bRubberBandOnMove = movable;
    QList<MuWidgetData*> list = d->m_widgetDataHash.values();
    foreach (MuWidgetData *data, list) {
        data->updateRubberBandStatus();
    }
}

void MuFramelessHelper::setRubberBandOnResize(bool resizable)
{
    d->m_bRubberBandOnResize = resizable;
    QList<MuWidgetData*> list = d->m_widgetDataHash.values();
    foreach (MuWidgetData *data, list) {
        data->updateRubberBandStatus();
    }
}

void MuFramelessHelper::setBorderWidth(uint width)
{
    if (width > 0) {
        MuCursorPosCalculator::m_nBorderWidth = width;
    }
}

void MuFramelessHelper::setTitleHeight(uint height)
{
    if (height > 0) {
        MuCursorPosCalculator::m_nTitleHeight = height;
    }
}

void MuFramelessHelper::setShadowWidth(int width)
{
    if (width >= 0) {
        d->m_nShadowWidth = width;
        for (auto key : d->m_widgetDataHash.keys()) {
            d->m_widgetDataHash.value(key)->setShadowWidth(d->m_nShadowWidth);
        }
    }
}

bool MuFramelessHelper::widgetResizable() const
{
    return d->m_bWidgetResizable;
}

bool MuFramelessHelper::widgetMoable() const
{
    return d->m_bWidgetMovable;
}

bool MuFramelessHelper::rubberBandOnMove() const
{
    return d->m_bRubberBandOnMove;
}

bool MuFramelessHelper::rubberBandOnResize() const
{
    return d->m_bRubberBandOnResize;
}

uint MuFramelessHelper::borderWidth() const
{
    return MuCursorPosCalculator::m_nBorderWidth;
}

uint MuFramelessHelper::titleHeight() const
{
    return MuCursorPosCalculator::m_nTitleHeight;
}

bool MuFramelessHelper::eventFilter(QObject *watched, QEvent *event)
{
    switch (event->type()) {
    case QEvent::MouseMove:
    case QEvent::HoverMove:
    case QEvent::MouseButtonPress:
    case QEvent::MouseButtonRelease:
    case QEvent::Leave: {
        MuWidgetData *data = d->m_widgetDataHash.value(static_cast<QWidget *>(watched));
        if (data) {
            data->handleWidgetEvent(event);
            return true;
        }
    }
    default:
        return QObject::eventFilter(watched, event);
    }
}
