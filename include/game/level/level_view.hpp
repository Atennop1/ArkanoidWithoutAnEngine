#ifndef ARKANOIDWITHOUTANENGINE_INCLUDE_GAME_LEVEL_LEVEL_VIEW_HPP_
#define ARKANOIDWITHOUTANENGINE_INCLUDE_GAME_LEVEL_LEVEL_VIEW_HPP_

#include "brick.hpp"
#include <genesis/rendering/window_references.hpp>
#include <genesis/memory/shared_pointer.hpp>
#include <SDL2/SDL_render.h>
#include <vector>

namespace arkanoid
{
class LevelView
{
public:
    explicit LevelView(const genesis::WindowReferences &window_references);
    ~LevelView();

    void Display(const std::vector<std::vector<genesis::SharedPointer<Brick>>>& map) const;

private:
    const genesis::WindowReferences &window_references_;
    SDL_Texture *violet_brick_texture_;
    SDL_Texture *blue_brick_texture_;
};
}

#endif
