#include "input.hpp"
#include <algorithm>

Input::Input()
{
    m_pressed_keys_ = std::list<KeyType>();
    m_pressed_this_frame_keys_ = std::list<KeyType>();
}

bool Input::IsKeyPressed(const KeyType key_type) const
{
    return std::find(m_pressed_keys_.begin(), m_pressed_keys_.end(), key_type) != m_pressed_keys_.end();
}

bool Input::IsKeyPressedThisFrame(const KeyType key_type) const
{
    return std::find(m_pressed_this_frame_keys_.begin(), m_pressed_this_frame_keys_.end(), key_type) !=
           m_pressed_this_frame_keys_.end();
}

void Input::Update(float delta)
{
    m_pressed_this_frame_keys_.clear();
}

void Input::Update(const SDL_Event &event)
{
    if (event.type != SDL_KEYDOWN && event.type != SDL_KEYUP)
        return;

    KeyType key_type = kNone;
    switch (event.key.keysym.sym)
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

    if (event.type == SDL_KEYUP)
    {
        m_pressed_keys_.remove(key_type);
        return;
    }

    m_pressed_this_frame_keys_.push_back(key_type);
    m_pressed_keys_.push_back(key_type);
}
