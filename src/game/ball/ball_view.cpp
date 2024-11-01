#include <SDL2/SDL_image.h>
#include "game/ball/ball_view.hpp"
#include "genesis/shortcuts/shortcuts.hpp"

namespace arkanoid
{
BallView::BallView(genesis::WindowReferences window_references) : window_references_(window_references)
{
    ball_texture_ = IMG_LoadTexture(window_references_.Renderer(), "assets/sprites/ball.png");
}

BallView::~BallView()
{
    SDL_DestroyTexture(ball_texture_);
}

void BallView::Display(genesis::Vector2 position) const
{
    SDL_FRect rect = genesis::Shortcuts::PositionAndTextureToRect(position, ball_texture_, 6, 6);
    SDL_RenderCopyF(window_references_.Renderer(), ball_texture_, nullptr, &rect);
}
}
