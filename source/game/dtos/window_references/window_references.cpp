#include "window_references.h"

WindowReferences::WindowReferences(SDL_Window &window, SDL_Renderer &renderer)
    : m_window_(window), m_renderer_(renderer) { }

SDL_Window *WindowReferences::Window() const
{
    return &m_window_;
}

SDL_Renderer *WindowReferences::Renderer() const
{
    return &m_renderer_;
}
