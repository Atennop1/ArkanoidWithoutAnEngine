#pragma once
#include "../../Converters/converters.h"

struct WindowHandles
{
private:
    HDC *m_hdc;
    HWND *m_hwnd;
    
public:
    WindowHandles(HDC *hdc, HWND *hwnd);
    ~WindowHandles();

    HWND* HWND() const;
    HDC* HDC() const;
};
