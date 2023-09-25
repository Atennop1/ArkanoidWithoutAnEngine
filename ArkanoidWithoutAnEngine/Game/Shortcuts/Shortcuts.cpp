#include "Shortcuts.h"
#include "Windows.h"

//----------------------------------------------------------------------------------------------------
void Shortcuts::SelectRenderPack(HDC hdc, RenderPack renderPack)
{
    SelectObject(hdc, renderPack.Pen());
    SelectObject(hdc, renderPack.Brush());
}

//----------------------------------------------------------------------------------------------------
