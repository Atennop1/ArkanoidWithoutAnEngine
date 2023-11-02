#include "shortcuts.h"
#include <cwchar>
#include <debugapi.h>

//----------------------------------------------------------------------------------------------------
void Shortcuts::SelectColor(SDL_Renderer *renderer, SDL_Color color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}

//----------------------------------------------------------------------------------------------------
void Shortcuts::PrintDebugString(const wchar_t *string, ...)
{
    va_list args;
    va_start(args, string);
    wchar_t char_buffer[256];
    
    vswprintf(char_buffer, 256, string, args);
    OutputDebugString(reinterpret_cast<LPCSTR>(char_buffer));
    va_end(args);
}

//----------------------------------------------------------------------------------------------------
