#include "converters.h"

KeyType Converters::FromWParamToKeyType(WPARAM wParam)
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
