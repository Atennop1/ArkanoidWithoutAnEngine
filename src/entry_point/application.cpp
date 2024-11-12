#include "entry_point/application.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace arkanoid
{
Application::Application()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);

    SDL_Window *window = SDL_CreateWindow("Arkanoid Without An Engine", 0, 0, 320 * 6, 180 * 6, SDL_WINDOW_FULLSCREEN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    window_references_ = genesis::WindowReferences(window, renderer);
    m_game_ = genesis::SharedPointer(new Game(window_references_));
    SDL_Log("Application initialized\n");
}

Application::~Application()
{
    SDL_Log("Application cleared\n");
    IMG_Quit();
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