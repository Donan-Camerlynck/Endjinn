#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Singleton.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);

		void Initialize();
		void Update();
		void Render();
		void End();
		dae::Scene& LoadLevel0();
		dae::Scene& LoadLevel1();
		dae::Scene& LoadLevel2();
		dae::Scene& GetScene();
		void ClearScenes();
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_scenes;
	};
}
