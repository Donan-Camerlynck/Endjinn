#pragma once
#include "BaseComponent.h"
#include <string>
#include <memory>
namespace dae
{
	class Texture2D;
    class SpriteComponent : public BaseComponent
    {
	public:

		virtual void Update() override;
		virtual void Render() const override;

		void SetTexture(const std::string& filename);

		SpriteComponent(GameObject* owner, const std::string& textureFilename);
		virtual ~SpriteComponent() override = default;
		SpriteComponent(const SpriteComponent& other) = delete;
		SpriteComponent(SpriteComponent&& other) = delete;
		SpriteComponent& operator=(const SpriteComponent& other) = delete;
		SpriteComponent& operator=(SpriteComponent&& other) = delete;
	private:
		bool m_NeedsUpdate;
		std::shared_ptr<Texture2D> m_pTexture{};
    };
}
