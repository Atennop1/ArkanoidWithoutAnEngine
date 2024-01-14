#pragma once
#include "../dtos/window_references/window_references.h"
#include "../loop/updatables/updatable.h"

class ScreenCleaner : IUpdatable
{
private:
    const WindowReferences &m_window_references_;
    
public:
    explicit ScreenCleaner(const WindowReferences &window_references);
    ~ScreenCleaner() override = default;
    
    void Update(const float &delta) override;
};
