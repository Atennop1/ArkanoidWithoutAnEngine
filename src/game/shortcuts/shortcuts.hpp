#ifndef ARKANOIDWITHOUTANENGINE_SRC_GAME_SHORTCUTS_SHORTCUTS_HPP_
#define ARKANOIDWITHOUTANENGINE_SRC_GAME_SHORTCUTS_SHORTCUTS_HPP_

#include "SDL.h"

namespace arkanoid
{
class Shortcuts
{
public:
    static void SelectColor(SDL_Renderer *renderer, const SDL_Color &color);
};
}

#endif
