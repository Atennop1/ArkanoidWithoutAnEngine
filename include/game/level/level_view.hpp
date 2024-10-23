#ifndef ARKANOIDWITHOUTANENGINE_INCLUDE_GAME_LEVEL_LEVEL_VIEW_HPP_
#define ARKANOIDWITHOUTANENGINE_INCLUDE_GAME_LEVEL_LEVEL_VIEW_HPP_

#include "game/rendering/window_references.hpp"
#include "game/math/vector2.hpp"
#include "brick.hpp"
#include "tools/shared_pointer.hpp"
#include "SDL.h"
#include <vector>

namespace arkanoid
{
class LevelView
{
public:
    explicit LevelView(const WindowReferences &window_references);
    ~LevelView();

    void Display(const std::vector<std::vector<SharedPointer<Brick>>>& map) const;

private:
    /*
    const float level_offset_x_ = 93.0f;
    const float level_offset_y_ = 36.0f;

    int brick_width_;
    int brick_height_;
    */

    const WindowReferences &window_references_;
    SDL_Texture *violet_brick_texture_;
    SDL_Texture *blue_brick_texture_;
};
}

#endif
