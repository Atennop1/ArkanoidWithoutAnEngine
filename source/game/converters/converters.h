#ifndef ARKANOIDWITHOUTANENGINE_7C41A79821D446878DE991EC02215267
#define ARKANOIDWITHOUTANENGINE_7C41A79821D446878DE991EC02215267

#include "../input/key_type.h"
#include "../dtos/vector2/int_vector2.h"
#include "../dtos/vector2/vector2.h"
#include "SDL.h"

class Converters
{
public:
    static KeyType FromEventToKeyType(SDL_Event event);

    static IntVector2 FromVector2ToIntVector2(Vector2 vector2);
    static Vector2 FromIntVector2ToVector2(IntVector2 int_vector2);
};

#endif
