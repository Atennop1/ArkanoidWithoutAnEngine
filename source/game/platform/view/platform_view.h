#pragma once
#include "../../dtos/window_handles/window_references.h"

class PlatformView
{
private:
    WindowReferences *m_window_handles_;

public:
    PlatformView(WindowReferences *window_handles);
    ~PlatformView();
    
    void Display(Vector2 position, Vector2 size) const;
};

