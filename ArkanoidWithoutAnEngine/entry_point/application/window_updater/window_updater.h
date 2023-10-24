#pragma once
#include "../../../game/dtos/window_handles/window_handles.h"

LRESULT UpdateApplication(HWND window, UINT message, WPARAM word_parameter, LPARAM long_parameter);

class WindowUpdater
{
private:
    WindowHandles *m_window_handles_;
    
public:
    WindowUpdater(WindowHandles *window_handles);
    ~WindowUpdater();
    
    LRESULT CALLBACK Update(HWND window, UINT message, WPARAM word_parameter, LPARAM long_parameter) const;
};
