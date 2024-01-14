#pragma once
#include "../../Converters/converters.h"
#include "SDL.h"

struct WindowReferences
{
private:
    const SDL_Renderer &m_renderer_;
    const SDL_Window &m_window_;
    
public:
    WindowReferences(const SDL_Window &window, const SDL_Renderer &renderer);
    ~WindowReferences() = default;

    SDL_Window *Window() const;
    SDL_Renderer *Renderer() const;
};
