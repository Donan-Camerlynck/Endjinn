#pragma once
#include "SceneManager.h"
#include "GameObject.h"



namespace dae
{

	
	class Scene final
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		GameObject* Add(std::unique_ptr<GameObject> object, bool isPlayer = false, bool isEnemy = false);
		void Remove(std::unique_ptr<GameObject> object);
		void RemoveAll();
		std::unique_ptr<GameObject> Release(GameObject* object);

		void Initialize();
		void Update();
		void Render() const;
		void End();
		void SetActive(bool bIsActive) { m_bIsActive = bIsActive; }
		bool IsActive() { return m_bIsActive; }

		std::vector<GameObject*> GetEnemyObjects() { return m_Enemies; }
		std::vector<GameObject*> GetPlayers() { return m_Players; }

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;


	private: 
		explicit Scene(const std::string& name);
		bool m_bIsActive{ false };

		std::string m_name;
		std::vector < std::unique_ptr<GameObject>> m_objects{};
		std::vector<GameObject*> m_Enemies;
		std::vector<GameObject*> m_Players;

		static unsigned int m_idCounter; 
	};

}
