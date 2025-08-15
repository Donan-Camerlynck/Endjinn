#pragma once
#include "Bullet.h"
#include "TimeManager.h"
#include "Tile.h"
#include "Level.h"


namespace dae
{
	Bullet::Bullet(glm::vec2 position, glm::vec2 velocity, GameObject* caster)
		:m_Position(position), m_Velocity(velocity), m_pCaster(caster)
	{

	}


	Bullet::~Bullet() = default;

	void Bullet::Update()
	{
        
		glm::vec2 oldPos = m_Position;
		m_Position += m_Velocity * TimeManager::GetInstance().GetDeltaTime();

		//check collision
		Tile* CurrentTile = Level::GetInstance().GetTileAtPos(m_Position);
        if (CurrentTile->GetType() == TileType::wall)
        {
            m_Bounces++;
            if (m_Bounces >= m_MaxBounces)
            {
                m_bActive = false;
            }
            else
            {
                //determine bounce
                glm::vec2 tileCenter = CurrentTile->m_Coordinates; // e.g., tilePos + half tile size
                glm::vec2 diff = oldPos - tileCenter;

                if (std::abs(diff.x) > std::abs(diff.y))
                {
                    m_Velocity.x *= -1;
                }
                else if (std::abs(diff.x) < std::abs(diff.y))
                {
                    m_Velocity.y *= -1;
                }
                else
                {
                    m_Velocity.x *= -1;
                    m_Velocity.y *= -1;
                }
                m_Position = oldPos;
            }
		}

	}

    
}