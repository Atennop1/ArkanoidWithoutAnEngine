#include "shortcuts.h"

void Shortcuts::SelectColor(SDL_Renderer *renderer, const SDL_Color &color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}

