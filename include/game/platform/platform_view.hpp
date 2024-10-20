#ifndef ARKANOIDWITHOUTANENGINE_INCLUDE_GAME_PLATFORM_PLATFORM_VIEW_HPP_
#define ARKANOIDWITHOUTANENGINE_INCLUDE_GAME_PLATFORM_PLATFORM_VIEW_HPP_

#include "game/rendering/window_references.hpp"
#include "game/math/vector2.hpp"

namespace arkanoid
{
class PlatformView
{
public:
    explicit PlatformView(const WindowReferences &window_references);
    ~PlatformView();

    void Display(Vector2 position) const;

private:
    SDL_Texture *platform_texture_;
    const WindowReferences &window_references_;
};
}

#endif
