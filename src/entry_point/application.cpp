#include "entry_point/application.hpp"
#include "engine/rendering/rendering_constants.hpp"

namespace arkanoid
{
Application::Application()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window = SDL_CreateWindow("Popcorn", 0, 0, RenderingConstants::kWindowWidth, RenderingConstants::kWindowHeight, SDL_WINDOW_FULLSCREEN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    window_references_ = WindowReferences(window, renderer);
    m_game_ = SharedPointer(new Game(window_references_));
    SDL_Log("Application initialized\n");
}

Application::~Application()
{
    SDL_Log("Application cleared\n");
    SDL_DestroyWindow(window_references_.Window());
    SDL_DestroyRenderer(window_references_.Renderer());
    SDL_Quit();
}

void Application::Activate()
{
    SDL_Log("Application activated\n");
    m_game_->Activate();
}
}