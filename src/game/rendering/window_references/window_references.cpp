#include "window_references.hpp"

arkanoid::WindowReferences::WindowReferences(SDL_Window *window, SDL_Renderer *renderer)
    : window(window), renderer(renderer) { }

SDL_Window *arkanoid::WindowReferences::Window() const
{
    return window;
}

SDL_Renderer *arkanoid::WindowReferences::Renderer() const
{
    return renderer;
}
