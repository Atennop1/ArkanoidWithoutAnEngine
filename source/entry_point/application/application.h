#pragma once

#include "../../game/game.h"
#include "window_factory/window_factory.h"

class Application
{
private:
    WindowUpdater *m_window_updater_;
    WindowFactory *m_window_factory_;

    Game *m_game_;
    WindowHandles *m_window_handles_;

    HWND m_window_;
    HDC m_intermediate_hdc_;

    void PrepareIntermediateHDC();
    
public:
    Application(HINSTANCE instance, HINSTANCE previous_instance, LPWSTR command_line, int window_showing_type);
    ~Application();
    
    void Activate() const;
};
