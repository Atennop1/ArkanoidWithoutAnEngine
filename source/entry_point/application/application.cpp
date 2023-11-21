#include <iostream>
#include "application.h"
#include "../../game/rendering/rendering_constants.h"

//----------------------------------------------------------------------------------------------------
void Application::Activate() const
{
    m_game_->Activate();
    SDL_Log("Application activated\n");
}

//----------------------------------------------------------------------------------------------------
Application::Application()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window = SDL_CreateWindow("Popcorn", 0, 0, RenderingConstants::kWindowWidth, RenderingConstants::kWindowHeight, SDL_WINDOW_FULLSCREEN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    m_window_references_ = new WindowReferences(window, renderer);
    m_game_ = new Game(m_window_references_);
    SDL_Log("Application initialized\n");
}

//----------------------------------------------------------------------------------------------------
Application::~Application()
{
    SDL_DestroyWindow(m_window_references_->Window());
    SDL_DestroyRenderer(m_window_references_->Renderer());
    SDL_Quit();

    free(m_game_);
    free(m_window_references_);
    SDL_Log("Application cleared\n");
}

//----------------------------------------------------------------------------------------------------
