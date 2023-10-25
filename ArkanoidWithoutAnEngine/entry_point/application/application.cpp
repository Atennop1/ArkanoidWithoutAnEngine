#include "application.h"
#include "../../game/game.h"
#include "../../game/rendering/rendering_consts.h"
#include "window_factory/window_factory.h"

//----------------------------------------------------------------------------------------------------
void Application::Activate() const
{
    m_game_->Activate();
}

//----------------------------------------------------------------------------------------------------
Application::Application(HINSTANCE instance, HINSTANCE previous_instance, LPWSTR command_line, int window_showing_type)
{
    PrepareIntermediateHDC();
    m_window_handles_ = new WindowHandles(&m_intermediate_hdc_, &m_window_);
    m_window_updater_ = new WindowUpdater(m_window_handles_);
    m_window_factory_ = new WindowFactory(m_window_updater_, instance, previous_instance, command_line, window_showing_type);

    m_window_ = m_window_factory_->Create();
    m_game_ = new Game(m_window_handles_);
}

//----------------------------------------------------------------------------------------------------
void Application::PrepareIntermediateHDC()
{
    m_intermediate_hdc_ = CreateCompatibleDC(nullptr);
    const auto initial_hdc = GetDC(nullptr);
    const HBITMAP intermediate_bitmap = CreateCompatibleBitmap(initial_hdc, kWindowWidth, kWindowHeight);
    
    SelectObject(m_intermediate_hdc_, intermediate_bitmap);
    ReleaseDC(m_window_, initial_hdc);
}

//----------------------------------------------------------------------------------------------------
Application::~Application()
{
    free(m_game_);
    free(m_window_factory_);
    DeleteDC(m_intermediate_hdc_);
}

//----------------------------------------------------------------------------------------------------
