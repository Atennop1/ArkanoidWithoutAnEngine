#ifndef ARKANOIDWITHOUTANENGINE_1C6EF8776F63439EA499802662F2706C
#define ARKANOIDWITHOUTANENGINE_1C6EF8776F63439EA499802662F2706C

#include "../dtos/window_references/window_references.h"
#include "../loop/updatables/updatable.h"

class ScreenApplier : IUpdatable
{
private:
    const WindowReferences &m_window_references_;

public:
    explicit ScreenApplier(const WindowReferences &window_references);
    ~ScreenApplier() override = default;

    void Update(float delta) override;
};

#endif
