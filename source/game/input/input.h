#ifndef ARKANOIDWITHOUTANENGINE_629D06922D4E416DB500254C08D79DEE
#define ARKANOIDWITHOUTANENGINE_629D06922D4E416DB500254C08D79DEE

#include "key_type.h"
#include "../loop/updatables/updatable.h"
#include "../loop/updatables/events_updatable.h"

#include "SDL.h"
#include <list>

class Input : IUpdatable, IEventsUpdatable
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
