#include "input.h"
#include "../converters/converters.h"

//----------------------------------------------------------------------------------------------------
Input::Input()
{
    m_pressed_keys_ = new std::list<KeyType>();
    m_pressed_this_frame_keys_ = new std::list<KeyType>();
}

//----------------------------------------------------------------------------------------------------
Input::~Input()
{
    free(m_pressed_keys_);
    free(m_pressed_this_frame_keys_);
}

//----------------------------------------------------------------------------------------------------
bool Input::IsKeyPressed(KeyType key_type) const
{
    return std::find(m_pressed_keys_->begin(), m_pressed_keys_->end(), key_type) != m_pressed_keys_->end();
}

//----------------------------------------------------------------------------------------------------
bool Input::IsKeyPressedThisFrame(KeyType key_type) const
{
    return std::find(m_pressed_this_frame_keys_->begin(), m_pressed_this_frame_keys_->end(), key_type) != m_pressed_this_frame_keys_->end();
}

//----------------------------------------------------------------------------------------------------
void Input::Update(float delta)
{
    m_pressed_this_frame_keys_->clear();
}

//----------------------------------------------------------------------------------------------------
BOOL Input::PreTranslateMessage(MSG *message)
{
    const WPARAM word_parameter = message->wParam;
    const KeyType key_type = Converters::FromWParamToKeyType(word_parameter);
    
    if (word_parameter == WM_KEYUP)
    {
        m_pressed_keys_->remove(key_type);
        return 0;
    }
    
    if (word_parameter == WM_KEYDOWN)
    {
        m_pressed_this_frame_keys_->push_back(key_type);
        m_pressed_keys_->push_back(key_type);
    }

    return 0;
}

//----------------------------------------------------------------------------------------------------
