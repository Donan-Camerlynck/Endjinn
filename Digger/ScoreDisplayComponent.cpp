#include "ScoreDisplayComponent.h"
#include "ScoreComponent.h"
#include "GameObject.h"
#include <format>

void dae::ScoreDisplayComponent::Notify(const Event& event)
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

dae::ScoreDisplayComponent::ScoreDisplayComponent(GameObject* owner, GameObject* characterToDisplay)
	: BaseComponent(owner), m_pCharacterToDisplay(characterToDisplay)
{

}

void dae::ScoreDisplayComponent::Initialize()
{
	BaseComponent::Initialize();
	auto owner = GetOwner();
	if (owner)
	{
		m_pTextComp = owner->GetComponent<TextComponent>();
		m_pCharacterToDisplay->GetComponent<ScoreComponent>()->GetScoreChangedEvent()->AddObserver(this);
		m_NeedsUpdate = true;
	}
}

void dae::ScoreDisplayComponent::Update()
{
	if (m_pTextComp == nullptr || m_pCharacterToDisplay == nullptr)
	{
		return;
	}
	if (m_NeedsUpdate)
	{
		m_pTextComp->SetText(std::format("Score: {}", m_pCharacterToDisplay->GetComponent<ScoreComponent>()->GetScore()));
		m_NeedsUpdate = false;
	}
}
