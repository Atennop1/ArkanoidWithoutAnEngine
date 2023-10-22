#pragma once
#include "../../core/includes/framework.h"
#include "../../Game/game.h"

class Application
{
private:
    HINSTANCE m_instance_;
    int m_window_showing_type_;

    WCHAR m_title_buffer_size_[100];
    WCHAR m_window_buffer_size_[100];
    
    Game *m_game_;
    WindowHandles *m_window_handles_;
    
    BOOL InitInstance(HINSTANCE instance, int window_showing_type);
    ATOM RegisterWindow(HINSTANCE instance) const;
    
public:
    Application(HINSTANCE instance, HINSTANCE previous_instance, LPWSTR command_line, int window_showing_type);
    
    MSG Activate();
    LRESULT CALLBACK ProcessWindow(HWND window, UINT message, WPARAM word_parameter, LPARAM long_parameter) const;
};
