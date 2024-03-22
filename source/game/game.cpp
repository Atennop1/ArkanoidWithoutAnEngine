#include "game.h"

#include <memory>
#include "platform/controller/platform_controller.h"
#include "rendering/screen_applier.h"
#include "rendering/screen_cleaner.h"
#include "level/level.h"
#include "level/constants/levels.h"
#include "loop/time/average_game_time.h"

Game::Game(const WindowReferences &window_references) : m_game_loop_(nullptr), m_game_time_(nullptr)
{
    auto screen_cleaner = new ScreenCleaner(window_references);
    auto screen_applier = new ScreenApplier(window_references);
    
    auto input = new Input();
    auto platform_view = new PlatformView(window_references);
    auto platform = new Platform(*platform_view);
    auto platform_controller = new PlatformController(*input, *platform);

    auto level_view = new LevelView(window_references);
    auto level = new Level(Levels::kFirst, *level_view);

    m_game_time_ = std::make_unique<AverageGameTime>();
    m_game_loop_ = std::make_unique<GameLoop>(*m_game_time_);

    m_game_loop_->AddEventsUpdatable(*input);
    m_game_loop_->AddUpdatable(*platform_controller);
    m_game_loop_->AddUpdatable(*screen_cleaner); // SYSTEM COMPONENT: clearing all render that was before this line
    m_game_loop_->AddUpdatable(*platform);
    m_game_loop_->AddUpdatable(*level);
    m_game_loop_->AddUpdatable(*screen_applier); // SYSTEM COMPONENT: applies all render that was before this line
    m_game_loop_->AddUpdatable(*input);
}

void Game::Activate() const
{
    m_game_loop_->Activate();
}

