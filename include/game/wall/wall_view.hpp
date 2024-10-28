#ifndef ARKANOIDWITHOUTANENGINE_INCLUDE_GAME_WALL_WALL_VIEW_HPP_
#define ARKANOIDWITHOUTANENGINE_INCLUDE_GAME_WALL_WALL_VIEW_HPP_

#include "engine/rendering/window_references.hpp"
#include "engine/math/vector2.hpp"

namespace arkanoid
{
class WallView
{
public:
    WallView(const WindowReferences &window_references, const char *texture_file_path);
    ~WallView();

    void Display(Vector2 position) const;

private:
    SDL_Texture *wall_texture_;
    const WindowReferences &window_references_;
};
}

#endif
