#ifndef ARKANOIDWITHOUTANENGINE_INCLUDE_GAME_WALL_WALL_VIEW_HPP_
#define ARKANOIDWITHOUTANENGINE_INCLUDE_GAME_WALL_WALL_VIEW_HPP_

#include <genesis/rendering/window_references.hpp>
#include <genesis/math/vector2.hpp>

namespace arkanoid
{
class WallView
{
public:
    WallView(const genesis::WindowReferences &window_references, const char *texture_file_path);
    ~WallView();

    void Display(genesis::Vector2 position) const;

private:
    SDL_Texture *wall_texture_;
    genesis::WindowReferences window_references_;
};
}

#endif
