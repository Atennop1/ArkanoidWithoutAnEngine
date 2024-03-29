#ifndef ARKANOIDWITHOUTANENGINE_8858B4CB865344A4B80E85D21AC1B87D
#define ARKANOIDWITHOUTANENGINE_8858B4CB865344A4B80E85D21AC1B87D

#include <memory>
#include "../../DTOs/Vector2/vector2.h"
#include "../../loop/updatables/updatable.h"
#include "../View/platform_view.h"

class Platform : public IUpdatable
{
private:
    Vector2 m_platform_position_ { };
    const std::unique_ptr<PlatformView> m_platform_view_;

public:
    explicit Platform(std::unique_ptr<PlatformView> &platform_view);
    ~Platform() override = default;

    void Update(float delta) override;
    void Move(Vector2 move_vector);
};

#endif
