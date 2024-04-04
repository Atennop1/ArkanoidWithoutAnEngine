#ifndef ARKANOIDWITHOUTANENGINE_5927CB008F20454CA6ECC117FD5E93ED
#define ARKANOIDWITHOUTANENGINE_5927CB008F20454CA6ECC117FD5E93ED

#include "../../rendering/window_references/window_references.hpp"
#include "../../../../libs/Box2D/include/Box2D.hpp"
#include <memory>

class PlatformView
{
private:
    SDL_Texture *m_platform_texture_;
    const std::shared_ptr<WindowReferences> &m_window_references_;

public:
    explicit PlatformView(const std::shared_ptr<WindowReferences> &window_references);
    ~PlatformView();

    void Display(Box2D::Vector2 position) const;
};

#endif
