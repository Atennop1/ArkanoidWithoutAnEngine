#include "game/ball/ball_view.hpp"
#include <genesis/shortcuts/shortcuts.hpp>
#include <SDL2/SDL_image.h>

namespace arkanoid
{
BallView::BallView(const genesis::WindowReferences &window_references) : window_references_(window_references)
{
    ball_texture_ = IMG_LoadTexture(window_references_.Renderer(), "assets/sprites/ball.png");
}

BallView::~BallView()
{
    SDL_DestroyTexture(ball_texture_);
}

void BallView::Display(genesis::Vector2 position) const
{
    SDL_FRect rect = genesis::Shortcuts::PositionAndTextureToRect(window_references_.Window(), position, ball_texture_, 6, 6);
    SDL_RenderCopyF(window_references_.Renderer(), ball_texture_, nullptr, &rect);
}
}
