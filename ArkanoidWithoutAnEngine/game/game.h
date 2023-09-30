﻿#pragma once

#include <Windows.h>

#include "input/key_type.h"
#include "platform/View/platform_view.h"
#include "View/Level/level_view.h"

class Game
{
private:
    WindowHandles *m_window_handles_;
    LevelView *m_level_view_;
    PlatformView *m_platform_view_;
    
public:
    Game(WindowHandles *window_handles);
    ~Game();
    
    void Update(float delta) const;
    void OnKeyDown(KeyType key_type) const;
};

