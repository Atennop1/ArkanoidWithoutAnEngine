#ifndef ARKANOIDWITHOUTANENGINE_B3FAD715A0DD444798232F8F184E5090
#define ARKANOIDWITHOUTANENGINE_B3FAD715A0DD444798232F8F184E5090

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

#endif //ARKANOIDWITHOUTANENGINE_B3FAD715A0DD444798232F8F184E5090
