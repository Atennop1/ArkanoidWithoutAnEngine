#pragma once
#include "../../Converters/Converters.h"

struct WindowHandles
{
private:
    HDC *m_HDC;
    HWND *m_HWND;
    
public:
    WindowHandles(HDC *HDC, HWND *HWND);
    ~WindowHandles();

    HWND* HWND() const;
    
    HDC* HDC() const;
    void SetHDC(::HDC* hdc);
};
