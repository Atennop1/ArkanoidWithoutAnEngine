#include "tools/shortcuts/shortcuts.hpp"
#include "engine/rendering/rendering_constants.hpp"

namespace arkanoid
{
void Shortcuts::SelectColor(SDL_Renderer *renderer, const SDL_Color &color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}

SDL_Rect Shortcuts::PhysicalPropertiesToRect(PhysicalProperties properties)
{
    SDL_Rect rect;
    rect.x = properties.Left();
    rect.y = properties.Top();
    rect.w = properties.size.x;
    rect.h = properties.size.y;
    return rect;
}

SDL_Rect Shortcuts::PositionAndSizeToRect(Vector2 position, Vector2 size)
{
    SDL_Rect rect;
    rect.w = size.x;
    rect.h = size.y;
    rect.x = position.x - size.x / 2.0f;
    rect.y = position.y - size.y / 2.0f;
    return rect;
}

SDL_Rect Shortcuts::PositionAndTextureToRect(Vector2 position, SDL_Texture *texture)
{
    SDL_Rect rect = { };
    SDL_QueryTexture(texture, nullptr, nullptr, &rect.w, &rect.h);

    rect.h = rect.h * RenderingConstants::kScaleMultiplier;
    rect.w = rect.w * RenderingConstants::kScaleMultiplier;
    rect.x = position.x * RenderingConstants::kScaleMultiplier - rect.w / 2;
    rect.y = position.y * RenderingConstants::kScaleMultiplier - rect.h / 2;

    return rect;
}
}
