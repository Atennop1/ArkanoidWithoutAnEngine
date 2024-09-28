#ifndef ARKANOIDWITHOUTANENGINE_4F0478AC3E6C4928B8A168A9A7B13643
#define ARKANOIDWITHOUTANENGINE_4F0478AC3E6C4928B8A168A9A7B13643

#include "SDL.h"

namespace arkanoid
{
    struct WindowReferences
    {
    private:
        SDL_Renderer *m_renderer_;
        SDL_Window *m_window_;

    public:
        WindowReferences(SDL_Window *window, SDL_Renderer *renderer);

        SDL_Window *Window() const;

        SDL_Renderer *Renderer() const;
    };
}

#endif
