#pragma once

#include <Windows.h>
#include "Input/KeyType.h"
#include "Rendering/Level/LevelRenderer.h"
#include "Rendering/Platform/PlatformRenderer.h"

class Game
{
private:
    LevelRenderer *m_levelRenderer;
    PlatformRenderer *m_platformRenderer;
    
public:
    Game();
    ~Game();
    
    void Render(HDC hdc) const;
    void OnKeyDown(KeyType keyType) const;
};

