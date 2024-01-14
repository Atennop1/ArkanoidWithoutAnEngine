#ifndef ARKANOIDWITHOUTANENGINE_D155A55943A14D8386145E96D36244F5
#define ARKANOIDWITHOUTANENGINE_D155A55943A14D8386145E96D36244F5

class IGameObject
{
private:
    bool m_is_active_ { };

public:
    virtual ~IGameObject() = default;

    bool IsActive() const
    {
        return m_is_active_;
    }
};

#endif //ARKANOIDWITHOUTANENGINE_D155A55943A14D8386145E96D36244F5
