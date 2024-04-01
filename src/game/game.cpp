﻿#include "game.hpp"

#include <memory>
#include "platform/controller/platform_controller.hpp"
#include "rendering/screen_applier.hpp"
#include "rendering/screen_cleaner.hpp"
#include "level/level.hpp"
#include "level/constants/level_maps.hpp"
#include "loop/time/average_game_time.hpp"

Game::Game(const std::shared_ptr<WindowReferences> &window_references) : m_game_loop_(nullptr), m_game_time_(nullptr)
{
    m_game_time_ = std::make_shared<AverageGameTime>();
    m_game_loop_ = std::make_unique<GameLogicLoop>(m_game_time_);

    auto screen_cleaner = std::make_unique<ScreenCleaner>(window_references);
    m_game_loop_->AddUpdatable(std::move(screen_cleaner)); // SYSTEM COMPONENT: clearing all render that was before this line
    
    auto input = std::make_shared<Input>();
    m_game_loop_->AddEventsUpdatable(*input);

    auto platform_view = std::make_unique<PlatformView>(window_references);
    auto platform = std::make_unique<Platform>(std::move(platform_view));
    m_game_loop_->AddUpdatable(*platform);
    auto platform_controller = std::make_unique<PlatformController>(input, platform);
    m_game_loop_->AddUpdatable(std::move(platform_controller));

    auto level_view = std::make_unique<LevelView>(window_references);
    auto level = std::make_unique<Level>(std::move(LevelMaps::First()), std::move(level_view));
    m_game_loop_->AddUpdatable(std::move(level));

    auto screen_applier = std::make_unique<ScreenApplier>(window_references);
    m_game_loop_->AddUpdatable(std::move(screen_applier)); // SYSTEM COMPONENT: applies all render that was before this line
    m_game_loop_->AddUpdatable(*input);
}

void Game::Activate() const
{
    m_game_loop_->Activate();
}