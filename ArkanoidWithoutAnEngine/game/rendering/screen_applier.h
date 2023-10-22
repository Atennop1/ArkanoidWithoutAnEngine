#pragma once
#include "../dtos/window_handles/window_handles.h"
#include "../loop/updatables/updatable.h"

class ScreenApplier : IUpdatable
{
private:
    WindowHandles *m_window_handles_;
    
public:
    ScreenApplier(WindowHandles *window_handles);
    ~ScreenApplier() override = default;
    
    void Update(float delta) override;
};
