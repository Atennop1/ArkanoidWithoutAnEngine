#ifndef ARKANOIDWITHOUTANENGINE_B0581C2169124B399B807DBFF83F7B3F
#define ARKANOIDWITHOUTANENGINE_B0581C2169124B399B807DBFF83F7B3F

#include "key_type.hpp"
#include "../../loop/game_loop_object.hpp"
#include "../application_events.hpp"
#include "shared_pointer.hpp"
#include "SDL.h"
#include <list>

class Input : public IGameLoopObject
{
private:
    SharedPointer<ApplicationEvents> m_events_;

    std::list<KeyType> m_pressed_keys_ = { };
    std::list<KeyType> m_pressed_this_frame_keys_ = { };

public:
    Input(const SharedPointer<ApplicationEvents> &events);
    ~Input() override = default;

    void Update(float delta) override;
    bool IsKeyPressed(KeyType key_type) const;
    bool IsKeyPressedThisFrame(KeyType key_type) const;
};

#endif
