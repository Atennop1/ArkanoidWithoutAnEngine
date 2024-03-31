#ifndef ARKANOIDWITHOUTANENGINE_63298145BFEA4A2589E20B0AFEC992C7
#define ARKANOIDWITHOUTANENGINE_63298145BFEA4A2589E20B0AFEC992C7

#include "../../rendering/window_references/window_references.h"
#include "Box2D/Box2D.hpp"
#include <memory>

class PlatformView
{
private:
    SDL_Texture *m_platform_texture_;
    const std::shared_ptr<WindowReferences> &m_window_references_;

public:
    explicit PlatformView(const std::shared_ptr<WindowReferences> &window_references);
    ~PlatformView();

    void Display(Box2D::Vec2 position) const;
};

#endif
