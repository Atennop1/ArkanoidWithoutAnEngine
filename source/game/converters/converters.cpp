#include "converters.h"
#include "SDL.h"

//----------------------------------------------------------------------------------------------------
KeyType Converters::FromEventToKeyType(SDL_Event event)
{
    switch (event.key.keysym.sym)
    {
        case SDKL_w:
        case SDLK_LEFT:
            return kLeft;

        case SDLK_RIGHT:
            return kRight;
    
        case SDLK_SPACE:
            return kSpace;
        default:
            return kNone;
    }
}

//----------------------------------------------------------------------------------------------------
IntVector2 Converters::FromVector2ToIntVector2(Vector2 vector2)
{
    return { static_cast<int>(vector2.X()), static_cast<int>(vector2.Y()) };
}

//----------------------------------------------------------------------------------------------------
Vector2 Converters::FromIntVector2ToVector2(IntVector2 int_vector2)
{
    return { int_vector2.X(), int_vector2.Y() };
}

//----------------------------------------------------------------------------------------------------
