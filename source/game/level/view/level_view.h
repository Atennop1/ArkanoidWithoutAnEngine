#include "SDL.h"
#include "../../dtos/window_references/window_references.h"
#include "../../loop/updatable.h"
#include <array>

class LevelView
{
private:
    const int m_level_offset_x_ = 8;
    const int m_level_offset_y_ = 6;

    int m_brick_width_;
    int m_brick_height_;

    SDL_Rect m_displaying_rect_ { };
    WindowReferences &m_window_references_;

    SDL_Texture *m_violet_brick_texture_;
    SDL_Texture *m_blue_brick_texture_;

    void DisplayBrick(SDL_Texture *texture, IntVector2 position);

public:
    explicit LevelView(const WindowReferences &window_references);
    ~LevelView();

    void Display(std::array<std::array<char, 12>, 14> level);
};

