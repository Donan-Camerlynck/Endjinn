#pragma once
#include "ShootingComponent.h"
#include "BulletManager.h"
#include <SpriteComponent.h>
#include "Soundsystem.h"
#include "ResourceManager.h"
#include <filesystem>
#include <string>

namespace dae
{
	ShootingComponent::ShootingComponent(GameObject* owner, float speed, bool bIsPlayer) 
		:BaseComponent(owner), m_Speed(speed), m_bShouldShoot{false}, m_bIsPlayer(bIsPlayer)
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
				BulletManager::GetInstance().SpawnBullet(pos, glm::normalize(m_Direction) * m_Speed, GetOwner(), m_bIsPlayer);
				std::filesystem::path path = ResourceManager::GetInstance().GetPath() / std::string{"Sounds/Shoot.mp3"};
				const std::string soundPath = path.string();
				SoundSystem::GetInstance().playSound(soundPath, 1);
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