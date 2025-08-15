#include "TextComponent.h"
#include "Renderer.h"
#include <stdexcept>
#include <SDL_ttf.h>
#include "Font.h"
#include "Texture2D.h"
#include "ResourceManager.h"
#include "GameObject.h"

void dae::TextComponent::Update()
{
	if (m_NeedsUpdate)
	{
		BaseComponent::Update();
		const SDL_Color color = { 255,255,255,255 };
		const auto surface = TTF_RenderText_Blended(m_pFont->GetFont(), m_Text.c_str(), color);
		if (surface == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surface);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surface);
		m_pTexture = std::make_shared<Texture2D>(texture);
		m_NeedsUpdate = false;
	}
}

void dae::TextComponent::Render() const
{
	BaseComponent::Render();
	if (m_pTexture != nullptr)
	{
		auto owner = GetOwner();
		if (owner)
		{
			auto pos = owner->GetWorldPos();
			Renderer::GetInstance().RenderTexture(*m_pTexture, static_cast<float>(pos.x), static_cast<float>(pos.y));
		}

	}
}

dae::TextComponent::TextComponent(GameObject* owner, std::shared_ptr<Font> font, const std::string& text)
	:BaseComponent(owner), m_pFont(font), m_NeedsUpdate(true), m_Text(text), m_pTexture(nullptr)
{
}

void dae::TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}
