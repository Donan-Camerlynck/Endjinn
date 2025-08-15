#include "MovementComponent.h"
#include "GameObject.h"
#include "Level.h"
#include "Renderer.h"
#include "TimeManager.h"
#include <iostream>
#include <algorithm>

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



        glm::vec2 updatedPos = m_PosToCalcFrom + offset;
       
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
    dae::Level& level = dae::Level::GetInstance();
    glm::vec2 pos = GetOwner()->GetWorldPos();

    const int tileWidth = level.GetTileWidth(); 
    const int tileHeight = level.GetTileHeight();  

    const int snapPx = 4; 

    pos = SnapToGridIfClose(pos, direction, tileWidth, tileHeight, snapPx);

    m_PosToCalcFrom = pos;
    m_Direction = direction;
    m_bNeedsToMove = true;
}

inline glm::vec2 dae::MovementComponent::SnapToGridIfClose(glm::vec2 pos, glm::vec2 direction, int tileWidth, int tileHeight, int snapPixels)
{
    glm::vec2 snappedPos = pos;
    int column = static_cast<int>(pos.x)  / tileWidth;
    int row = static_cast<int>(pos.y) / tileHeight;
    glm::vec2 closestTile{column * tileWidth + tileWidth / 2.f, row * tileHeight + tileHeight / 2.f };
    glm::vec2 diff = pos - closestTile;
    int snapDir{};
    if (direction.x == 1 && direction.y == 0)
    {
        if (diff.y > 0)
        {
            snapDir = -1;
        }
        else if (diff.y < 0)
        {
            snapDir = 1;
        }
        int tempcolumn = (static_cast<int>(pos.y) + snapDir * snapPixels) / tileHeight;
        snappedPos.y = static_cast<float>(tempcolumn * tileHeight) + tileHeight/2.f;
    }
    else if (direction.y == 1 && direction.x == 0)
    {
        if (diff.x > 0)
        {
            snapDir = -1;
        }
        else if (diff.x < 0)
        {
            snapDir = 1;
        }
        int temprow = (static_cast<int>(pos.x) + snapDir * snapPixels) / tileWidth;
        snappedPos.x = static_cast<float>(temprow * tileWidth) + tileWidth / 2.f;
    }
    else if (direction.x == -1 && direction.y == 0)
    {
        if (diff.y > 0)
        {
            snapDir = -1;
        }
        else if (diff.y < 0)
        {
            snapDir = 1;
        }
        int tempcolumn = (static_cast<int>(pos.y) + snapDir * snapPixels) / tileHeight;
        snappedPos.y = static_cast<float>(tempcolumn * tileHeight) + tileHeight / 2.f;
    }
    else if (direction.y == -1 && direction.x == 0)
    {
        if (diff.x > 0)
        {
            snapDir = -1;
        }
        else if (diff.x < 0)
        {
            snapDir = 1;
        }
        int temprow = (static_cast<int>(pos.x) + snapDir * snapPixels) / tileWidth;
        snappedPos.x = static_cast<float>(temprow * tileWidth) + tileWidth / 2.f;
    }
    return snappedPos;
}

bool dae::MovementComponent::CanMoveTo(glm::ivec2 direction)
{
    dae::Level& level = dae::Level::GetInstance();
    glm::vec2 pos = m_PosToCalcFrom;
    //glm::ivec2 newPosition = GetOwner()->GetWorldPos() + direction * 2; // proposed position

    if (level.IsTileWalkable(pos, direction))
    {
        return true;
    }
    else
    {
        return false;
    }

   
}


