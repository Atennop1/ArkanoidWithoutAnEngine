#pragma once
#include "../dtos/window_handles/window_references.h"
#include "../loop/updatables/updatable.h"

class ScreenCleaner : IUpdatable
{
private:
    WindowReferences *m_window_references_;
    
public:
    ScreenCleaner(WindowReferences *window_references);
    ~ScreenCleaner() override = default;
    
    void Update(float delta) override;
};
