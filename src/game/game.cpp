#include "game.hpp"
#include "level/constants/level_maps.hpp"
#include "loop/game_loop.hpp"
#include "physics/physics_simulation.hpp"
#include "level/level.hpp"
#include "level/view/level_view.hpp"
#include "loop/time/average_game_time.hpp"
#include "rendering/screen_cleaner.hpp"
#include "rendering/screen_applier.hpp"
#include "input/input.hpp"
#include "platform/view/platform_view.hpp"
#include "platform/model/platform.hpp"
#include "platform/controller/platform_controller.hpp"

Game::Game(const WindowReferences &window_references)
{
    auto game_time = SharedPointer<IReadOnlyGameTime>(new AverageGameTime());
    auto world = SharedPointer(new Box2D::World(Box2D::Vector2(0.0f, -10.0f)));

    m_game_loop_ = SharedPointer(new GameLoop(game_time));
    auto physics_simulation = SharedPointer(new PhysicsSimulation(world));

    auto screen_cleaner = SharedPointer(new ScreenCleaner(window_references));
    auto screen_applier = SharedPointer(new ScreenApplier(window_references));

    auto input = SharedPointer(new Input());
    auto platform_view = SharedPointer(new PlatformView(window_references));
    auto platform = SharedPointer(new Platform(platform_view));
    auto platform_controller = SharedPointer(new PlatformController(platform, input));

    auto level_view = SharedPointer(new LevelView(window_references));
    auto level = SharedPointer(new Level(LevelMaps::First(), level_view));

    m_game_loop_->AddObject(physics_simulation); // SYSTEM COMPONENT: updates all physics before other logic
    m_game_loop_->AddObject(screen_cleaner); // SYSTEM COMPONENT: clearing all render that was before this line
    m_game_loop_->AddEventsObject(input);
    m_game_loop_->AddObject(platform);
    m_game_loop_->AddObject(platform_controller);
    m_game_loop_->AddObject(level);
    m_game_loop_->AddObject(screen_applier); // SYSTEM COMPONENT: applies all render that was before this line
    m_game_loop_->AddObject(input);
}

void Game::Activate()
{
    m_game_loop_->Activate();
}
