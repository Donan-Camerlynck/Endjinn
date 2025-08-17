#include "SceneManager.h"
#include "Scene.h"
#include "InputManager.h"
#include <SDL.h>
#include "MoveCommand.h"

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
		if (scene->IsActive())
		{
			scene->Update();
		}
		
	}
}

void dae::SceneManager::Render()
{
	for (const auto& scene : m_scenes)
	{
		if (scene->IsActive()) scene->Render();
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

dae::Scene& dae::SceneManager::LoadLevel0()
{
	for (const auto& scene : m_scenes)
	{
		scene->SetActive(false);
	}
	m_scenes[0]->SetActive(true);
	return *m_scenes[0];
}

dae::Scene& dae::SceneManager::LoadLevel1()
{
	for (const auto& scene : m_scenes)
	{
		scene->SetActive(false);
	}
	m_scenes[1]->SetActive(true);
	return *m_scenes[1];
}

dae::Scene& dae::SceneManager::LoadLevel2()
{
	for (const auto& scene : m_scenes)
	{
		scene->SetActive(false);
	}
	m_scenes[2]->SetActive(true);
	return *m_scenes[2];
}

void dae::SceneManager::ClearScenes()
{
	End();
	m_scenes.clear();
}

dae::Scene& dae::SceneManager::GetScene()
{
	return *m_scenes.front();
}
