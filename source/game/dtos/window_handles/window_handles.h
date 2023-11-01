#pragma once
#include "../../Converters/converters.h"

struct WindowHandles
{
private:
    HDC *m_hdc_;
    HWND *m_hwnd_;
    
public:
    WindowHandles(HDC *hdc, HWND *hwnd);
    ~WindowHandles();

    HWND* HWND() const;
    HDC* HDC() const;
};
