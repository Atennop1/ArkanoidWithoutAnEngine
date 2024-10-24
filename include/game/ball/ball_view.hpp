#ifndef ARKANOIDWITHOUTANENGINE_INCLUDE_GAME_BALL_BALL_VIEW_HPP_
#define ARKANOIDWITHOUTANENGINE_INCLUDE_GAME_BALL_BALL_VIEW_HPP_

#include "game/rendering/window_references.hpp"
#include "game/math/vector2.hpp"

namespace arkanoid
{
class BallView
{
public:
    explicit BallView(const WindowReferences &window_references);
    ~BallView();

    void Display(Vector2 position) const;

private:
    SDL_Texture *ball_texture_;
    const WindowReferences &window_references_;
};
}

#endif
