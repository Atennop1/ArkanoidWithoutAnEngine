#include "application.hpp"

#include <memory>
#include "../../game/rendering/rendering_constants.hpp"

void Application::Activate() const
{
    SDL_Log("Application activated\n");
    m_game_->Activate();
}

Application::Application() : m_game_(nullptr), m_window_references_(nullptr)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window = SDL_CreateWindow("Popcorn", 0, 0, RenderingConstants::m_k_window_width_, RenderingConstants::m_k_window_height_, SDL_WINDOW_FULLSCREEN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    m_window_references_ = std::make_shared<WindowReferences>(*window, *renderer);
    m_game_ = std::make_unique<Game>(m_window_references_);
    SDL_Log("Application initialized\n");
}

Application::~Application()
{
    SDL_Log("Application cleared\n");
    SDL_DestroyWindow(m_window_references_->Window());
    SDL_DestroyRenderer(m_window_references_->Renderer());
    SDL_Quit();
}
