#include "Game.h"
#include "Levels/Levels.h"
#include "Rendering/Level/LevelRenderer.h"
#include "Rendering/Platform/PlatformRenderer.h"

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
    m_platformRenderer->Render(hdc, Vector2(100, 185));
}

//----------------------------------------------------------------------------------------------------
Game::Game() 
{
    const auto violetRenderPack = RenderPack(RGB(255, 85, 255));
    const auto blueRenderPack = RenderPack(RGB(85, 255, 255));
    const auto whitePen = CreatePen(PS_SOLID, 3, RGB(255, 255, 255));

    m_levelRenderer = new LevelRenderer(violetRenderPack, blueRenderPack);
    m_platformRenderer = new PlatformRenderer(violetRenderPack, blueRenderPack, whitePen);
}

//----------------------------------------------------------------------------------------------------
Game::~Game()
{
    free(m_levelRenderer);
    free(m_platformRenderer);
}

//----------------------------------------------------------------------------------------------------
