#pragma once
#include "ShootingComponent.h"
#include "BulletManager.h"
#include <SpriteComponent.h>

namespace dae
{
	ShootingComponent::ShootingComponent(GameObject* owner, float speed) 
		:BaseComponent(owner), m_Speed(speed)
	{
		
	}

	

	void ShootingComponent::Shoot()
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
		}
	}

	void ShootingComponent::SetDirection(glm::vec2 direction)
	{
		m_Direction.x += direction.x;
		m_Direction.y += direction.y;
	}
}