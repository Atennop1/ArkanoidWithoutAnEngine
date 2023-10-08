#include "game.h"
#include "platform/controller/platform_controller.h"
#include "shortcuts/shortcuts.h"
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
    
    const auto violet_render_pack = new RenderPack(RGB(255, 85, 255));
    const auto blue_render_pack = new RenderPack(RGB(85, 255, 255));
    const HPEN white_pen = CreatePen(PS_SOLID, 3, RGB(255, 255, 255));

    const auto input = new Input();
    const auto platform_view = new PlatformView(m_window_handles_, violet_render_pack, blue_render_pack, white_pen);
    const auto platform = new Platform(platform_view);
    const auto platform_controller = new PlatformController(input, platform);

    m_game_loop_ = new GameLoop();
    m_game_loop_->Add((IUpdatable*)input);
    m_game_loop_->Add((IUpdatable*)platform_controller);
}

//----------------------------------------------------------------------------------------------------
void Game::Activate() const
{
    m_game_loop_->Activate();
}

//----------------------------------------------------------------------------------------------------
