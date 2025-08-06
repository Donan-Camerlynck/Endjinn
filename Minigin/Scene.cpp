#include "Scene.h"
#include "GameObject.h"
#include "Level.h"

#include <algorithm>
#include <stdexcept>

using namespace dae;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name) : m_name(name) {}

Scene::~Scene() = default;

GameObject* Scene::Add(std::unique_ptr<GameObject> object)
{

	if (!object)
	{
		return nullptr;
	}
	auto obj = std::move(object);
	const auto pRaw = obj.get();

	m_objects.emplace_back(std::move(obj));
	return pRaw;
}

void Scene::Remove(std::unique_ptr<GameObject> object)
{
	m_objects.erase(std::remove(m_objects.begin(), m_objects.end(), object), m_objects.end());
}

void Scene::RemoveAll()
{
	m_objects.clear();
}

std::unique_ptr<GameObject> dae::Scene::Release(GameObject* object)
{

	
		auto it = std::find_if(m_objects.begin(), m_objects.end(), [object](const auto& rootgo) {
			return rootgo.get() == object;
			});

		std::unique_ptr<GameObject> child;
		if (it != m_objects.end())
		{
			child = std::move(*it);
			m_objects.erase(it);
		}

		return child;
	
}

void dae::Scene::Initialize()
{
	for (auto& object : m_objects)
	{
		object->Initialize();
	}
}

void Scene::Update()
{
	for(auto& object : m_objects)
	{
		object->Update();
	}
}

void Scene::Render() const
{
	Level::GetInstance().Render();
	for (int i{ }; i < static_cast<int>(RenderLayer::numLayers); ++i)
	{
		for (const auto& object : m_objects)
		{
			if (static_cast<int>(object->GetRenderLayer()) == i)
			{
				object->Render();
			}
		}
	}
}

void dae::Scene::End()
{
	for (const auto& object : m_objects)
	{
		object->End();
	}
}

