#include "MovementComponent.h"
#include "GameObject.h"
#include "Level.h"

dae::MovementComponent::MovementComponent(GameObject* owner, float speed)
	:BaseComponent(owner), m_Speed(speed)
{

}

void dae::MovementComponent::Update()
{
    if (m_bNeedsToMove)
    {
        GetOwner()->SetWorldPos(m_DesiredPosition);
    }
}

void dae::MovementComponent::Move(glm::vec2 direction)
{
    if (!m_bNeedsToMove)
    {
        m_bNeedsToMove = CanMoveTo(direction);
    }
}

bool dae::MovementComponent::CanMoveTo(glm::vec2 direction)
{
    dae::Level& level = dae::Level::GetInstance();

    glm::vec2 newPosition = GetOwner()->GetWorldPos() + direction * m_Speed; // proposed position

    Rect futureAABB;
    futureAABB.position = newPosition; // top-left corner of the character
    futureAABB.size = glm::vec2(level.GetTileWidth() * 2, level.GetTileHeight() * 2);

    bool bCanMoveTo = level.AreAllTilesWalkable(futureAABB, static_cast<float>(level.GetTileWidth()), static_cast<float>(level.GetTileHeight()));
    if (bCanMoveTo)
    {
        m_DesiredPosition = newPosition;
    }
    return bCanMoveTo;
}


