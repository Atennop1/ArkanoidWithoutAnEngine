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
#include "game/physics/test_object.hpp"
#include "game/physics/physics_simulation.hpp"
#include "game/level/level_layouts.hpp"
#include "game/root/level_factory.hpp"

namespace arkanoid
{
Game::Game(const WindowReferences &window_references)
{
    auto game_time = SharedPointer<IReadOnlyGameTime>(new AverageGameTime());
    auto application_events = SharedPointer(new ApplicationEvents());
    game_loop_ = SharedPointer(new GameLoop(game_time, application_events));

    auto screen_cleaner = SharedPointer(new ScreenCleaner(window_references));
    auto screen_applier = SharedPointer(new ScreenApplier(window_references));

    auto input = SharedPointer(new Input(application_events));
    auto platform_view = SharedPointer(new PlatformView(window_references));
    auto platform = SharedPointer(new Platform(PhysicalProperties {{ 110 * 6, 150 * 6 }, { 28 * 6, 7 * 6 } }, platform_view));
    auto platform_controller = SharedPointer(new PlatformController(platform, input));

    auto test_object = SharedPointer(new TestObject(PhysicalProperties {{ 500, 500 }, { 50, 50 }, { 1, 1 }, { 10, 10} }, window_references));
    auto test_object2 = SharedPointer(new TestObject(PhysicalProperties {{ 1500, 100 }, { 50, 50 }, { -1, 1 }, { -10, 10} }, window_references));
    auto physics_simulation = SharedPointer(new PhysicsSimulation({ test_object, test_object2, platform }));

    auto level_view = SharedPointer(new LevelView(window_references));
    auto level_factory = LevelFactory();
    auto level = SharedPointer(new Level(level_factory.MakeMap(LevelLayouts::First(), physics_simulation.Get()), level_view));

    game_loop_->Add(application_events); // SYSTEM COMPONENT: gets all events from SDL2
    game_loop_->Add(physics_simulation); // SYSTEM COMPONENT: updates all physics before other logic
    game_loop_->Add(screen_cleaner); // SYSTEM COMPONENT: clearing all render that was before this line
    game_loop_->Add(input);
    game_loop_->Add(platform_controller);
    game_loop_->Add(platform);
    game_loop_->Add(level);
    game_loop_->Add(test_object);
    game_loop_->Add(test_object2);
    game_loop_->Add(screen_applier); // SYSTEM COMPONENT: applies all render that was before this line
}

void Game::Activate()
{
    game_loop_->Activate();
}
}
