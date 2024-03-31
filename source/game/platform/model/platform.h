#ifndef ARKANOIDWITHOUTANENGINE_8858B4CB865344A4B80E85D21AC1B87D
#define ARKANOIDWITHOUTANENGINE_8858B4CB865344A4B80E85D21AC1B87D

#include "../../loop/updatables/updatable.h"
#include "../View/platform_view.h"
#include "Box2D/Box2D.hpp"
#include <memory>

class Platform : public IUpdatable
{
private:
    Box2D::Vec2 m_platform_position_ { };
    std::unique_ptr<PlatformView> m_platform_view_;

public:
    explicit Platform(std::unique_ptr<PlatformView> &&platform_view);
    ~Platform() override = default;

    void Update(float delta) override;
    void Move(Box2D::Vec2 move_vector);
};

#endif
