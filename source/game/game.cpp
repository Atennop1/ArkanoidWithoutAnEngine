#include "game.h"
#include "platform/controller/platform_controller.h"
#include "rendering/screen_applier.h"
#include "rendering/screen_cleaner.h"
#include "level/level.h"
#include "level/constants/levels.h"
#include "loop/time/average_game_time.h"

Game::Game(const WindowReferences &window_references)
{
    auto screen_cleaner = ScreenCleaner(window_references);
    auto screen_applier = ScreenApplier(window_references);
    
    auto input = Input();
    auto platform_view = PlatformView(window_references);
    auto platform = Platform(platform_view);
    const auto platform_controller = PlatformController(input, platform);

    auto level_view = LevelView(window_references);
    auto level = Level(Levels::kFirst, level_view);

    auto average_game_time = AverageGameTime();
    m_game_loop_ = new GameLoop((IReadOnlyGameTime&)average_game_time);

    m_game_loop_->AddEventsUpdatable((IEventsUpdatable&)input);
    m_game_loop_->AddUpdatable((IUpdatable&)platform_controller);
    m_game_loop_->AddUpdatable((IUpdatable&)screen_cleaner); // SYSTEM COMPONENT: clearing all render that was before this line
    m_game_loop_->AddUpdatable((IUpdatable&)platform);
    m_game_loop_->AddUpdatable((IUpdatable&)level);
    m_game_loop_->AddUpdatable((IUpdatable&)screen_applier); // SYSTEM COMPONENT: applies all render that was before this line
    m_game_loop_->AddUpdatable((IUpdatable&)input);
}

void Game::Activate() const
{
    m_game_loop_.Activate();
}

