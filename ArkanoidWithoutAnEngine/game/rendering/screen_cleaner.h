#pragma once
#include "../dtos/window_handles/window_handles.h"
#include "../loop/updatables/updatable.h"

class ScreenCleaner : IUpdatable
{
private:
    WindowHandles *m_window_handles_;
    
public:
    ScreenCleaner(WindowHandles *window_handles);
    ~ScreenCleaner() override = default;
    
    void Update(float delta) override;
};
