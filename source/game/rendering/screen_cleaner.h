#pragma once
#include "../dtos/window_references/window_references.h"
#include "../loop/updatable.h"

class ScreenCleaner : IUpdatable
{
private:
    WindowReferences &m_window_references_;
    
public:
    explicit ScreenCleaner(const WindowReferences &window_references);
    ~ScreenCleaner() override = default;
    
    void Update(float delta) override;
};
