#ifndef ARKANOIDWITHOUTANENGINE_515C9CA98BC44C93A805F15EDDD26BCE
#define ARKANOIDWITHOUTANENGINE_515C9CA98BC44C93A805F15EDDD26BCE

#include "../../loop/game_loop_object.hpp"
#include "../view/platform_view.hpp"
#include "Box2D.hpp"
#include "shared_pointer.hpp"

class Platform : public IGameLoopObject
{
private:
    Box2D::Vector2 m_platform_position_ { };
    SharedPointer<PlatformView> m_platform_view_;

public:
    explicit Platform(SharedPointer<PlatformView> &platform_view);
    ~Platform() override = default;

    void Update(float delta) override;
    void Move(Box2D::Vector2 move_vector);
};

#endif
