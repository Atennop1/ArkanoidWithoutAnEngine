#include "Platform.h"

Platform::Platform(PlatformView* platformView)
{
    m_platformView = platformView;
    m_platformPosition = Vector2(100, 155);
}

void Platform::Move(Vector2 moveVector)
{
    m_platformPosition = Vector2(m_platformPosition.X() + moveVector.X(), m_platformPosition.Y() + moveVector.Y());
    m_platformView->Display(m_platformPosition);
}
