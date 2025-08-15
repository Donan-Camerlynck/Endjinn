#pragma once
#include "ShootingComponent.h"
#include "BulletManager.h"
#include <SpriteComponent.h>

namespace dae
{
	ShootingComponent::ShootingComponent(GameObject* owner, float speed) 
		:BaseComponent(owner), m_Speed(speed), m_bShouldShoot{false}
	{
		
	}

	void ShootingComponent::Update()
	{
		if (m_bShouldShoot)
		{
			
			if (m_Direction.x == 0 && m_Direction.y == 0)
			{
				return;
			}
			else
			{
				glm::vec2 pos = GetOwner()->GetWorldPos();
				BulletManager::GetInstance().SpawnBullet(pos, glm::normalize(m_Direction) * m_Speed, GetOwner());
				m_Direction.x = 0;
				m_Direction.y = 0;
				m_bShouldShoot = false;
			}
		}
	}

	void ShootingComponent::Shoot()
	{
		m_bShouldShoot = true;
	}

	void ShootingComponent::SetDirection(glm::vec2 direction)
	{
		if (direction.x != 0 && direction.y != 0)
		{
 			m_Direction.x = direction.x;
			m_Direction.y = direction.y;
		}
		else if (direction.x == 0 && direction.y != 0)
		{
			m_Direction.y = direction.y;
		}
		else if (direction.x != 0 && direction.y == 0)
		{
			m_Direction.x = direction.x;
		}
		
	}
}