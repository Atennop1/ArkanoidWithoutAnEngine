#pragma once
#include "../../Converters/converters.h"
#include "SDL.h"

struct WindowReferences
{
private:
    SDL_Renderer *m_renderer_;
    SDL_Window *m_window_;
    
public:
    WindowReferences(SDL_Window *window, SDL_Renderer *renderer);
    ~WindowReferences() = default;

    SDL_Window *Window() const;
    SDL_Renderer *Renderer() const;
};
