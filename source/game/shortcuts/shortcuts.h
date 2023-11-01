#pragma once

#include "Windows.h"
#include "../DTOs/render_pack/render_pack.h"

class Shortcuts
{
public:
    static void PrintDebugString(const wchar_t *string, ...);
    static void SelectRenderPack(HDC hdc, RenderPack render_pack);
};



