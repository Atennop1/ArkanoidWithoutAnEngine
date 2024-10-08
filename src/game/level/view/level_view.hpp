#ifndef ARKANOIDWITHOUTANENGINE_SRC_GAME_LEVEL_VIEW_LEVEL_VIEW_HPP_
#define ARKANOIDWITHOUTANENGINE_SRC_GAME_LEVEL_VIEW_LEVEL_VIEW_HPP_

#include "../../rendering//window_references/window_references.hpp"
#include "../map/level_map.hpp"
#include "../../physics/vector2.hpp"
#include "SDL.h"

namespace arkanoid
{
    class LevelView
    {
    private:
        const float level_offset_x_ = 8.0f;
        const float level_offset_y_ = 6.0f;

        int brick_width_;
        int brick_height_;

        const WindowReferences &window_references_;
        SDL_Texture *violet_brick_texture_;
        SDL_Texture *blue_brick_texture_;

        void DisplayBrick(SDL_Texture *texture, arkanoid::Vector2 position) const;

    public:
        explicit LevelView(const WindowReferences &window_references);
        ~LevelView();

        void Display(const LevelMap &map) const;
    };
}

#endif
