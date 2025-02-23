#pragma once
#include "BaseComponent.h"
namespace dae
{
	class TextComponent;
	class FPSComponent : public BaseComponent
	{
	public:

		void Initialize() override;
		void Update() override;

		FPSComponent(GameObject* owner);

		virtual ~FPSComponent() = default;
		FPSComponent(const FPSComponent& other) = delete;
		FPSComponent(FPSComponent&& other) = delete;
		FPSComponent& operator=(const FPSComponent& other) = delete;
		FPSComponent& operator=(FPSComponent&& other) = delete;

	private:
		TextComponent* m_pTextComp;
		float m_AccumulatedSeconds{ 0.0f };
		int m_FrameCount{};
		float m_UpdateInterval{ .1f };
	};
}

