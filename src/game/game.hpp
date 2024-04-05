#ifndef ARKANOIDWITHOUTANENGINE_E0B1DD35A1FB4D53B48EB27BFA7B193A
#define ARKANOIDWITHOUTANENGINE_E0B1DD35A1FB4D53B48EB27BFA7B193A

#include "rendering/window_references/window_references.hpp"
#include "loop/game_loops.hpp"
#include "loop/time/average_game_time.hpp"
#include "rendering/screen_cleaner.hpp"
#include "rendering/screen_applier.hpp"
#include "input/input.hpp"
#include "platform/view/platform_view.hpp"
#include "platform/model/platform.hpp"
#include "platform/controller/platform_controller.hpp"
#include "level/view/level_view.hpp"
#include "level/level.hpp"
#include "loop/logic/game_logic_loop.hpp"
#include "loop/physics/game_physics_loop.hpp"
#include "Box2D.hpp"

class Game
{
private:
    AverageGameTime m_game_time_;
    Box2D::World m_world_;

    ScreenCleaner m_screen_cleaner_;
    ScreenApplier m_screen_applier_;

    Input m_input_;
    PlatformView m_platform_view_;
    Platform m_platform_;
    PlatformController m_platform_controller_;

    LevelView m_level_view_;
    Level m_level_;

    GameLogicLoop m_game_logic_loop_;
    GamePhysicsLoop m_game_physics_loop_;
    GameLoops m_game_loops_;

public:
    explicit Game(const WindowReferences &window_references);
    void Activate();
};

#endif
