#pragma once

#include <Windows.h>

#include "input/key_type.h"
#include "loop/game_loop.h"
#include "platform/View/platform_view.h"
#include "View/Level/level_view.h"

class Game
{
private:
    WindowHandles *m_window_handles_;
    GameLoop *game_loop_;
    
    LevelView *m_level_view_;
    PlatformView *m_platform_view_;
    
public:
    Game(WindowHandles *window_handles);
    void Activate() const;
    
    void OnKeyDown(KeyType key_type) const;
    ~Game();
};

