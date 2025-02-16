#include "SpriteComponent.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "GameObject.h"

dae::SpriteComponent::SpriteComponent(GameObject* owner, const std::string& textureFilename) :
	BaseComponent(owner)
{
	SetTexture(textureFilename);
}



void dae::SpriteComponent::Update()
{
}

void dae::SpriteComponent::Render() const
{
	if (m_pTexture != nullptr)
	{
		auto owner = GetOwner();
		if (owner)
		{
			auto& pos = owner->GetTransform().GetPosition();
			Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
		}
	}
}

void dae::SpriteComponent::SetTexture(const std::string& filename)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(filename);
}
