#pragma once

#include "BaseComponent.h"
#include <memory>
#include <string>

namespace dae
{
	class Texture2D;
	class Font;
	class GameObject;
	class TextComponent : public BaseComponent
	{
	public:

		virtual void Update() override;
		virtual void Render() const override;

		TextComponent(GameObject* parent, std::shared_ptr<Font> font, const std::string& text);
		void SetText(const std::string& text);

		virtual ~TextComponent() = default;
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;

	private:
		bool m_NeedsUpdate;
		std::string m_Text;
		std::shared_ptr<Font> m_pFont;
		std::shared_ptr<Texture2D> m_pTexture;
	};
}
