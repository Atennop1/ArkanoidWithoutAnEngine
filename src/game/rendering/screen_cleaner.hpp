#ifndef ARKANOIDWITHOUTANENGINE_BCF32EB3BAE64E8C821572B20358FE83
#define ARKANOIDWITHOUTANENGINE_BCF32EB3BAE64E8C821572B20358FE83

#include <memory>
#include "window_references/window_references.hpp"
#include "../loop/logic/updatables/updatable.hpp"

class ScreenCleaner : public IUpdatable
{
private:
    const std::shared_ptr<WindowReferences> &m_window_references_;

public:
    explicit ScreenCleaner(const std::shared_ptr<WindowReferences> &window_references);
    ~ScreenCleaner() override = default;

    void Update(float delta) override;
};

#endif
