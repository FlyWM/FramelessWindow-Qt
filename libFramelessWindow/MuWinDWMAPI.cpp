/**
 * 自定义无边框窗体、对话框和提示框
 *
 * MuWinDwmapi.cpp
 * 简单封装了Win平台下的DWM接口实现，后期可能弃用
 *
 * dnybz
 * GitHub: https://github.com/dnybz
 *
 * FlyWM_
 * GitHub: https://github.com/FlyWM
 * CSDN: https://blog.csdn.net/a844651990
 *
 */
#include "MuWinDWMAPI.h"

#ifdef Q_OS_WIN32

MuWinDwmapi::MuWinDwmapi()
{
}

MuWinDwmapi::~MuWinDwmapi()
{
}


MuWinDwmapi *MuWinDwmapi::instance()
{
    static MuWinDwmapi s_dwmapi;
    return &s_dwmapi;
}

HRESULT MuWinDwmapi::dwmExtendFrameIntoClientArea(HWND hWnd, const MARGINS *pMarInset) const
{
    return DwmExtendFrameIntoClientArea(hWnd, pMarInset);
}

HRESULT MuWinDwmapi::enableBlurBehind(HWND hwnd)
{
    HRESULT hr = S_OK;

    // Create and populate the blur-behind structure.
    DWM_BLURBEHIND bb = {0};

    // Specify blur-behind and blur region.
    bb.dwFlags = DWM_BB_ENABLE;
    bb.fEnable = true;
    bb.hRgnBlur = NULL;

    // Enable blur-behind.
    hr = DwmEnableBlurBehindWindow(hwnd, &bb);

    return hr;
}

HRESULT MuWinDwmapi::dwmEnableTransition(HWND hWnd, bool enable)
{
    HRESULT hr = S_OK;
    BOOL enabled;
    if (enable) {
        enabled = FALSE;
        hr = DwmSetWindowAttribute(hWnd, DWMWA_TRANSITIONS_FORCEDISABLED, &enabled, sizeof(enabled));
    } else {
        enabled = TRUE;
        hr = DwmSetWindowAttribute(hWnd, DWMWA_TRANSITIONS_FORCEDISABLED, &enabled, sizeof(enabled));
    }
    return hr;
}

int MuWinDwmapi::dwmIsCompositionEnabledsEnabled() const
{
    HRESULT hr = S_OK;
    BOOL enabled;
    hr = DwmIsCompositionEnabled(&enabled);
    if (hr == S_OK)
        return enabled;
    else
        return -1;
}

HRESULT MuWinDwmapi::dwmEnableComposition(bool enable)
{
    HRESULT hr = S_OK;
    if (enable)
        hr = DwmEnableComposition(DWM_EC_ENABLECOMPOSITION);
    else
        hr = DwmEnableComposition(DWM_EC_DISABLECOMPOSITION);

    return hr;
}

HRESULT MuWinDwmapi::dwmEnabledNoClientRender(HWND hWnd, bool enable)
{
    HRESULT hr = S_OK;
    DWMNCRENDERINGPOLICY ncrp;
    if (enable) {
        ncrp = DWMNCRP_ENABLED;
        hr = DwmSetWindowAttribute(hWnd, DWMWA_NCRENDERING_POLICY, &ncrp, sizeof(ncrp));
    } else {
        ncrp = DWMNCRP_DISABLED;
        hr = DwmSetWindowAttribute(hWnd, DWMWA_NCRENDERING_POLICY, &ncrp, sizeof(ncrp));
    }
    return hr;
}


#endif
