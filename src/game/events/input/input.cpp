#include <algorithm>
#include "input.hpp"

arkanoid::Input::Input(const SharedPointer<ApplicationEvents> &events)
    : m_events_(events) { }

bool arkanoid::Input::IsKeyPressed(const KeyType key_type) const
    { return std::ranges::find(m_pressed_keys_.begin(), m_pressed_keys_.end(), key_type) != m_pressed_keys_.end(); }

bool arkanoid::Input::IsKeyPressedThisFrame(const KeyType key_type) const
    { return std::ranges::find(m_pressed_this_frame_keys_.begin(), m_pressed_this_frame_keys_.end(), key_type) != m_pressed_this_frame_keys_.end(); }

void arkanoid::Input::Update(float delta)
{
    m_pressed_this_frame_keys_.clear();
    std::vector<SDL_Event*> events = m_events_->GetEventsOfType({ SDL_KEYDOWN, SDL_KEYUP });

    for (auto event : events)
    {
        KeyType key_type = KNone;
        switch (event->key.keysym.sym)
        {
            case SDLK_a:
            case SDLK_LEFT:
                key_type = KLeft;
                break;

            case SDLK_d:
            case SDLK_RIGHT:
                key_type = KRight;
                break;

            case SDLK_SPACE:
                key_type = KSpace;
                break;
        }

        if (event->type == SDL_KEYUP)
        {
            m_pressed_keys_.remove(key_type);
            continue;
        }

        m_pressed_this_frame_keys_.push_back(key_type);
        m_pressed_keys_.push_back(key_type);
    }
}
