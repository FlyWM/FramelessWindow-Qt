/**
 * 自定义无边框窗体、对话框和提示框
 *
 * MuWinDwmapi.h
 * 简单封装了Win平台下的DWM接口，后期可能弃用
 *
 * dnybz
 * GitHub: https://github.com/dnybz
 *
 * FlyWM_
 * GitHub: https://github.com/FlyWM
 * CSDN: https://blog.csdn.net/a844651990
 *
 */

#include <QtGlobal>

#ifdef Q_OS_WIN32

#ifndef MUWINDWMAPI_H
#define MUWINDWMAPI_H

#include <windows.h>
#include <dwmapi.h>
#include "FramelessWindow_Global.h"

class FRAMELESSWINDOWSHARED_EXPORT MuWinDwmapi
{
public:
    static MuWinDwmapi* instance();

    /**
     * @brief DwnIsEnabled 判断系统Aero效果是否开启
     * @return -1，函数执行失败； 0，未开启；1，已开启；
     */
    int dwmIsCompositionEnabledsEnabled() const;

    /**
     * @brief dwmEnableComposition 开启或关闭Aero Glass效果
     * @param enable
     * @return
     */
    HRESULT dwmEnableComposition(bool enable);

    /**
     * @brief dwmEnabledNoClientRender
     *        开启或者关闭非客户区渲染
     *        \warning 当系统的Aero Glass关闭时，设置无效。
     * @param hWnd
     * @param enable
     * @return
     */
    HRESULT dwmEnabledNoClientRender(HWND hWnd, bool enable);

    /**
     * @brief dwmExtendFrameIntoClientArea
     *        GLASS效果向客户区域扩展
     *        \note 非客户区通常包括窗口标题栏和窗口边框。
     *              缺省状态下，非客户区会被渲染成毛玻璃效果，这也称为Compostion。
     * @param hWnd 窗口句柄
     * @param pMarInset
     *        MARGINS指定了在上下左右4个方向上扩展的范围。如果4个值均为-1，则扩展到整个客户区。
     * @return
     */
    HRESULT dwmExtendFrameIntoClientArea(HWND hWnd, const MARGINS *pMarInset) const;

    /**
     * @brief enableBlurBehind 在指定窗口上启用模糊效果。
     * @param hwnd 窗口句柄
     * @return
     */
    HRESULT enableBlurBehind(HWND hwnd);

    /**
     * @brief dwmEnableTransition
     *        Transition控制是否以动画方式显示窗口的最小化和还原。
     *        只对当前窗口有效
     * @param hWnd
     * @param enable
     * @return
     */
    HRESULT dwmEnableTransition(HWND hWnd, bool enable);

private:
    MuWinDwmapi();
    MuWinDwmapi(const MuWinDwmapi &);
    MuWinDwmapi &operator = (const MuWinDwmapi &);
    ~MuWinDwmapi();

private:

};


#endif // MUWINDWMAPI_H

#endif
