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
			glm::vec2 pos = GetOwner()->GetWorldPos() + glm::vec2{ GetOwner()->GetComponent<SpriteComponent>()->GetSize().x / 2, GetOwner()->GetComponent<SpriteComponent>()->GetSize().y / 2 };
			BulletManager::GetInstance().SpawnBullet(pos, glm::normalize(m_Direction) * m_Speed, GetOwner());
		}
		
	}

	void ShootingComponent::SetDirection(glm::vec2 direction)
	{
		m_Direction.x += direction.x;
		m_Direction.y += direction.y;
		if (m_Direction.x > 1)
		{
			m_Direction.x = 1;
		}
		if (m_Direction.x < -1)
		{
			m_Direction.x = -1;
		}
		if (m_Direction.y > 1)
		{
			m_Direction.y = 1;
		}
		if (m_Direction.y < -1)
		{
			m_Direction.y = -1;
		}
	}
}