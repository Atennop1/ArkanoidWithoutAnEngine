#pragma once
#include <array>
#include "Windows.h"

#include "../../DTOs/render_pack/render_pack.h"
#include "../../DTOs/Vector2/vector2.h"

class LevelView
{
private:
    const int kBrickWidth = 15;
    const int kBrickHeight = 7;

    const int kCellWidth = kBrickWidth + 1;
    const int kCellHeight = kBrickHeight + 1;

    const int kLevelOffsetX = 8;
    const int kLevelOffsetY = 6;
    
    RenderPack m_violet_render_pack_;
    RenderPack m_blue_render_pack_;

    void RenderBrick(HDC hdc, Vector2 position, RenderPack render_pack) const;
    
public:
    LevelView(RenderPack violet_render_pack, RenderPack blue_render_pack);
    void Render(HDC hdc, const std::array<std::array<char, 12>, 14> *level) const;
};

