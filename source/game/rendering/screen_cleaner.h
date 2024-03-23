#ifndef ARKANOIDWITHOUTANENGINE_43CAC00ADE2A421E97BE51C8D45DF775
#define ARKANOIDWITHOUTANENGINE_43CAC00ADE2A421E97BE51C8D45DF775

#include <memory>
#include "../dtos/window_references/window_references.h"
#include "../loop/updatables/updatable.h"

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
