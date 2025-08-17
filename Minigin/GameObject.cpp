#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include <iostream>

dae::GameObject::GameObject(Scene* pOwner, RenderLayer renderLayer) :
	m_pScene{ pOwner }, m_RenderLayer(renderLayer)
{
	
}

dae::GameObject::~GameObject() = default;

void dae::GameObject::Initialize()
{
	for (int idx{}; idx < static_cast<int>(m_Components.size()); idx++)
	{
		m_Components[idx]->Initialize();
	}		
	for (int idx{}; idx < static_cast<int>(m_Children.size()); idx++)
	{
		m_Children[idx]->Initialize();
	}	
}

void dae::GameObject::Update()
{
	UpdateWorldPos();
	for (int idx{}; idx < static_cast<int>(m_Components.size()); idx++)
	{
		m_Components[idx]->Update();
	}
	for (int idx{}; idx < static_cast<int>(m_Children.size()); idx++)
	{
		m_Children[idx]->Update();
	}
}

void dae::GameObject::Render() const
{
	for (int idx{}; idx < static_cast<int>(m_Components.size()); idx++)
	{
		m_Components[idx]->Render();
	}
	for (int idx{}; idx < static_cast<int>(m_Children.size()); idx++)
	{
		m_Children[idx]->Render();
	}
}

void dae::GameObject::SetPosition(int x, int y)
{
	m_transform.SetPosition(x, y, 0);
}


void dae::GameObject::SetLocalPos(glm::vec2 localPos)
{
	m_LocalPos = localPos;
	SetPositionDirty();
}

void dae::GameObject::SetWorldPos(glm::vec2 worldPos)
{
	m_WorldPos = worldPos;
	SetPositionDirty();
}

void dae::GameObject::SetPositionDirty()
{
	m_bPositionDirty = true;
}

void dae::GameObject::SetActive(bool bActive)
{
	m_bActive = bActive;
	if (!bActive)
	{
		std::cout << "set not active\n";
	}
}

void dae::GameObject::UpdateWorldPos()
{
	if (m_bPositionDirty)
	{
		if (m_pParent == nullptr)
			m_WorldPos = m_LocalPos;
		else
			m_WorldPos = m_pParent->GetWorldPos() + m_LocalPos;
	}
	m_bPositionDirty = false;
}

void dae::GameObject::End()
{
	for (int idx{}; idx < static_cast<int>(m_Components.size()); idx++)
	{
		m_Components[idx]->Update();
	}
	m_Components.clear();

	
	for (int idx{}; idx < static_cast<int>(m_Children.size()); idx++)
	{
		m_Children[idx]->End();
	}
	m_Children.clear();
}

bool dae::GameObject::IsChild(GameObject* parent)
{
	if (!parent) return false; 

	auto& children = parent->m_Children; 

	return std::any_of(children.begin(), children.end(),
		[this](const std::unique_ptr<GameObject>& child) {
			return child.get() == this; 
		});
}

void dae::GameObject::SetParent(GameObject* parent, bool keepWorldPos)
{
	if (IsChild(parent) || parent == this || m_pParent == parent)
		return;
	if (parent == nullptr)
		SetLocalPos(GetWorldPos());
	else
	{
		if (keepWorldPos)
			SetLocalPos(GetWorldPos() - parent->GetWorldPos());
		SetPositionDirty();
	}
	std::unique_ptr<GameObject> child;
	if (m_pParent)
	{
		auto it = std::find_if(m_pParent->m_Children.begin(), m_pParent->m_Children.end(), [this](const auto& go) {
			return go.get() == this;
			});


		if (it != m_pParent->m_Children.end())
		{
			child = std::move(*it);
			m_pParent->m_Children.erase(it);
		}
	}
	m_pParent = parent;
	if (m_pParent)
	{
		if (!child)
		{			
			child = m_pScene->Release(this);
		}
		m_pParent->m_Children.push_back(std::move(child));
	}
	else
	{
		if (child) m_pScene->Add(std::move(child));
	}
}

dae::GameObject* dae::GameObject::GetChildAt(int idx)
{
	return m_Children[idx].get();
}
