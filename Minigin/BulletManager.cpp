#pragma once
#include "BulletManager.h"
#include "TimeManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Texture2D.h"

namespace dae
{
   

    void BulletManager::SpawnBullet(glm::vec2 pos, glm::vec2 vel, GameObject* caster)
    {
        m_Bullets.push_back(std::make_unique<Bullet>(pos, vel, caster));
    }

	void BulletManager::Update()
	{
        for (auto& bullet : m_Bullets) 
        
        if(bullet->m_bActive)
        {
            bullet->Update();
        }

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
}