#ifndef ARKANOIDWITHOUTANENGINE_733BD8BDA5C344A0A0EA2FCD927A7B43
#define ARKANOIDWITHOUTANENGINE_733BD8BDA5C344A0A0EA2FCD927A7B43

#include "window_references/window_references.hpp"
#include "../loop/game_loop_object.hpp"

class ScreenApplier : public IGameLoopObject
{
private:
    const WindowReferences &m_window_references_;

public:
    explicit ScreenApplier(const WindowReferences &window_references);
    ~ScreenApplier() override = default;

    void Update(float delta) override;
};

#endif
