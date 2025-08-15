#include "SpriteComponent.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "Texture2D.h"

dae::SpriteComponent::SpriteComponent(GameObject* owner, const std::string& textureFilename) :
	BaseComponent(owner)
{
	SetTexture(textureFilename);
}

glm::vec2 dae::SpriteComponent::GetSize()
{
	return static_cast<glm::vec2>(m_pTexture->GetSize());
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
			auto pos = owner->GetWorldPos();
			auto size = m_pTexture->GetSize();
			Renderer::GetInstance().RenderTexture(*m_pTexture, static_cast<float>(pos.x - size.x /2.f), static_cast<float>(pos.y - size.y /2.f));
		}
	}
}

void dae::SpriteComponent::SetTexture(const std::string& filename)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(filename);
}
