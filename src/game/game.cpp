#include "game.hpp"
#include "level/constants/level_maps.hpp"

Game::Game(const WindowReferences &window_references)
    : m_game_time_(),
      m_world_(Box2D::Vector2(0.0f, -10.0f)),
      m_screen_cleaner_(window_references),
      m_screen_applier_(window_references),
      m_input_(),
      m_platform_view_(window_references),
      m_platform_(m_platform_view_),
      m_platform_controller_(m_input_, m_platform_),
      m_level_view_(window_references),
      m_level_(LevelMaps::First(), m_level_view_),
      m_game_logic_loop_(m_game_time_),
      m_game_physics_loop_(m_world_, m_game_time_),
      m_game_loops_({ })
{
    m_game_logic_loop_.AddUpdatable(m_screen_cleaner_); // SYSTEM COMPONENT: clearing all render that was before this line
    m_game_logic_loop_.AddEventsUpdatable(m_input_);
    m_game_logic_loop_.AddUpdatable(m_platform_);
    m_game_logic_loop_.AddUpdatable(m_platform_controller_);
    m_game_logic_loop_.AddUpdatable(m_level_);
    m_game_logic_loop_.AddUpdatable(m_screen_applier_); // SYSTEM COMPONENT: applies all render that was before this line
    m_game_logic_loop_.AddUpdatable(m_input_);

    m_game_loops_ = GameLoops({ &m_game_logic_loop_, &m_game_physics_loop_ });
}

void Game::Activate()
{
    m_game_loops_.Activate();
}
