#pragma once
#include "../window_updater/window_updater.h"

class WindowFactory
{
private:
    HINSTANCE m_instance_;
    int m_window_showing_type_;

    WCHAR m_title_buffer_size_[100];
    WCHAR m_window_buffer_size_[100];
    WindowUpdater *m_window_updater_;
    
    void RegisterWindow() const;
    HWND CreateWindowInstance() const;
    
public:
    WindowFactory(WindowUpdater *window_updater, HINSTANCE instance, HINSTANCE previous_instance, LPWSTR command_line, int window_showing_type);
    HWND Create() const;
};
