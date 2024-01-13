#pragma once
#include "../../DTOs/Vector2/vector2.h"
#include "../../loop/updatable.h"
#include "../View/platform_view.h"

class Platform : IUpdatable
{
private:
    Vector2 m_platform_position_;
    PlatformView m_platform_view_;
    
public:
    explicit Platform(const PlatformView &platform_view);
    ~Platform() override = default;

    void Update(float delta) override;
    void Move(Vector2 move_vector);
};
