#include "game.hpp"
#include "level/constants/level_maps.hpp"
#include "loop/logic/game_logic_loop.hpp"
#include "loop/physics/game_physics_loop.hpp"
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

    auto loops = std::vector<SharedPointer<IGameLoop>> { };
    auto game_logic_loop = SharedPointer(new GameLogicLoop(game_time));
    auto game_physics_loop = SharedPointer(new GamePhysicsLoop(world, game_time));

    auto screen_cleaner = SharedPointer(new ScreenCleaner(window_references));
    auto screen_applier = SharedPointer(new ScreenApplier(window_references));

    auto input = SharedPointer(new Input());
    auto platform_view = SharedPointer(new PlatformView(window_references));
    auto platform = SharedPointer(new Platform(platform_view));
    auto platform_controller = SharedPointer(new PlatformController(platform, input));

    auto level_view = SharedPointer(new LevelView(window_references));
    auto level = SharedPointer(new Level(LevelMaps::First(), level_view));

    game_logic_loop->AddUpdatable(screen_cleaner); // SYSTEM COMPONENT: clearing all render that was before this line
    game_logic_loop->AddEventsUpdatable(input);
    game_logic_loop->AddUpdatable(platform);
    game_logic_loop->AddUpdatable(platform_controller);
    game_logic_loop->AddUpdatable(level);
    game_logic_loop->AddUpdatable(screen_applier); // SYSTEM COMPONENT: applies all render that was before this line
    game_logic_loop->AddUpdatable(input);

    loops.push_back(game_physics_loop);
    loops.push_back(game_logic_loop);
    m_game_loops_ = SharedPointer(new GameLoops(loops));
}

void Game::Activate()
{
    m_game_loops_->Activate();
}
