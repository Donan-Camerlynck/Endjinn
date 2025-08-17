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
		void SpawnBullet(glm::vec2 pos, glm::vec2 vel, GameObject* caster, bool isPlayer);
		void CheckCollision();
		void SetTexture(const std::string& filename);
		void AddPlayer(GameObject* player);
		void AddEnemy(GameObject* enemy);
		void ClearPlayersEnemies();

	private:
		std::vector<std::unique_ptr<Bullet>> m_Bullets;
		std::shared_ptr<Texture2D> m_pTexture{};
		std::vector<GameObject*> m_Players{};
		std::vector<GameObject*> m_Enemies{};
	};
}