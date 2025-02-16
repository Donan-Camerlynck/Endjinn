#include "FPSComponent.h"
#include <format>
#include "GameObject.h"
#include "TextComponent.h"
#include "TimeManager.h"

void dae::FPSComponent::Initialize()
{
	BaseComponent::Initialize();
	auto owner = GetOwner();
	if (owner)
	{
		m_pTextComp = owner->GetComponent<TextComponent>();
	}
}

void dae::FPSComponent::Update()
{
	if (m_pTextComp == nullptr)
	{
		return;
	}

	m_AccumulatedSeconds += TimeManager::GetInstance().GetDeltaTime();
	++m_FrameCount;

	if (m_AccumulatedSeconds < m_UpdateInterval)
	{
		return;
	}

	auto textComp = m_pTextComp;
	textComp->SetText(std::format("FPS: {:.1f}", m_FrameCount / m_AccumulatedSeconds));
	m_FrameCount = 0;
	m_AccumulatedSeconds = 0;

}

void dae::FPSComponent::Render() const
{
	BaseComponent::Render();
}

dae::FPSComponent::FPSComponent(GameObject* owner)
	:BaseComponent(owner)
{
}