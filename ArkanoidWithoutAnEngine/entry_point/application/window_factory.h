#pragma once
#include "../../core/includes/framework.h"

class WindowFactory
{
private:
    HINSTANCE m_instance_;
    int m_window_showing_type_;

    WCHAR m_title_buffer_size_[100];
    WCHAR m_window_buffer_size_[100];
    
    void RegisterWindow() const;
    HWND CreateWindowInstance();
    
public:
    WindowFactory(HINSTANCE instance, HINSTANCE previous_instance, LPWSTR command_line, int window_showing_type);
    HWND Create();
};
