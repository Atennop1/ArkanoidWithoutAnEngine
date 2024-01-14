#pragma once
#include "../dtos/window_references/window_references.h"
#include "../loop/updatables/updatable.h"

class ScreenApplier : IUpdatable
{
private:
    const WindowReferences &m_window_references_;
    
public:
    explicit ScreenApplier(const WindowReferences &window_references);
    ~ScreenApplier() override = default;
    
    void Update(const float &delta) override;
};
