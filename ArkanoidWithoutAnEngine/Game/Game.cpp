#include "Game.h"
#include "Levels/Levels.h"
#include "Rendering/RenderingConsts.h"
#include "Rendering/Level/LevelRenderer.h"
#include "Rendering/Platform/PlatformRenderer.h"
#include "Shortcuts/Shortcuts.h"

//----------------------------------------------------------------------------------------------------
void Game::Update(HDC hdc) const
{
    const auto violetRenderPack = RenderPack(RGB(255, 85, 255));
    const auto blueRenderPack = RenderPack(RGB(85, 255, 255));
    const auto whitePen = CreatePen(PS_SOLID, 3, RGB(255, 255, 255));

    const auto levelRenderer = LevelRenderer(violetRenderPack, blueRenderPack);
    const auto platformRenderer = PlatformRenderer(violetRenderPack, blueRenderPack, whitePen);
    
    levelRenderer.Render(hdc, Levels::First());
    platformRenderer.Render(hdc, Vector2(90, 150));




    
    XFORM oldXform;
    XFORM newXform;

    constexpr double rotationAngle = 360.0;
    SetGraphicsMode(hdc, GM_ADVANCED);

    newXform.eM11 = 1.0f; 
    newXform.eM12 = 0;
    newXform.eM21 = 0; 
    newXform.eM22 = (float)cos(rotationAngle); 
    newXform.eDx = (FLOAT)100.0; 
    newXform.eDy = (FLOAT)100.0; 
    
    GetWorldTransform(hdc, &oldXform);
    SetWorldTransform(hdc, &newXform);

    Shortcuts::SelectRenderPack(hdc, blueRenderPack);
    Rectangle(hdc, 0, 0,  15 * SCALE_MULTIPLIER, 7 * SCALE_MULTIPLIER);
    SetWorldTransform(hdc, &oldXform);
}

//----------------------------------------------------------------------------------------------------
