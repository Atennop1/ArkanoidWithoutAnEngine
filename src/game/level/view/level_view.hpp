#ifndef ARKANOIDWITHOUTANENGINE_1C6BD96ACE2042718FDD8457E44EFE5B
#define ARKANOIDWITHOUTANENGINE_1C6BD96ACE2042718FDD8457E44EFE5B

#include "../../rendering//window_references/window_references.hpp"
#include "../map/level_map.hpp"
#include "SDL.h"
#include "Box2D.hpp"

namespace arkanoid
{
    class LevelView
    {
    private:
        const float m_level_offset_x_ = 8.0f;
        const float m_level_offset_y_ = 6.0f;

        int m_brick_width_;
        int m_brick_height_;

        const WindowReferences &m_window_references_;
        SDL_Texture *m_violet_brick_texture_;
        SDL_Texture *m_blue_brick_texture_;

        void DisplayBrick(SDL_Texture *texture, box2d::Vector2 position) const;

    public:
        explicit LevelView(const WindowReferences &window_references);

        ~LevelView();

        void Display(const LevelMap &map) const;
    };
}

#endif
