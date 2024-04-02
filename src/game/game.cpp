#include "game.hpp"

#include <memory>
#include "platform/controller/platform_controller.hpp"
#include "rendering/screen_applier.hpp"
#include "rendering/screen_cleaner.hpp"
#include "level/level.hpp"
#include "level/constants/level_maps.hpp"
#include "loop/time/average_game_time.hpp"
#include "loop/logic/game_logic_loop.hpp"
#include "loop/game_loops.hpp"
#include "loop/physics/game_physics_loop.hpp"

Game::Game(const std::shared_ptr<WindowReferences> &window_references) : m_game_loops_(nullptr)
{
    std::shared_ptr<IReadOnlyGameTime> game_time = std::make_shared<AverageGameTime>();
    std::shared_ptr<Box2D::World> world = std::make_unique<Box2D::World>(Box2D::Vec2(0.0f, -10.0f));

    std::vector<std::unique_ptr<IGameLoop>> loops { };
    std::unique_ptr<GameLogicLoop> game_logic_loop = std::make_unique<GameLogicLoop>(game_time);
    std::unique_ptr<GamePhysicsLoop> game_physics_loop = std::make_unique<GamePhysicsLoop>(world, game_time);

    auto screen_cleaner = std::make_unique<ScreenCleaner>(window_references);
    game_logic_loop->AddUpdatable(std::move(screen_cleaner)); // SYSTEM COMPONENT: clearing all render that was before this line
    
    auto input = std::make_shared<Input>();
    game_logic_loop->AddEventsUpdatable(*input);

    auto platform_view = std::make_unique<PlatformView>(window_references);
    auto platform = std::make_unique<Platform>(platform_view);
    game_logic_loop->AddUpdatable(*platform);
    auto platform_controller = std::make_unique<PlatformController>(input, platform);
    game_logic_loop->AddUpdatable(std::move(platform_controller));

    auto level_view = std::make_unique<LevelView>(window_references);
    auto level = std::make_unique<Level>(LevelMaps::First(), level_view);
    game_logic_loop->AddUpdatable(std::move(level));

    auto screen_applier = std::make_unique<ScreenApplier>(window_references);
    game_logic_loop->AddUpdatable(std::move(screen_applier)); // SYSTEM COMPONENT: applies all render that was before this line
    game_logic_loop->AddUpdatable(*input);

    loops.push_back(std::move(game_logic_loop));
    loops.push_back(std::move(game_physics_loop));
    m_game_loops_ = std::make_unique<GameLoops>(loops);
}

void Game::Activate() const
{
    m_game_loops_->Activate();
}
