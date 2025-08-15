#include "AIComponent.h"
#include "Renderer.h"

void dae::AIComponent::Update()
{
	m_pState->Update();
}

void dae::AIComponent::Render() const
{
	m_pState->Render();
}

void dae::AIComponent::SetState(std::unique_ptr<AIState> newState)
{
	if (m_pState)
	{
		m_pState->Exit();
	}

	m_pState = std::move(newState);
	if (m_pState)
	{
		m_pState->Enter();
	}
}



dae::AIComponent::AIComponent(GameObject* owner, std::unique_ptr<AIState> state, int pathingDistance)
	:BaseComponent(owner), m_pState(std::move(state)), m_pTarget(nullptr), m_PathingDistance(pathingDistance)
{

}

void dae::AIComponent::SetTarget(GameObject* target)
{
	m_pTarget = target;
}
