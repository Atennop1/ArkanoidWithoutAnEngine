#ifndef ARKANOIDWITHOUTANENGINE_B0581C2169124B399B807DBFF83F7B3F
#define ARKANOIDWITHOUTANENGINE_B0581C2169124B399B807DBFF83F7B3F

#include "key_type.hpp"
#include "../loop/updatables/updatable.hpp"
#include "../loop/updatables/events_updatable.hpp"

#include "SDL.h"
#include <list>

class Input : public IUpdatable, public IEventsUpdatable
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
    void Update(const SDL_Event &event) override;
};

#endif
