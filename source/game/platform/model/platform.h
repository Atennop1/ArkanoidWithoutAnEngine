#pragma once
#include "../../DTOs/Vector2/vector2.h"
#include "../../loop/updatables/updatable.h"
#include "../View/platform_view.h"

class Platform : IUpdatable
{
private:
    Vector2 m_platform_position_;
    PlatformView *m_platform_view_;
    
public:
    Platform(PlatformView *platform_view);
    ~Platform() override;

    void Update(float delta) override;
    void Move(Vector2 move_vector);
};
