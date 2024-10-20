#ifndef ARKANOIDWITHOUTANENGINE_INCLUDE_GAME_RENDERING_WINDOW_REFERENCES_HPP_
#define ARKANOIDWITHOUTANENGINE_INCLUDE_GAME_RENDERING_WINDOW_REFERENCES_HPP_

#include "SDL.h"

namespace arkanoid
{
struct WindowReferences
{
public:
    WindowReferences(SDL_Window *window, SDL_Renderer *renderer);

    SDL_Window *Window() const;
    SDL_Renderer *Renderer() const;

private:
    SDL_Renderer *renderer;
    SDL_Window *window;
};
}

#endif
