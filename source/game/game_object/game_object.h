#include <iostream>
#include <vector>


class IGameObject
{
private:
    bool m_is_active_;

public:
    virtual ~IGameObject() = default;

    bool IsActive()
    {
        return m_is_active_;
    }
};

