#include "converters.h"

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
