#pragma once

#include "window_factory.h"
#include "window_processor.h"
#include "../../Game/game.h"

class Application
{
private:
    WindowFactory *m_window_factory_;
    WindowProcessor *m_window_processor_;

    Game *m_game_;
    
public:
    Application(HINSTANCE instance, HINSTANCE previous_instance, LPWSTR command_line, int window_showing_type);
    ~Application();
    
    void Activate() const;
};
