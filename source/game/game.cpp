﻿#include "game.h"
#include "platform/controller/platform_controller.h"
#include "rendering/screen_applier.h"
#include "rendering/screen_cleaner.h"
#include "level/level.h"
#include "level/constants/levels.h"

//----------------------------------------------------------------------------------------------------
Game::~Game()
{
    free(m_game_loop_);
}

//----------------------------------------------------------------------------------------------------
Game::Game(WindowReferences *window_references)
{
    const auto screen_cleaner = new ScreenCleaner(window_references);
    const auto screen_applier = new ScreenApplier(window_references);
    
    const auto input = new Input();
    const auto platform_view = new PlatformView(window_references);
    const auto platform = new Platform(platform_view);
    const auto platform_controller = new PlatformController(input, platform);

    const auto level_view = new LevelView(window_references);
    const auto level = new Level(Levels::kFirst, level_view);

    m_game_loop_ = new GameLoop();
    m_game_loop_->AddSystemUpdatable((ISystemUpdatable*)input);

    m_game_loop_->AddUpdatable((IUpdatable*)screen_cleaner); // SYSTEM COMPONENT: clearing all render that was before this line
    m_game_loop_->AddUpdatable((IUpdatable*)platform_controller);
    m_game_loop_->AddUpdatable((IUpdatable*)platform);
    m_game_loop_->AddUpdatable((IUpdatable*)level);
    m_game_loop_->AddUpdatable((IUpdatable*)screen_applier); // SYSTEM COMPONENT: applies all render that was before this line
}

//----------------------------------------------------------------------------------------------------
void Game::Activate() const
{
    m_game_loop_->Activate();
}

//----------------------------------------------------------------------------------------------------
