/**
 * 自定义无边框窗体、对话框和提示框
 *
 * MuFramelessHelper.h
 * MuFramelessHelper
 *
 * FlyWM_
 * GitHub: https://github.com/FlyWM
 * CSDN: https://blog.csdn.net/a844651990
 *
 */

#ifndef MUFRAMELESSHELPER_H
#define MUFRAMELESSHELPER_H

#include <QObject>
#include <QHash>
#include "MuWidgetData.h"
#include "FramelessWindow_Global.h"


class QWdiget;
class MuFramelessHelperPrivate;
class FRAMELESSWINDOWSHARED_EXPORT MuFramelessHelper : public QObject
{
    Q_OBJECT
public:
    explicit MuFramelessHelper(QObject *parent = nullptr);
    ~MuFramelessHelper();

    /**
     * @brief activateOn 激活窗体
     * @param topLevelWidget
     */
    void activateOn(QWidget *topLevelWidget, QWidget *shadowContainerWidget = nullptr);

    /**
     * @brief removeFrom 移除窗体
     * @param topLevelWidget
     */
    void removeFrom(QWidget *topLevelWidget);

    /**
     * @brief setWidgetMovable 设置窗体移动
     * @param movable
     */
    void setWidgetMovable(bool movable);

    /**
     * @brief setWidgetResizable 设置窗体缩放
     * @param resizable
     */

    void setWidgetResizable(bool resizable);
    /**
     * @brief setRubberBandOnMove 设置橡皮筋是否移动
     * @param movable
     */
    void setRubberBandOnMove(bool movable);
    /**
     * @brief setRubberBandOnResize 设置橡皮筋是否可以缩放
     * @param resizable
     */
    void setRubberBandOnResize(bool resizable);

    /**
     * @brief setBorderWidth 设置边框的宽度
     * @param width  unsigned int
     */
    void setBorderWidth(uint width);

    /**
     * @brief setTitleHeight 设置标题栏高度
     * @param height unsigned int
     */
    void setTitleHeight(uint height);

    /**
     * @brief setShadowWidth 设置边框阴影的宽度，会涉及到在什么位置改变鼠标的形状
     * @param width
     */
    void setShadowWidth(int width);

    bool widgetResizable() const;
    bool widgetMoable() const;
    bool rubberBandOnMove() const;
    bool rubberBandOnResize() const;
    uint borderWidth() const;
    uint titleHeight() const;

protected:
    virtual bool eventFilter(QObject *watched, QEvent *event);

private:
    MuFramelessHelperPrivate *d;
};

#endif // MUFRAMELESSHELPER_H
