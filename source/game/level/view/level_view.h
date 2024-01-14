#include "SDL.h"
#include "../../dtos/window_references/window_references.h"
#include "../../loop/updatables/updatable.h"
#include <array>

class LevelView
{
private:
    const int m_level_offset_x_ = 8;
    const int m_level_offset_y_ = 6;

    int m_brick_width_;
    int m_brick_height_;

    const WindowReferences &m_window_references_;
    SDL_Texture *m_violet_brick_texture_;
    SDL_Texture *m_blue_brick_texture_;

    void DisplayBrick(SDL_Texture *texture, IntVector2 position) const;

public:
    explicit LevelView(const WindowReferences &window_references);
    ~LevelView();

    void Display(const std::array<std::array<char, 12>, 14> &level) const;
};

