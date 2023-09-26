#pragma once

#include <array>
#include "Windows.h"
#include "../../DTOs/RenderPack/RenderPack.h"
#include "../../DTOs/Vector2/Vector2.h"

class LevelRenderer
{
private:
    const int BRICK_WIDTH = 15;
    const int BRICK_HEIGHT = 7;

    const int CELL_WIDTH = BRICK_WIDTH + 1;
    const int CELL_HEIGHT = BRICK_HEIGHT + 1;

    const int LEVEL_OFFSET_X = 8;
    const int LEVEL_OFFSET_Y = 6;
    
    RenderPack m_violetRenderPack;
    RenderPack m_blueRenderPack;

    void RenderBrick(HDC hdc, Vector2 position, RenderPack renderPack) const;
    
public:
    LevelRenderer(RenderPack violetRenderPack, RenderPack blueRenderPack);
    void Render(HDC hdc, const std::array<std::array<char, 12>, 14> *level) const;
};

