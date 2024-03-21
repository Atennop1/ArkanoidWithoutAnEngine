#include "game.h"

#include <memory>
#include "platform/controller/platform_controller.h"
#include "rendering/screen_applier.h"
#include "rendering/screen_cleaner.h"
#include "level/level.h"
#include "level/constants/levels.h"
#include "loop/time/average_game_time.h"

Game::Game(const WindowReferences &window_references) : m_game_loop_(nullptr)
{
    auto screen_cleaner = ScreenCleaner(window_references);
    auto screen_applier = ScreenApplier(window_references);
    
    auto input = Input();
    auto platform_view = PlatformView(window_references);
    auto platform = Platform(platform_view);
    auto platform_controller = PlatformController(input, platform);

    auto level_view = LevelView(window_references);
    auto level = Level(Levels::kFirst, level_view);

    auto average_game_time = AverageGameTime();
    m_game_loop_ = std::make_unique<GameLoop>(average_game_time);

    m_game_loop_->AddEventsUpdatable(input);
    m_game_loop_->AddUpdatable(platform_controller);
    m_game_loop_->AddUpdatable(screen_cleaner); // SYSTEM COMPONENT: clearing all render that was before this line
    m_game_loop_->AddUpdatable(platform);
    m_game_loop_->AddUpdatable(level);
    m_game_loop_->AddUpdatable(screen_applier); // SYSTEM COMPONENT: applies all render that was before this line
    m_game_loop_->AddUpdatable(input);
}

void Game::Activate() const
{
    m_game_loop_->Activate();
}

