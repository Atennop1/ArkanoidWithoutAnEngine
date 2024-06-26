#include "level_layouts.hpp"

std::array<std::array<char, 12>, 14> LevelLayouts::m_empty_ = std::array<std::array<char, 12>, 14>
{{
    {{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }},
    {{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }},
    {{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }},
    {{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }},
    {{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }},
    {{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }},
    {{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }},
    {{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }},
    {{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }},
    {{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }},
    {{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }},
    {{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }},
    {{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }},
    {{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }}
}};

std::array<std::array<char, 12>, 14> LevelLayouts::m_k_first_ = std::array<std::array<char, 12>, 14>
{{
    {{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }},
    {{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }},
    {{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }},
    {{ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 }},
    {{ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 }},
    {{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }},
    {{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }},
    {{ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 }},
    {{ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 }},
    {{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }},
    {{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }},
    {{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }},
    {{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }},
    {{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }}
}};

std::array<std::array<char, 12>, 14> &LevelLayouts::Empty()
{
    return m_empty_;
}

std::array<std::array<char, 12>, 14>& LevelLayouts::First()
{
    return m_k_first_;
}
