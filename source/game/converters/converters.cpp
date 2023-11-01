#include "converters.h"

//----------------------------------------------------------------------------------------------------
KeyType Converters::FromWParamToKeyType(const WPARAM wParam)
{
    switch (wParam)
    {
    case VK_LEFT:
        return kLeft;

    case VK_RIGHT:
        return kRight;

    case VK_SPACE:
        return kSpace;

    default:
        return kNone;
    }
}

//----------------------------------------------------------------------------------------------------
IntVector2 Converters::FromVector2ToIntVector2(Vector2 vector2)
{
    return IntVector2(static_cast<int>(vector2.X()), static_cast<int>(vector2.Y()));
}

//----------------------------------------------------------------------------------------------------
Vector2 Converters::FromIntVector2ToVector2(IntVector2 int_vector2)
{
    return Vector2(int_vector2.X(), int_vector2.Y());
}

//----------------------------------------------------------------------------------------------------
