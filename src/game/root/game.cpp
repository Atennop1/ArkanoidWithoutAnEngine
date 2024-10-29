#include "game/root/game.hpp"
#include "engine/loop/time/average_game_time.hpp"
#include "engine/rendering/screen_cleaner.hpp"
#include "engine/rendering/screen_applier.hpp"
#include "engine/events/input/input.hpp"
#include "engine/physics/physics_simulation.hpp"
#include "game/platform/platform_view.hpp"
#include "game/platform/platform.hpp"
#include "game/platform/platform_controller.hpp"
#include "game/level/level_view.hpp"
#include "game/level/level.hpp"
#include "game/level/level_layouts.hpp"
#include "game/root/level_factory.hpp"
#include "game/ball/ball_view.hpp"
#include "game/ball/ball.hpp"
#include "game/root/wall_factory.hpp"

namespace arkanoid
{
Game::Game(const WindowReferences &window_references)
{
    auto game_time = SharedPointer<IReadOnlyGameTime>(new AverageGameTime());
    auto application_events = SharedPointer(new ApplicationEvents());
    game_loop_ = SharedPointer(new GameLoop(game_time, application_events));

    auto screen_cleaner = SharedPointer(new ScreenCleaner(window_references));
    auto physics_simulation = SharedPointer(new PhysicsSimulation());
    auto input = SharedPointer(new Input(application_events));

    game_loop_->Add(application_events); // SYSTEM COMPONENT: gets all events from SDL2
    game_loop_->Add(physics_simulation); // SYSTEM COMPONENT: updates all physics before other logic
    game_loop_->Add(screen_cleaner); // SYSTEM COMPONENT: clearing all render that was before this line
    game_loop_->Add(input); // SYSTEM COMPONENT: reading input from OS

    // GAME LOGIC PART
    // -----------------------------------------------------------------------------------------------------------------

    auto platform_view = SharedPointer(new PlatformView(window_references));
    auto platform = SharedPointer(new Platform(PhysicalProperties { { 55 + 103.5, 150 }, { 28, 5 } }, platform_view));
    auto platform_controller = SharedPointer(new PlatformController(platform, input));
    physics_simulation->Add(platform);
    game_loop_->Add(platform_controller);
    game_loop_->Add(platform);

    auto level_factory = LevelFactory(physics_simulation.Get());
    auto level_view = SharedPointer(new LevelView(window_references));
    auto level = SharedPointer(new Level(level_factory.CreateMap(LevelLayouts::First()), level_view));
    game_loop_->Add(level);

    auto ball_view = SharedPointer(new BallView(window_references));
    auto ball = SharedPointer(new Ball(PhysicalProperties { { 55 + 103.5, 100 }, { 4, 4 }, { -35, -35 } }, ball_view));
    physics_simulation->Add(ball);
    game_loop_->Add(ball);

    auto wall_factory = WallFactory(game_loop_.Get(), physics_simulation.Get());
    auto left_wall = wall_factory.Create(window_references, "assets/sprites/left_wall.png", PhysicalProperties { { 55 + 4, 101 }, { 4, 200 } });
    auto up_wall = wall_factory.Create(window_references, "assets/sprites/up_wall.png", PhysicalProperties { { 55 + 103, 3 }, { 200, 4 } });
    auto right_wall = wall_factory.Create(window_references, "assets/sprites/right_wall.png", PhysicalProperties { { 55 + 202, 101 }, { 4, 200 } });

    // -----------------------------------------------------------------------------------------------------------------

    auto screen_applier = SharedPointer(new ScreenApplier(window_references));
    game_loop_->Add(screen_applier); // SYSTEM COMPONENT: applies all render that was before this line
}

void Game::Activate()
{
    game_loop_->Activate();
}
}
