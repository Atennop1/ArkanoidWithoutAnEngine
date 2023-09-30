#pragma once
#include "../input/key_type.h"
#include "Windows.h"

class Converters
{
public:
    static KeyType FromWParamToKeyType(WPARAM wParam);
};
