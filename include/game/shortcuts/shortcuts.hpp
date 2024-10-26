#ifndef ARKANOIDWITHOUTANENGINE_INCLUDE_GAME_SHORTCUTS_SHORTCUTS_HPP_
#define ARKANOIDWITHOUTANENGINE_INCLUDE_GAME_SHORTCUTS_SHORTCUTS_HPP_

#include "SDL.h"
#include "game/physics/physical_properties.hpp"

namespace arkanoid
{
class Shortcuts
{
public:
    static void SelectColor(SDL_Renderer *renderer, const SDL_Color &color);

    static SDL_Rect PhysicalPropertiesToRect(PhysicalProperties properties);
    static SDL_Rect PositionAndSizeToRect(Vector2 position, Vector2 size);
    static SDL_Rect PositionAndTextureToRect(Vector2 position, SDL_Texture *texture);
};
}

#endif
