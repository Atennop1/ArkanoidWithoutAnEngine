#pragma once
#include "../input/key_type.h"
#include "Windows.h"
#include "../dtos/vector2/int_vector2.h"
#include "../dtos/vector2/vector2.h"

class Converters
{
public:
    static KeyType FromWParamToKeyType(WPARAM wParam);

    static IntVector2 FromVector2ToIntVector2(Vector2 vector2);
    static Vector2 FromIntVector2ToVector2(IntVector2 int_vector2);
};
