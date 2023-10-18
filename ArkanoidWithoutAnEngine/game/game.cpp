#include "game.h"
#include "platform/controller/platform_controller.h"
#include "shortcuts/shortcuts.h"
#include "view/screen_cleaner.h"
#include "view/level/level_view.h"

//----------------------------------------------------------------------------------------------------
Game::~Game()
{
    free(m_window_handles_);
    free(m_game_loop_);
}

//----------------------------------------------------------------------------------------------------
Game::Game(WindowHandles *window_handles) 
{
    m_window_handles_ = window_handles;
    const auto screen_cleaner = new ScreenCleaner(window_handles);
    
    const auto input = new Input();
    const auto platform_view = new PlatformView(m_window_handles_);
    const auto platform = new Platform(platform_view);
    const auto platform_controller = new PlatformController(input, platform);

    m_game_loop_ = new GameLoop();
    m_game_loop_->AddSystemUpdatable((ISystemUpdatable*)input);
    m_game_loop_->AddUpdatable((IUpdatable*)screen_cleaner);
    m_game_loop_->AddUpdatable((IUpdatable*)platform_controller);
}

//----------------------------------------------------------------------------------------------------
void Game::Activate() const
{
    m_game_loop_->Activate();
}

//----------------------------------------------------------------------------------------------------
