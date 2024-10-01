#ifndef ARKANOIDWITHOUTANENGINE_SRC_GAME_PLATFORM_VIEW_PLATFORM_VIEW_HPP_
#define ARKANOIDWITHOUTANENGINE_SRC_GAME_PLATFORM_VIEW_PLATFORM_VIEW_HPP_

#include "../../rendering/window_references/window_references.hpp"
#include "Box2D.hpp"

namespace arkanoid
{
    class PlatformView
    {
    private:
        SDL_Texture *platform_texture_;
        const WindowReferences &window_references_;

    public:
        explicit PlatformView(const WindowReferences &window_references);
        ~PlatformView();

        void Display(box2d::Vector2 position) const;
    };
}

#endif
