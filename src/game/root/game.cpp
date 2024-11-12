#include "game/root/game.hpp"
#include "game/platform/platform_controller.hpp"
#include "game/level/level.hpp"
#include "game/level/level_layouts.hpp"
#include "game/root/level_factory.hpp"
#include "game/ball/ball.hpp"
#include "game/root/wall_factory.hpp"
#include <genesis/rendering/screen_cleaner.hpp>
#include <genesis/rendering/screen_applier.hpp>
#include <genesis/exiting/application_exiter.hpp>

namespace arkanoid
{
Game::Game(const genesis::WindowReferences &window_references)
{
    auto game_time = genesis::SharedPointer<genesis::GameTime>(new genesis::GameTime());
    auto application_events = genesis::SharedPointer(new genesis::ApplicationEvents());
    game_loop_ = genesis::SharedPointer(new genesis::GameLoop(game_time, application_events));

    auto screen_cleaner = genesis::SharedPointer(new genesis::ScreenCleaner(window_references));
    auto physics_simulation = genesis::SharedPointer(new genesis::PhysicsSimulation());
    auto input = genesis::SharedPointer(new genesis::Input(application_events));
    auto exiter = genesis::SharedPointer(new genesis::ApplicationExiter(input));

    game_loop_->Add(application_events); // SYSTEM COMPONENT: gets all events from SDL2
    game_loop_->Add(physics_simulation); // SYSTEM COMPONENT: updates all physics before other logic
    game_loop_->Add(screen_cleaner); // SYSTEM COMPONENT: clearing all render that was before this line
    game_loop_->Add(input); // SYSTEM COMPONENT: reading input from OS
    game_loop_->Add(exiter); // SYSTEM COMPONENT: exiting from loop by pressing 'Escape'

    // GAME LOGIC PART
    // -----------------------------------------------------------------------------------------------------------------

    auto platform_view = genesis::SharedPointer(new PlatformView(window_references));
    auto platform = genesis::SharedPointer(new Platform(genesis::PhysicalProperties { { 158.5, 30 }, { 28, 5 } }, platform_view));
    auto platform_controller = genesis::SharedPointer(new PlatformController(platform, input));
    physics_simulation->Add(platform);
    game_loop_->Add(platform_controller);
    game_loop_->Add(platform);

    auto level_factory = LevelFactory(physics_simulation.Get());
    auto level_view = genesis::SharedPointer(new LevelView(window_references));
    auto level = genesis::SharedPointer(new Level(level_factory.CreateMap(LevelLayouts::First()), level_view));
    game_loop_->Add(level);

    auto ball_view = genesis::SharedPointer(new BallView(window_references));
    auto ball = genesis::SharedPointer(new Ball(genesis::PhysicalProperties { { 158.5, 80 }, { 4, 4 }, { -35, 35 } }, ball_view));
    physics_simulation->Add(ball);
    game_loop_->Add(ball);

    auto wall_factory = WallFactory(game_loop_.Get(), physics_simulation.Get());
    wall_factory.Create(window_references, "assets/sprites/walls/left_wall.png", genesis::PhysicalProperties { { 59, 79 }, { 4, 200 } });
    wall_factory.Create(window_references, "assets/sprites/walls/up_wall.png", genesis::PhysicalProperties { { 158, 177 }, { 200, 4 } });
    wall_factory.Create(window_references, "assets/sprites/walls/right_wall.png", genesis::PhysicalProperties { { 257, 79 }, { 4, 200 } });

    // -----------------------------------------------------------------------------------------------------------------

    auto screen_applier = genesis::SharedPointer(new genesis::ScreenApplier(window_references));
    game_loop_->Add(screen_applier); // SYSTEM COMPONENT: applies all render that was before this line
}

void Game::Activate()
{
    game_loop_->Activate();
}
}
