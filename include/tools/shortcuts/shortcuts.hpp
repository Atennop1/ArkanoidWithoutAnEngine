#ifndef ARKANOIDWITHOUTANENGINE_INCLUDE_TOOLS_SHORTCUTS_SHORTCUTS_HPP_
#define ARKANOIDWITHOUTANENGINE_INCLUDE_TOOLS_SHORTCUTS_SHORTCUTS_HPP_

#include "SDL.h"
#include "engine/physics/physical_properties.hpp"
#include "engine/rendering/rendering_constants.hpp"

namespace arkanoid
{
class Shortcuts
{
public:
    static void SelectColor(SDL_Renderer *renderer, const SDL_Color &color);

    static SDL_FRect PhysicalPropertiesToRect(PhysicalProperties properties);
    static SDL_FRect PositionAndSizeToRect(Vector2 position, Vector2 size);
    static SDL_FRect PositionAndTextureToRect(Vector2 position, SDL_Texture *texture, float position_multiplier = RenderingConstants::kScaleMultiplier, float size_multiplier = RenderingConstants::kScaleMultiplier);
};
}

#endif
