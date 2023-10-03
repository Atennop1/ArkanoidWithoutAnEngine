#pragma once
#include "key_type.h"
#include "Windows.h"

class Input
{
public:
    bool IsKeyPressed(KeyType key_type);
    bool IsKeyPressedThisFrame(KeyType key_type);

    void ReactOnKeyEvent(WPARAM word_parameter);
};
