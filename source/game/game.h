#pragma once

#include "loop/game_loop.h"
#include "platform/View/platform_view.h"

class Game
{
private:
    GameLoop *m_game_loop_;
    WindowHandles *m_window_handles_;
    
public:
    Game(WindowHandles *window_handles);
    ~Game();

    void Activate() const;
};

