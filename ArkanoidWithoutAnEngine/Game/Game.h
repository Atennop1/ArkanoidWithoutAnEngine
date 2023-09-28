#pragma once

#include <Windows.h>

#include "DTOs/WindowHandles/WindowHandles.h"
#include "Input/KeyType.h"
#include "Platform/View/PlatformView.h"
#include "View/Level/LevelView.h"

class Game
{
private:
    WindowHandles *m_windowHandles;
    LevelView *m_levelView;
    PlatformView *m_platformRenderer;
    
public:
    Game(WindowHandles *windowHandles);
    ~Game();
    
    void Render(HDC hdc) const;
    void OnKeyDown(KeyType keyType) const;
};

