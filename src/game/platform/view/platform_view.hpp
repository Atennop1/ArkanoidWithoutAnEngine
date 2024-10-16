#ifndef ARKANOIDWITHOUTANENGINE_SRC_GAME_PLATFORM_VIEW_PLATFORM_VIEW_HPP_
#define ARKANOIDWITHOUTANENGINE_SRC_GAME_PLATFORM_VIEW_PLATFORM_VIEW_HPP_

#include "../../rendering/window_references/window_references.hpp"
#include "../../math/vector2.hpp"

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
