#pragma once

#include "Windows.h"
#include "../DTOs/render_pack/render_pack.h"

class Shortcuts
{
public:
    static void SelectRenderPack(HDC hdc, RenderPack render_pack);
};
