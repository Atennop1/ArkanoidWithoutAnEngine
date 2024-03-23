#ifndef ARKANOIDWITHOUTANENGINE_92ABB16FB39C42AF8EDF0477A386021D
#define ARKANOIDWITHOUTANENGINE_92ABB16FB39C42AF8EDF0477A386021D

#include "../../dtos/window_references/window_references.h"
#include "../../loop/updatables/updatable.h"
#include "SDL.h"
#include "../map/level_map.h"
#include <array>
#include <memory>

class LevelView
{
private:
    const int m_level_offset_x_ = 8;
    const int m_level_offset_y_ = 6;

    int m_brick_width_;
    int m_brick_height_;

    const std::shared_ptr<WindowReferences> &m_window_references_;
    SDL_Texture *m_violet_brick_texture_;
    SDL_Texture *m_blue_brick_texture_;

    void DisplayBrick(SDL_Texture *texture, IntVector2 position) const;

public:
    explicit LevelView(const std::shared_ptr<WindowReferences> &window_references);
    ~LevelView();

    void Display(const LevelMap &map) const;
};

#endif
