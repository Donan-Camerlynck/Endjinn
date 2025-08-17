#pragma once
#include "BulletManager.h"
#include "TimeManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Texture2D.h"
#include <iostream>
#include "ScoreComponent.h"
#include "HealthComponent.h"

namespace dae
{
   

    void BulletManager::SpawnBullet(glm::vec2 pos, glm::vec2 vel, GameObject* caster, bool isPlayer)
    {
        m_Bullets.push_back(std::make_unique<Bullet>(pos, vel, caster));
        m_Bullets.back()->GetSubject()->AddObserver(caster->GetComponent<ScoreComponent>());
        if (isPlayer)
        {
            for (auto& enemy : m_Enemies)
            {
                m_Bullets.back()->GetSubject()->AddObserver(enemy->GetComponent<HealthComponent>());
            }
        }
        else
        {
            for (auto& player : m_Players)
            {
                m_Bullets.back()->GetSubject()->AddObserver(player->GetComponent<HealthComponent>());
            }
        }
       
    }

	void BulletManager::Update()
	{
        for (auto& bullet : m_Bullets) 
        
        if(bullet->m_bActive)
        {
            bullet->Update();
        }

        CheckCollision();

        // Remove dead bullets
        m_Bullets.erase(
            std::remove_if(m_Bullets.begin(), m_Bullets.end(),
                [](const std::unique_ptr<Bullet>& b) { return !b.get()->m_bActive; }),
            m_Bullets.end()
        );
	}

    void BulletManager::Render()
    {
        glm::ivec2 spritesize = m_pTexture->GetSize();
        for (const auto& bullet : m_Bullets) 
        {
            if (bullet->m_bActive)
            {
                Renderer::GetInstance().RenderTexture(*m_pTexture, bullet->GetPos().x - spritesize.x/2, bullet->GetPos().y - spritesize.y / 2);
            }
        }
    }

    void BulletManager::SetTexture(const std::string& filename)
    {
        m_pTexture = ResourceManager::GetInstance().LoadTexture(filename);
    }

    void BulletManager::ClearPlayersEnemies()
    {
        m_Players.clear();
        m_Enemies.clear();
    }

    void BulletManager::AddPlayer(GameObject* player)
    {
        m_Players.push_back(player);
    }

    void BulletManager::AddEnemy(GameObject* enemy)
    {
        m_Enemies.push_back(enemy);
    }

    void BulletManager::CheckCollision()
    {
        for (auto& bullet : m_Bullets)
        {
            for (auto& enemy : m_Enemies)
            {
                if (std::find(m_Enemies.begin(), m_Enemies.end(), bullet->GetCaster()) != m_Enemies.end())
                {
                    continue;
                }
                float distance = glm::distance(enemy->GetWorldPos(), bullet->GetPos());
                if (distance < 10.f)
                {
                    bullet->GetSubject()->NotifyAll({ EventType::OnDamage, enemy, 1 });
                    bullet->m_bActive = false;
                    std::cout << "hit\n";
                }
            }
            for (auto& player : m_Players)
            {
                if (std::find(m_Players.begin(), m_Players.end(), bullet->GetCaster()) != m_Players.end())
                {
                    continue;
                }
                float distance = glm::distance(player->GetWorldPos(), bullet->GetPos());
                if (distance < 10.f)
                {
                    bullet->GetSubject()->NotifyAll({ EventType::OnDamage, player, 1 });
                    bullet->m_bActive = false;
                    std::cout << "hit\n";
                }
            }
        }
    }
}