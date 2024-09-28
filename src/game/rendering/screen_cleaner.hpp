#ifndef ARKANOIDWITHOUTANENGINE_BCF32EB3BAE64E8C821572B20358FE83
#define ARKANOIDWITHOUTANENGINE_BCF32EB3BAE64E8C821572B20358FE83

#include "window_references/window_references.hpp"
#include "../loop/game_loop_object.hpp"

namespace arkanoid
{
    class ScreenCleaner : public IGameLoopObject
    {
    private:
        const WindowReferences &m_window_references_;

    public:
        explicit ScreenCleaner(const WindowReferences &window_references);

        ~ScreenCleaner() override = default;

        void Update(float delta) override;
    };
}

#endif
