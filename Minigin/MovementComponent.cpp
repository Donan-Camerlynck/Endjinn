#include "MovementComponent.h"
#include "GameObject.h"
#include "Level.h"
#include "Renderer.h"
#include "TimeManager.h"
#include <iostream>

dae::MovementComponent::MovementComponent(GameObject* owner, float speed)
	:BaseComponent(owner), m_Speed(speed)
{

}

void dae::MovementComponent::Update()
{
    if (m_bNeedsToMove)
    {
        if (!CanMoveTo(m_Direction))
        {
            m_bNeedsToMove = false;
            return;
        }
       // dae::Level& level= dae::Level::GetInstance();
        glm::vec2 oldPos = GetOwner()->GetWorldPos();
        glm::vec2 dir = m_Direction;
        glm::vec2 offset{};
        m_MoveVector = dir * m_Speed * dae::TimeManager::GetInstance().GetDeltaTime();

        if (m_MoveVector.x > 1.f)
        {
            offset.x = 1.f;
            m_MoveVector.x -= 1.f;
        }
        if (m_MoveVector.x < -1.f)
        {
            offset.x = -1.f;
            m_MoveVector.x += 1.f;
        }
        if (m_MoveVector.y > 1.f)
        {
            offset.y = 1.f;
            m_MoveVector.y -= 1.f;
        }
        if (m_MoveVector.y < -1.f)
        {
            offset.y = -1.f;
            m_MoveVector.y += 1.f;
        }

        glm::vec2 updatedPos = oldPos + offset;
       
        GetOwner()->SetLocalPos(updatedPos);
        


        //std::cout << "oldPos: " << oldPos.x << " " << oldPos.y << " newPos: " << newPos.x << " " << newPos.y << std::endl;
        m_bNeedsToMove = false;

    }
    
}

void dae::MovementComponent::Render() const
{
    dae::Level& level = dae::Level::GetInstance();
    Rect futureAABB{};
    futureAABB.position = GetOwner()->GetWorldPos();
    futureAABB.size = glm::vec2(level.GetTileWidth()  , level.GetTileHeight() );
    dae::Renderer::GetInstance().RenderDebugBox(futureAABB.position.x - futureAABB.size.x /2, futureAABB.position.y - futureAABB.size.y /2, futureAABB.size.x, futureAABB.size.y);
}

void dae::MovementComponent::Move(glm::ivec2 direction)
{
    
    m_Direction = direction;
    m_bNeedsToMove = true;
   
}

bool dae::MovementComponent::CanMoveTo(glm::ivec2 direction)
{
    dae::Level& level = dae::Level::GetInstance();

    //glm::ivec2 newPosition = GetOwner()->GetWorldPos() + direction * 2; // proposed position

    if (level.IsTileWalkable(GetOwner()->GetWorldPos(), direction))
    {
        return true;
    }
    else
    {
        return false;
    }

   
}


