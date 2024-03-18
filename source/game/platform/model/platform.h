#ifndef ARKANOIDWITHOUTANENGINE_8858B4CB865344A4B80E85D21AC1B87D
#define ARKANOIDWITHOUTANENGINE_8858B4CB865344A4B80E85D21AC1B87D

#include "../../DTOs/Vector2/vector2.h"
#include "../../loop/updatables/updatable.h"
#include "../View/platform_view.h"

class Platform : IUpdatable
{
private:
    Vector2 m_platform_position_ { };
    const PlatformView &m_platform_view_;

public:
    explicit Platform(const PlatformView &platform_view);
    ~Platform() override = default;

    void Update(float delta) override;
    void Move(Vector2 move_vector);
};

#endif
