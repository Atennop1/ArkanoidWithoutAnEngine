#include "application.h"
#include "window_factory.h"
#include "window_processor.h"
#include "../../Game/game.h"

Application::Application(HINSTANCE instance, HINSTANCE previous_instance, LPWSTR command_line, int window_showing_type)
{
    m_window_factory_ = new WindowFactory(instance, previous_instance, command_line, window_showing_type);
    HWND window = m_window_factory_->Create();
    
    HDC initial_hdc = GetDC(nullptr);
    HDC independent_bitmap_dc = CreateCompatibleDC(initial_hdc);

    const auto window_handles = new WindowHandles(&independent_bitmap_dc, &window);
    m_game_ = new Game(window_handles);
    
    m_window_processor_ = new WindowProcessor(m_game_, window_handles, &initial_hdc);
}

//----------------------------------------------------------------------------------------------------
Application::~Application()
{
    free(m_game_);
    free(m_window_factory_);
    free(m_window_processor_);
}

//----------------------------------------------------------------------------------------------------
void Application::Activate() const
{
    m_game_->Activate();
}

//----------------------------------------------------------------------------------------------------
