#include "../dtos/window_references/window_references.h"
#include "view/level_view.h"

class Level : IUpdatable
{
private:
    std::array<std::array<char, 12>, 14> m_map_;
    LevelView *m_level_view_;

public:
    Level(std::array<std::array<char, 12>, 14> map, LevelView *level_view);
    ~Level() override;

    void Update(float delta) override;
};
