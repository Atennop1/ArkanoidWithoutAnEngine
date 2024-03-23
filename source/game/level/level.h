#ifndef ARKANOIDWITHOUTANENGINE_0103D3895F094EC7AA8D9C8EAA1BE87F
#define ARKANOIDWITHOUTANENGINE_0103D3895F094EC7AA8D9C8EAA1BE87F

#include "../dtos/window_references/window_references.h"
#include "view/level_view.h"
#include "map/level_map.h"

class Level : public IUpdatable
{
private:
    const std::unique_ptr<LevelMap> m_map_;
    const std::unique_ptr<LevelView> m_level_view_;

public:
    Level(std::unique_ptr<LevelMap> &map, std::unique_ptr<LevelView> &level_view);
    ~Level() override = default;

    void Update(float delta) override;
};

#endif
