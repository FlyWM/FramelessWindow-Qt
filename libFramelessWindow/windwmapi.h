#ifndef WINDWMAPI_H
#define WINDWMAPI_H

#include <windows.h>

typedef struct _MARGINS
{
    int cxLeftWidth;      // width of left border that retains its size
    int cxRightWidth;     // width of right border that retains its size
    int cyTopHeight;      // height of top border that retains its size
    int cyBottomHeight;   // height of bottom border that retains its size
} MARGINS, *PMARGINS;

class WinDwmapi
{
public:
    WinDwmapi();
    ~WinDwmapi();

    typedef HRESULT (WINAPI* DwmIsCompositionEnabledPtr)(__out BOOL* pfEnabled);
    typedef HRESULT (WINAPI* DwmExtendFrameIntoClientAreaPtr)(__in HWND hWnd, __in const MARGINS *pMarInset);

    HRESULT DwmIsCompositionEnabled(BOOL* pfEnabled) const;
    HRESULT DwmExtendFrameIntoClientArea(HWND hWnd, const MARGINS *pMarInset) const;

    static const WinDwmapi* instance();


private:
      DwmIsCompositionEnabledPtr dwm_is_composition_enabled_;
      DwmExtendFrameIntoClientAreaPtr dwm_extendframe_into_client_area_;
      HMODULE dwmapi_dll_;
};

#endif // WINDWMAPI_H
