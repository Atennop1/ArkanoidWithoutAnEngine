﻿#include "Game.h"
#include "Levels/Levels.h"
#include "Rendering/Level/LevelRenderer.h"

//----------------------------------------------------------------------------------------------------
void Game::OnKeyDown(KeyType keyType) const
{
    switch (keyType)
    {
    case KT_Left:
        break;
        
    case KT_Right:
        break;
        
    case KT_Space:
        break;
        
    case KT_None:
        break;
    }
}

//----------------------------------------------------------------------------------------------------
void Game::Render(HDC hdc) const
{
    const auto level = Levels::First();
    m_levelRenderer->Render(hdc, &level);
    m_platformRenderer->Display(Vector2(100, 100));
}

//----------------------------------------------------------------------------------------------------
Game::Game(HWND hwnd) 
{
    auto *violetRenderPack = new RenderPack(RGB(255, 85, 255));
    auto *blueRenderPack = new RenderPack(RGB(85, 255, 255));
    const HPEN whitePen = CreatePen(PS_SOLID, 3, RGB(255, 255, 255));

    HDC hdc = GetDC(hwnd);
    m_windowHandles = new WindowHandles(&hdc, &hwnd);

    m_levelRenderer = new LevelRenderer(*violetRenderPack, *blueRenderPack);
    m_platformRenderer = new PlatformView(m_windowHandles, violetRenderPack, blueRenderPack, whitePen);
}

//----------------------------------------------------------------------------------------------------
Game::~Game()
{
    free(m_levelRenderer);
    free(m_platformRenderer);
    free(m_windowHandles);
}

//----------------------------------------------------------------------------------------------------
