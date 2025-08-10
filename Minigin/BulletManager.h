#pragma once
#include "Singleton.h"
#include <vector>
#include "Bullet.h"

namespace dae
{
	class BulletManager : public Singleton<BulletManager>
	{
	public:
		
		void Update();
		void Render();
		void End();
		void SpawnBullet(glm::vec2 pos, glm::vec2 vel, GameObject* caster);
		void SetTexture(const std::string& filename);

	private:
		std::vector<std::unique_ptr<Bullet>> m_Bullets;
		std::shared_ptr<Texture2D> m_pTexture{};
	};
}