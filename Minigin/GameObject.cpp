#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::GameObject::~GameObject() = default;

void dae::GameObject::Update()
{
	for (int idx{}; idx < static_cast<int>(m_Components.size()); idx++)
	{
		m_Components[idx]->Update();
	}
}

void dae::GameObject::Render() const
{
	for (int idx{}; idx < static_cast<int>(m_Components.size()); idx++)
	{
		m_Components[idx]->Render();
	}
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_transform.SetPosition(x, y, 0.0f);
}


