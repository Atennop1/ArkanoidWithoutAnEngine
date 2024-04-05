#ifndef ARKANOIDWITHOUTANENGINE_733BD8BDA5C344A0A0EA2FCD927A7B43
#define ARKANOIDWITHOUTANENGINE_733BD8BDA5C344A0A0EA2FCD927A7B43

#include "window_references/window_references.hpp"
#include "../loop/logic/updatables/updatable.hpp"
#include <memory>

class ScreenApplier : public IUpdatable
{
private:
    const WindowReferences &m_window_references_;

public:
    explicit ScreenApplier(const WindowReferences &window_references);
    ~ScreenApplier() override = default;

    void Update(float delta) override;
};

#endif
