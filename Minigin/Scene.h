#pragma once
#include "SceneManager.h"
#include "GameObject.h"



namespace dae
{

	
	class Scene final
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		GameObject* Add(std::unique_ptr<GameObject> object);
		void Remove(std::unique_ptr<GameObject> object);
		void RemoveAll();
		std::unique_ptr<GameObject> Release(GameObject* object);

		void Initialize();
		void Update();
		void Render() const;
		void End();

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;


	private: 
		explicit Scene(const std::string& name);


		std::string m_name;
		std::vector < std::unique_ptr<GameObject>> m_objects{};


		static unsigned int m_idCounter; 
	};

}
