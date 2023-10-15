#pragma once

#include <list>
#include "key_type.h"
#include "Windows.h"
#include "../loop/updatables/system_updatable.h"

class Input : ISystemUpdatable
{
private:
    std::list<KeyType> *m_pressed_keys_;
    std::list<KeyType> *m_pressed_this_frame_keys_;
    
public:
    Input();
    ~Input() override;
    
    bool IsKeyPressed(KeyType key_type) const;
    bool IsKeyPressedThisFrame(KeyType key_type) const;
    void Update(MSG *message) override;
};
