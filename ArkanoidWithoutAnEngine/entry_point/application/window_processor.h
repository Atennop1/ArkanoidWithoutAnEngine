#pragma once

#include "../../core/includes/framework.h"
#include "../../Game/game.h"

LRESULT StaticProcessWindow(HWND window, UINT message, WPARAM word_parameter, LPARAM long_parameter);

class WindowProcessor
{
private:
    Game *m_game_;
    WindowHandles *m_window_handles_;
    HDC *m_initial_hdc_;
    
public:
    WindowProcessor(Game *game, WindowHandles *window_handles, HDC *initial_hdc);
    LRESULT CALLBACK ProcessWindow(HWND window, UINT message, WPARAM word_parameter, LPARAM long_parameter) const;
};
