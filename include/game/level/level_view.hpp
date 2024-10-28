#ifndef ARKANOIDWITHOUTANENGINE_INCLUDE_GAME_LEVEL_LEVEL_VIEW_HPP_
#define ARKANOIDWITHOUTANENGINE_INCLUDE_GAME_LEVEL_LEVEL_VIEW_HPP_

#include "brick.hpp"
#include "tools/shared_pointer.hpp"
#include "SDL.h"
#include "engine/rendering/window_references.hpp"
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
    const WindowReferences &window_references_;
    SDL_Texture *violet_brick_texture_;
    SDL_Texture *blue_brick_texture_;
};
}

#endif
