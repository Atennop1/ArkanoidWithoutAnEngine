#include "application.h"
#include "../../game/game.h"
#include "window_factory/window_factory.h"

//----------------------------------------------------------------------------------------------------
void Application::Activate() const
{
    m_game_->Activate();
}

//----------------------------------------------------------------------------------------------------
Application::Application(HINSTANCE instance, HINSTANCE previous_instance, LPWSTR command_line, int window_showing_type)
{
    m_initial_hdc_ = GetDC(nullptr);
    m_independent_hdc_ = CreateCompatibleDC(m_initial_hdc_);
    m_window_handles_ = new WindowHandles(&m_independent_hdc_, nullptr);
    
    m_window_updater_ = new WindowUpdater(m_window_handles_);
    m_window_factory_ = new WindowFactory(m_window_updater_, instance, previous_instance, command_line, window_showing_type);

    m_window_ = m_window_factory_->Create();
    m_window_handles_ = new WindowHandles(&m_independent_hdc_, &m_window_);
    m_game_ = new Game(m_window_handles_);
}

//----------------------------------------------------------------------------------------------------
Application::~Application()
{
    free(m_game_);
    free(m_window_factory_);
        
    DeleteDC(m_independent_hdc_);
    ReleaseDC(m_window_, m_initial_hdc_);
}

//----------------------------------------------------------------------------------------------------
