#include "game/ball/ball_view.hpp"
#include "tools/shortcuts/shortcuts.hpp"
#include <SDL_image.h>

namespace arkanoid
{
BallView::BallView(const arkanoid::WindowReferences &window_references) : window_references_(window_references)
{
    ball_texture_ = IMG_LoadTexture(window_references_.Renderer(), "assets/sprites/ball.png");
}

BallView::~BallView()
{
    SDL_DestroyTexture(ball_texture_);
}

void BallView::Display(Vector2 position) const
{
    SDL_Rect rect = Shortcuts::PositionAndTextureToRect(position, ball_texture_);
    SDL_RenderCopy(window_references_.Renderer(), ball_texture_, nullptr, &rect);
}
}
