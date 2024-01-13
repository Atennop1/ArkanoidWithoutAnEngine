#pragma once

#include <list>
#include "key_type.h"
#include "Windows.h"
#include "../loop/updatable.h"
#include "SDL.h"

class Input :  IUpdatable
{
private:
    std::list<KeyType> m_pressed_keys_;
    std::list<KeyType> m_pressed_this_frame_keys_;
    
public:
    Input();
    ~Input() override = default;
    
    bool IsKeyPressed(KeyType key_type) const;
    bool IsKeyPressedThisFrame(KeyType key_type) const;

    void Update(float delta) override;
};
