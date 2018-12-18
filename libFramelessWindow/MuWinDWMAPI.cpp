#include "MuWinDWMAPI.h"

MuWinDwmapi::MuWinDwmapi()
    : dwmapi_dll_(LoadLibraryW(L"dwmapi.dll"))
    , dwm_is_composition_enabled_(NULL)
{
    if (dwmapi_dll_) {
        dwm_is_composition_enabled_ = reinterpret_cast<DwmIsCompositionEnabledPtr>(GetProcAddress(dwmapi_dll_, "DwmIsCompositionEnabled"));
        dwm_extendframe_into_client_area_ = reinterpret_cast<DwmExtendFrameIntoClientAreaPtr>(GetProcAddress(dwmapi_dll_, "DwmExtendFrameIntoClientArea"));
    }
}

MuWinDwmapi::~MuWinDwmapi()
{
    if (dwmapi_dll_) {
        FreeLibrary(dwmapi_dll_);
    }
}

HRESULT MuWinDwmapi::DwmIsCompositionEnabled(BOOL *pfEnabled) const
{
    if (dwm_is_composition_enabled_) {
        return dwm_is_composition_enabled_(pfEnabled);
    }

    return E_NOTIMPL;
}

HRESULT MuWinDwmapi::DwmExtendFrameIntoClientArea(HWND hWnd, const MARGINS *pMarInset) const
{
    if (dwm_extendframe_into_client_area_) {
        return dwm_extendframe_into_client_area_(hWnd, pMarInset);
    }

    return E_NOTIMPL;
}

const MuWinDwmapi *MuWinDwmapi::instance()
{
    static const MuWinDwmapi s_dwmapi;
    return &s_dwmapi;
}
