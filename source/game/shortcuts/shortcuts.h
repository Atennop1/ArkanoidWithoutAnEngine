#pragma once
#include "SDL.h"

class Shortcuts
{
public:
    static void SelectColor(SDL_Renderer *renderer, SDL_Color color);
    static void PrintDebugString(const wchar_t *string, ...);
};



