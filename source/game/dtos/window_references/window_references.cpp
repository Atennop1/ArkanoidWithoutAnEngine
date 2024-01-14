#include "window_references.h"

WindowReferences::WindowReferences(const SDL_Window &window, const SDL_Renderer &renderer)
    : m_window_(window), m_renderer_(renderer) { }

SDL_Window *WindowReferences::Window() const
{
    return &(const_cast<SDL_Window&>(m_window_));
}

SDL_Renderer *WindowReferences::Renderer() const
{
    return &(const_cast<SDL_Renderer&>(m_renderer_));
}
