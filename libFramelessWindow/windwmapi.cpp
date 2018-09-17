#include "windwmapi.h"

WinDwmapi::WinDwmapi()
    : dwmapi_dll_(LoadLibraryW(L"dwmapi.dll"))
    , dwm_is_composition_enabled_(NULL)
{
    if(dwmapi_dll_)
    {
        dwm_is_composition_enabled_ = reinterpret_cast<DwmIsCompositionEnabledPtr>(GetProcAddress(dwmapi_dll_, "DwmIsCompositionEnabled"));
        dwm_extendframe_into_client_area_ = reinterpret_cast<DwmExtendFrameIntoClientAreaPtr>(GetProcAddress(dwmapi_dll_, "DwmExtendFrameIntoClientArea"));
    }
}

WinDwmapi::~WinDwmapi()
{
    if(dwmapi_dll_)
    {
        FreeLibrary(dwmapi_dll_);
    }
}

HRESULT WinDwmapi::DwmIsCompositionEnabled(BOOL *pfEnabled) const
{
    if(dwm_is_composition_enabled_)
    {
        return dwm_is_composition_enabled_(pfEnabled);
    }

    return E_NOTIMPL;
}

HRESULT WinDwmapi::DwmExtendFrameIntoClientArea(HWND hWnd, const MARGINS *pMarInset) const
{
    if(dwm_extendframe_into_client_area_)
    {
        return dwm_extendframe_into_client_area_(hWnd, pMarInset);
    }

    return E_NOTIMPL;
}

const WinDwmapi *WinDwmapi::instance()
{
    static const WinDwmapi s_dwmapi;
    return &s_dwmapi;
}
