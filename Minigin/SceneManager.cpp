#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::Initialize()
{
	for (auto& scene : m_scenes)
	{
		scene->Initialize();
	}
}

void dae::SceneManager::Update()
{
	for(auto& scene : m_scenes)
	{
		scene->Update();
	}
}

void dae::SceneManager::Render()
{
	for (const auto& scene : m_scenes)
	{
		scene->Render();
	}
}

void dae::SceneManager::End()
{
	for (const auto& scene : m_scenes)
	{
		scene->End();
	}
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_scenes.push_back(scene);
	return *scene;
}
