#include "shortcuts.h"
#include "Windows.h"

//----------------------------------------------------------------------------------------------------
void Shortcuts::SelectRenderPack(HDC hdc, RenderPack render_pack)
{
    SelectObject(hdc, render_pack.Pen());
    SelectObject(hdc, render_pack.Brush());
}

//----------------------------------------------------------------------------------------------------
