#ifndef ARKANOIDWITHOUTANENGINE_B3FAD715A0DD444798232F8F184E5090
#define ARKANOIDWITHOUTANENGINE_B3FAD715A0DD444798232F8F184E5090

#include "../../Converters/converters.h"
#include "SDL.h"

struct WindowReferences
{
private:
    SDL_Renderer *m_renderer_;
    SDL_Window *m_window_;

public:
    WindowReferences(SDL_Window &window, SDL_Renderer &renderer);

    SDL_Window *Window() const;
    SDL_Renderer *Renderer() const;
};

#endif
