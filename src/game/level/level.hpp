#ifndef ARKANOIDWITHOUTANENGINE_4DAF1F21C8B048A1AD3A916EA377A2ED
#define ARKANOIDWITHOUTANENGINE_4DAF1F21C8B048A1AD3A916EA377A2ED

#include "../rendering/window_references/window_references.hpp"
#include "view/level_view.hpp"
#include "map/level_map.hpp"
#include "../loop/logic/updatables/updatable.hpp"

class Level : public IUpdatable
{
private:
    const LevelMap &m_map_;
    const LevelView &m_level_view_;

public:
    Level(const LevelMap &map, const LevelView &level_view);
    ~Level() override = default;

    void Update(float delta) override;
};

#endif
