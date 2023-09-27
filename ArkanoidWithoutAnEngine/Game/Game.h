#pragma once

#include <Windows.h>

#include "DTOs/WindowHandles/WindowHandles.h"
#include "Input/KeyType.h"
#include "Platform/View/PlatformView.h"
#include "Rendering/Level/LevelRenderer.h"

class Game
{
private:
    WindowHandles *m_windowHandles;
    LevelRenderer *m_levelRenderer;
    PlatformView *m_platformRenderer;
    
public:
    Game(WindowHandles *windowHandles);
    ~Game();
    
    void Render(HDC hdc) const;
    void OnKeyDown(KeyType keyType) const;
};

