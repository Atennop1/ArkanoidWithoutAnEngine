#pragma once
#include "Windows.h"

class ISystemUpdatable
{
public:
    virtual ~ISystemUpdatable() = default;
    virtual void Update(MSG *message) = 0;
};
