#include "Converters.h"

KeyType Converters::FromWParam(WPARAM wParam)
{
    switch (wParam)
    {
    case VK_LEFT:
        return KT_Left;

    case VK_RIGHT:
        return KT_Right;

    case VK_SPACE:
        return KT_Space;

    default:
        return KT_None;
    }
}
