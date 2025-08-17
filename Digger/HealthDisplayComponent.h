#pragma once
#include "BaseComponent.h"
#include "TextComponent.h"
#include "Observer.h"
namespace dae
{
	class HealthDisplayComponent : public BaseComponent, public IObserver
	{
	public:
		HealthDisplayComponent(GameObject* owner, GameObject* characterToDisplay);

		void Initialize() override;
		void Update() override;

		void Notify(const Event& event) override;

		virtual ~HealthDisplayComponent() = default;
		HealthDisplayComponent(const HealthDisplayComponent& other) = delete;
		HealthDisplayComponent(HealthDisplayComponent&& other) = delete;
		HealthDisplayComponent& operator=(const HealthDisplayComponent& other) = delete;
		HealthDisplayComponent& operator=(HealthDisplayComponent&& other) = delete;
			
	private:
		TextComponent* m_pTextComp{ nullptr };
		GameObject* m_pCharacterToDisplay{ nullptr };
		bool m_NeedsUpdate{ false };
		
	};
}



