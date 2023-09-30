#pragma once
#include "../../core/includes/framework.h"
#include "../../Game/game.h"

class Application
{
private:
    int m_window_showing_type_;
    LPWSTR m_command_line_;

    WCHAR m_title_buffer_size[100];
    WCHAR m_window_buffer_size[100];
    
    HINSTANCE m_instance_;
    HINSTANCE m_previous_instance_;
    
    Game *m_game_;
    HDC m_current_hdc_;
    
    BOOL InitInstance(HINSTANCE instance, int window_showing_type);
    ATOM RegisterWindow(HINSTANCE instance) const;
    
public:
    Application(HINSTANCE instance, HINSTANCE previous_instance, LPWSTR command_line, int window_showing_type);
    
    MSG Run();
    LRESULT CALLBACK ProcessWindow(HWND window, UINT message, WPARAM word_parameter, LPARAM long_parameter);
};
