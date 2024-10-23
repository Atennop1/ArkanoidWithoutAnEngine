#include "game/level/level_view.hpp"
#include "game/shortcuts/shortcuts.hpp"
#include "SDL_image.h"

namespace arkanoid
{
LevelView::LevelView(const WindowReferences &window_references) : window_references_(window_references)
{
    blue_brick_texture_ = IMG_LoadTexture(window_references_.Renderer(), "assets/sprites/blue_brick.png");
    violet_brick_texture_ = IMG_LoadTexture(window_references_.Renderer(), "assets/sprites/violet_brick.png");
}

LevelView::~LevelView()
{
    SDL_DestroyTexture(blue_brick_texture_);
    SDL_DestroyTexture(violet_brick_texture_);
}

void LevelView::Display(const std::vector<std::vector<SharedPointer<Brick>>>& map) const
{
    for (auto line : map)
    {
        for (auto brick : line)
        {
            if (brick->Type() == BrickType::kNone || brick->IsDestroyed())
                continue;

            SDL_Texture *texture = brick->Type() == BrickType::kViolet ? violet_brick_texture_ : blue_brick_texture_;
            SDL_Rect rect = Shortcuts::PhysicalPropertiesToRect(brick->Properties());
            SDL_RenderCopy(window_references_.Renderer(), texture, nullptr, &rect);
        }
    }
}
}
