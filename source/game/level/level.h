#ifndef ARKANOIDWITHOUTANENGINE_0103D3895F094EC7AA8D9C8EAA1BE87F
#define ARKANOIDWITHOUTANENGINE_0103D3895F094EC7AA8D9C8EAA1BE87F

#include "../dtos/window_references/window_references.h"
#include "view/level_view.h"

class Level : IUpdatable
{
private:
    const std::array<std::array<char, 12>, 14> &m_map_;
    const LevelView &m_level_view_;

public:
    Level(const std::array<std::array<char, 12>, 14> &map, const LevelView &level_view);
    ~Level() override = default;

    void Update(const float &delta) override;
};

#endif //ARKANOIDWITHOUTANENGINE_0103D3895F094EC7AA8D9C8EAA1BE87F
