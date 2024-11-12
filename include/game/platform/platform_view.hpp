#ifndef ARKANOIDWITHOUTANENGINE_INCLUDE_GAME_PLATFORM_PLATFORM_VIEW_HPP_
#define ARKANOIDWITHOUTANENGINE_INCLUDE_GAME_PLATFORM_PLATFORM_VIEW_HPP_

#include <genesis/rendering/window_references.hpp>
#include <genesis/math/vector2.hpp>

namespace arkanoid
{
class PlatformView
{
public:
    explicit PlatformView(const genesis::WindowReferences &window_references);
    ~PlatformView();

    void Display(genesis::Vector2 position) const;

private:
    SDL_Texture *platform_texture_;
    genesis::WindowReferences window_references_;
};
}

#endif
