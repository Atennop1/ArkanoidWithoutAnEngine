#pragma once
#include "../Input/KeyType.h"
#include "Windows.h"

class Converters
{
public:
    static KeyType FromWParam(WPARAM wParam);
};
