#include "application.hpp"

#include <memory>
#include "../../game/rendering/rendering_constants.hpp"

void Application::Activate()
{
    SDL_Log("Application activated\n");
    m_game_->Activate();
}

Application::Application()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window = SDL_CreateWindow("Popcorn", 0, 0, RenderingConstants::m_k_window_width_, RenderingConstants::m_k_window_height_, SDL_WINDOW_FULLSCREEN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    m_window_references_ = WindowReferences(window, renderer);
    m_game_ = SharedPointer(new Game(m_window_references_));
    SDL_Log("Application initialized\n");
}

Application::~Application()
{
    SDL_Log("Application cleared\n");
    SDL_DestroyWindow(m_window_references_.Window());
    SDL_DestroyRenderer(m_window_references_.Renderer());
    SDL_Quit();
}
