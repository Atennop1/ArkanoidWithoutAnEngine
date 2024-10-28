#include "game/root/game.hpp"
#include "game/loop/time/average_game_time.hpp"
#include "game/rendering/screen_cleaner.hpp"
#include "game/rendering/screen_applier.hpp"
#include "game/events/input/input.hpp"
#include "game/platform/platform_view.hpp"
#include "game/platform/platform.hpp"
#include "game/platform/platform_controller.hpp"
#include "game/level/level_view.hpp"
#include "game/level/level.hpp"
#include "game/physics/physics_simulation.hpp"
#include "game/level/level_layouts.hpp"
#include "game/root/level_factory.hpp"
#include "game/ball/ball_view.hpp"
#include "game/ball/ball.hpp"
#include "game/wall/wall_view.hpp"
#include "game/wall/wall.hpp"
#include "game/root/wall_factory.hpp"

namespace arkanoid
{
Game::Game(const WindowReferences &window_references)
{
    auto game_time = SharedPointer<IReadOnlyGameTime>(new AverageGameTime());
    auto application_events = SharedPointer(new ApplicationEvents());
    game_loop_ = SharedPointer(new GameLoop(game_time, application_events));

    auto screen_cleaner = SharedPointer(new ScreenCleaner(window_references));
    auto screen_applier = SharedPointer(new ScreenApplier(window_references));
    auto physics_simulation = SharedPointer(new PhysicsSimulation());

    auto input = SharedPointer(new Input(application_events));
    auto platform_view = SharedPointer(new PlatformView(window_references));
    auto platform = SharedPointer(new Platform(PhysicalProperties { { 103.5, 150 }, { 28, 5 } }, platform_view));
    auto platform_controller = SharedPointer(new PlatformController(platform, input));
    physics_simulation->Add(platform);

    auto level_factory = LevelFactory();
    auto level_view = SharedPointer(new LevelView(window_references));
    auto level = SharedPointer(new Level(level_factory.CreateMap(LevelLayouts::First(), physics_simulation.Get()), level_view));

    auto ball_view = SharedPointer(new BallView(window_references));
    auto ball = SharedPointer(new Ball(PhysicalProperties { { 103.5, 100 }, { 4, 4 }, { -35, -35 } }, ball_view));
    physics_simulation->Add(ball);

    auto wall_factory = WallFactory();
    auto left_wall = wall_factory.CreateWall(window_references, "assets/sprites/left_wall.png", PhysicalProperties { { 4, 101 }, { 4, 200 } });
    auto up_wall = wall_factory.CreateWall(window_references, "assets/sprites/up_wall.png", PhysicalProperties { { 103, 3 }, { 200, 4 } });
    auto right_wall = wall_factory.CreateWall(window_references, "assets/sprites/right_wall.png", PhysicalProperties { { 202, 101 }, { 4, 200 } });
    physics_simulation->Add(left_wall);
    physics_simulation->Add(up_wall);
    physics_simulation->Add(right_wall);

    game_loop_->Add(application_events); // SYSTEM COMPONENT: gets all events from SDL2
    game_loop_->Add(physics_simulation); // SYSTEM COMPONENT: updates all physics before other logic
    game_loop_->Add(screen_cleaner); // SYSTEM COMPONENT: clearing all render that was before this line
    game_loop_->Add(input);
    game_loop_->Add(platform_controller);
    game_loop_->Add(platform);
    game_loop_->Add(level);
    game_loop_->Add(ball);
    game_loop_->Add(left_wall);
    game_loop_->Add(up_wall);
    game_loop_->Add(right_wall);
    game_loop_->Add(screen_applier); // SYSTEM COMPONENT: applies all render that was before this line
}

void Game::Activate()
{
    game_loop_->Activate();
}
}
