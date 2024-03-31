#ifndef ARKANOIDWITHOUTANENGINE_4DAF1F21C8B048A1AD3A916EA377A2ED
#define ARKANOIDWITHOUTANENGINE_4DAF1F21C8B048A1AD3A916EA377A2ED

#include "../rendering/window_references/window_references.hpp"
#include "view/level_view.hpp"
#include "map/level_map.hpp"
#include "../loop/updatables/updatable.hpp"

class Level : public IUpdatable
{
private:
    const std::unique_ptr<LevelMap> m_map_;
    const std::unique_ptr<LevelView> m_level_view_;

public:
    Level(std::unique_ptr<LevelMap> &&map, std::unique_ptr<LevelView> &&level_view);
    ~Level() override = default;

    void Update(float delta) override;
};

#endif
