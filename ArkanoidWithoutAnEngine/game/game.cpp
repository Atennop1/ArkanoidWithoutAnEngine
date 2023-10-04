#include "game.h"
#include "levels/levels.h"
#include "shortcuts/shortcuts.h"

//----------------------------------------------------------------------------------------------------
void Game::OnKeyDown(KeyType key_type) const
{
    switch (key_type)
    {
    case kLeft:
        break;
        
    case kRight:
        break;
        
    case kSpace:
        break;
        
    case kNone:
        break;
    }
}

//----------------------------------------------------------------------------------------------------
Game::Game(WindowHandles *window_handles) 
{
    auto *violet_render_pack = new RenderPack(RGB(255, 85, 255));
    auto *blue_render_pack = new RenderPack(RGB(85, 255, 255));
    const HPEN white_pen = CreatePen(PS_SOLID, 3, RGB(255, 255, 255));

    m_window_handles_ = window_handles;
    m_level_view_ = new LevelView(*violet_render_pack, *blue_render_pack);
    m_platform_view_ = new PlatformView(m_window_handles_, violet_render_pack, blue_render_pack, white_pen);

    game_loop_ = new GameLoop();
    game_loop_->Add(m_platform_view_);
}

//----------------------------------------------------------------------------------------------------
void Game::Activate() const
{
    game_loop_->Activate();
}

//----------------------------------------------------------------------------------------------------
Game::~Game()
{
    free(m_level_view_);
    free(m_platform_view_);
    free(m_window_handles_);
}

//----------------------------------------------------------------------------------------------------
