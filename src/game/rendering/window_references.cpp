#include "game/rendering/window_references.hpp"

namespace arkanoid
{
WindowReferences::WindowReferences(SDL_Window *window, SDL_Renderer *renderer)
    : window(window), renderer(renderer) { }

SDL_Window *WindowReferences::Window() const
{
    return window;
}

SDL_Renderer *WindowReferences::Renderer() const
{
    return renderer;
}
}