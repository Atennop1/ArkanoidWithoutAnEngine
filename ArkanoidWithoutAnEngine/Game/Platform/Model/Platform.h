#pragma once
#include "../../DTOs/Vector2/Vector2.h"
#include "../View/PlatformView.h"

class Platform
{
private:
    Vector2 m_platformPosition;
    PlatformView *m_platformView;
    
public:
    Platform(PlatformView *platformView);
    void Move(Vector2 moveVector);
};
