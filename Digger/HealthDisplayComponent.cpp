#include "HealthDisplayComponent.h"
#include "GameObject.h"
#include "TextComponent.h"
#include <format>
#include "HealthComponent.h"

namespace dae
{
	HealthDisplayComponent::HealthDisplayComponent(GameObject* owner, GameObject* characterToDisplay)
		: BaseComponent(owner), m_pCharacterToDisplay(characterToDisplay)
	{
	}
	void HealthDisplayComponent::Initialize()
	{
		BaseComponent::Initialize();
		auto owner = GetOwner();
		if (owner)
		{
			m_pTextComp = owner->GetComponent<TextComponent>();
			m_pCharacterToDisplay->GetComponent<HealthComponent>()->GetHealthChangedEvent()->AddObserver(this);
			m_NeedsUpdate = true;
		}
	}
	void HealthDisplayComponent::Update()
	{
		if (m_pTextComp == nullptr || m_pCharacterToDisplay == nullptr)
		{
			return;
		}
		if (m_NeedsUpdate)
		{
			m_pTextComp->SetText(std::format("Health: {}", m_pCharacterToDisplay->GetComponent<HealthComponent>()->GetHealth()));
			m_NeedsUpdate = false;
		}
	}

	void HealthDisplayComponent::Notify(const Event& event)
	{
		if (EventType::OnDeath == event.type) return;
		if (m_pCharacterToDisplay != nullptr)
		{
			m_NeedsUpdate = true;
		}
		else
		{
			m_NeedsUpdate = false;
		}
	}
}

