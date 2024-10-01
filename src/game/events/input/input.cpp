#include <algorithm>
#include "input.hpp"

arkanoid::Input::Input(const SharedPointer<ApplicationEvents> &events)
    : events_(events) { }

bool arkanoid::Input::IsKeyPressed(const KeyType key_type) const
    { return std::ranges::find(pressed_keys_.begin(), pressed_keys_.end(), key_type) != pressed_keys_.end(); }

bool arkanoid::Input::IsKeyPressedThisFrame(const KeyType key_type) const
    { return std::ranges::find(pressed_this_frame_keys_.begin(), pressed_this_frame_keys_.end(), key_type) != pressed_this_frame_keys_.end(); }

void arkanoid::Input::Update(float delta)
{
    pressed_this_frame_keys_.clear();
    std::vector<SDL_Event*> events = events_->GetEventsOfType({SDL_KEYDOWN, SDL_KEYUP });

    for (auto event : events)
    {
        KeyType key_type = kNone;
        switch (event->key.keysym.sym)
        {
            case SDLK_a:
            case SDLK_LEFT:
                key_type = kLeft;
                break;

            case SDLK_d:
            case SDLK_RIGHT:
                key_type = kRight;
                break;

            case SDLK_SPACE:
                key_type = kSpace;
                break;
        }

        if (event->type == SDL_KEYUP)
        {
            pressed_keys_.remove(key_type);
            continue;
        }

        pressed_this_frame_keys_.push_back(key_type);
        pressed_keys_.push_back(key_type);
    }
}
