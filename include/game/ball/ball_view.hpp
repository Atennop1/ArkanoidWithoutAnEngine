#ifndef ARKANOIDWITHOUTANENGINE_INCLUDE_GAME_BALL_BALL_VIEW_HPP_
#define ARKANOIDWITHOUTANENGINE_INCLUDE_GAME_BALL_BALL_VIEW_HPP_

#include "genesis/math/vector2.hpp"
#include "genesis/rendering/window_references.hpp"
#include "SDL2/SDL.h"

namespace arkanoid
{
class BallView
{
public:
    explicit BallView(genesis::WindowReferences window_references);
    ~BallView();

    void Display(genesis::Vector2 position) const;

private:
    SDL_Texture *ball_texture_;
    genesis::WindowReferences window_references_;
};
}

#endif
