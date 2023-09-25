﻿#include "Game.h"
#include "Levels/Levels.h"
#include "Rendering/Level/LevelRenderer.h"
#include "Rendering/Platform/PlatformRenderer.h"

//----------------------------------------------------------------------------------------------------
void Game::Update(HDC hdc) const
{
    const auto violetRenderPack = RenderPack(RGB(255, 85, 255));
    const auto blueRenderPack = RenderPack(RGB(85, 255, 255));

    const auto levelRenderer = LevelRenderer(violetRenderPack, blueRenderPack);
    const auto platformRenderer = PlatformRenderer(violetRenderPack, blueRenderPack);
    
    levelRenderer.Render(hdc, Levels::First());
    platformRenderer.Render(hdc, 50, 100);
}

//----------------------------------------------------------------------------------------------------
