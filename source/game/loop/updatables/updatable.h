#pragma once

class IUpdatable
{
public:
    virtual ~IUpdatable() = default;
    virtual void Update(const float &delta) = 0;
};
