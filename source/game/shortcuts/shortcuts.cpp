#include "shortcuts.h"
#include <cwchar>
#include "Windows.h"

//----------------------------------------------------------------------------------------------------
void Shortcuts::SelectRenderPack(HDC hdc, RenderPack render_pack)
{
    SelectObject(hdc, render_pack.Pen());
    SelectObject(hdc, render_pack.Brush());
}

//----------------------------------------------------------------------------------------------------
void Shortcuts::PrintDebugString(const wchar_t *string, ...)
{
    va_list args;
    va_start(args, string);
    wchar_t char_buffer[256];
    
    vswprintf(char_buffer, 256, string, args);
    OutputDebugString(char_buffer);
    va_end(args);
}

//----------------------------------------------------------------------------------------------------
