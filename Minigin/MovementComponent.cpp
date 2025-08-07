#include "MovementComponent.h"
#include "GameObject.h"
#include "Level.h"
#include "Renderer.h"
#include "TimeManager.h"

dae::MovementComponent::MovementComponent(GameObject* owner, float speed)
	:BaseComponent(owner), m_Speed(speed)
{

}

void dae::MovementComponent::Update()
{
    if (m_bNeedsToMove)
    {
        GetOwner()->SetLocalPos(GetOwner()->GetWorldPos() + m_Direction * m_Speed * dae::TimeManager::GetInstance().GetDeltaTime());
        m_bNeedsToMove = false;
    }
}

void dae::MovementComponent::Render() const
{
    dae::Level& level = dae::Level::GetInstance();
    Rect futureAABB;
    futureAABB.position = GetOwner()->GetWorldPos();
    futureAABB.size = glm::vec2(level.GetTileWidth() * 2 , level.GetTileHeight() * 2 );
    dae::Renderer::GetInstance().RenderDebugBox(futureAABB.position.x, futureAABB.position.y, futureAABB.size.x, futureAABB.size.y);
}

void dae::MovementComponent::Move(glm::vec2 direction)
{
    if (!m_bNeedsToMove)
    {
        m_bNeedsToMove = CanMoveTo(direction);
        m_Direction = direction;
    }
}

bool dae::MovementComponent::CanMoveTo(glm::vec2 direction)
{
    dae::Level& level = dae::Level::GetInstance();

    glm::vec2 newPosition = GetOwner()->GetWorldPos() + direction; // proposed position

    Rect futureAABB;
    futureAABB.position = newPosition; // top-left corner of the character
    futureAABB.size = glm::vec2(level.GetTileWidth() * 2 , level.GetTileHeight() * 2 );

    bool bCanMoveTo = level.AreAllTilesWalkable(futureAABB);
    if (bCanMoveTo)
    {
        m_DesiredPosition = newPosition;
    }
    return bCanMoveTo;
}


