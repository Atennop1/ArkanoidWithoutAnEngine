#include "game.hpp"
#include "level/constants/level_maps.hpp"
#include "loop/game_loop.hpp"
#include "physics/physics_simulation.hpp"
#include "level/level.hpp"
#include "level/view/level_view.hpp"
#include "loop/time/average_game_time.hpp"
#include "rendering/screen_cleaner.hpp"
#include "rendering/screen_applier.hpp"
#include "platform/view/platform_view.hpp"
#include "platform/model/platform.hpp"
#include "platform/controller/platform_controller.hpp"
#include "events/input/input.hpp"
#include "physics/test_object.hpp"

namespace arkanoid
{
Game::Game(const WindowReferences &window_references)
{
    auto game_time = SharedPointer<IReadOnlyGameTime>(new AverageGameTime());
    auto application_events = SharedPointer(new ApplicationEvents());
    game_loop_ = SharedPointer(new GameLoop(game_time, application_events));

    auto collision_detector = SharedPointer(new CollisionDetector());
    auto collision_solver = SharedPointer(new CollisionSolver());
    auto physics_simulation = SharedPointer(new PhysicsSimulation(collision_detector, collision_solver));

    auto screen_cleaner = SharedPointer(new ScreenCleaner(window_references));
    auto screen_applier = SharedPointer(new ScreenApplier(window_references));

    auto input = SharedPointer(new Input(application_events));
    auto platform_view = SharedPointer(new PlatformView(window_references));
    auto platform = SharedPointer(new Platform(platform_view));
    auto platform_controller = SharedPointer(new PlatformController(platform, input));

    auto level_view = SharedPointer(new LevelView(window_references));
    auto level = SharedPointer(new Level(LevelMaps::First(), level_view));

    auto test_object = SharedPointer(new TestObject(window_references));
    test_object->SetPosition(Vector2(500, 500));
    test_object->SetSize(Vector2(50, 50));
    test_object->SetVelocity(Vector2(10, 10));
    test_object->SetAcceleration(Vector2(5, 5));
    physics_simulation->Add(test_object);

    game_loop_->Add(application_events); // SYSTEM COMPONENT: gets all events from SDL2
    game_loop_->Add(physics_simulation); // SYSTEM COMPONENT: updates all physics before other logic
    game_loop_->Add(screen_cleaner); // SYSTEM COMPONENT: clearing all render that was before this line
    game_loop_->Add(input);
    game_loop_->Add(platform_controller);
    game_loop_->Add(platform);
    game_loop_->Add(level);
    game_loop_->Add(test_object);
    game_loop_->Add(screen_applier); // SYSTEM COMPONENT: applies all render that was before this line
}

void Game::Activate()
{
    game_loop_->Activate();
}
}
