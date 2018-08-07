/**
 * 自定义无边框窗体、对话框和提示框并封装成库
 *
 * framelesshelper.h
 * FramelessHelper类。设置窗体是否可移动、缩放、橡皮筋等属性。
 *
 * FlyWM_
 * GitHub: https://github.com/FlyWM
 * CSDN: https://blog.csdn.net/a844651990
 *
 */

#ifndef FRAMELESSHELPER_H
#define FRAMELESSHELPER_H

#include <QObject>
#include <QHash>
#include "widgetdata.h"


class QWdiget;
class FramelessHelperPrivate;
class FramelessHelper : public QObject
{
    Q_OBJECT
public:
    explicit FramelessHelper(QObject *parent = nullptr);
    ~FramelessHelper();

    /**
     * @brief activateOn
     *  激活窗体
     * @param topLevelWidget
     *  QWidget *
     */
    void activateOn(QWidget *topLevelWidget);

    /**
     * @brief removeFrom
     *  移除窗体
     * @param topLevelWidget
     *  QWidget *
     */
    void removeFrom(QWidget *topLevelWidget);

    /**
     * @brief setWidgetMovable
     *  设置窗体移动
     * @param movable
     *  bool
     */
    void setWidgetMovable(bool movable);

    /**
     * @brief setWidgetResizable
     *  设置窗体缩放
     * @param resizable
     *  bool
     */

    void setWidgetResizable(bool resizable);
    /**
     * @brief setRubberBandOnMove
     *  设置橡皮筋移动
     * @param movable
     *  bool
     */
    void setRubberBandOnMove(bool movable);
    /**
     * @brief setRubberBandOnResize
     *  设置橡皮筋缩放
     * @param resizable
     *  bool
     */
    void setRubberBandOnResize(bool resizable);

    /**
     * @brief setBorderWidth
     *  设置边框的宽度
     * @param width
     *  unsigned int
     */
    void setBorderWidth(uint width);

    /**
     * @brief setTitleHeight
     *  设置标题栏高度
     * @param height
     *  unsigned int
     */
    void setTitleHeight(uint height);

    bool widgetResizable() const;
    bool widgetMoable() const;
    bool rubberBandOnMove() const;
    bool rubberBandOnResize() const;
    uint borderWidth() const;
    uint titleHeight() const;

protected:
    virtual bool eventFilter(QObject *watched, QEvent *event);

private:
    FramelessHelperPrivate *d;
};

#endif // FRAMELESSHELPER_H
