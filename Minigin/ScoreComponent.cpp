#include "ScoreComponent.h"

dae::ScoreComponent::ScoreComponent(GameObject* owner, int initialScore)
	: BaseComponent(owner),
	m_Score(initialScore)
{
	m_ScoreChangedEvent = std::make_unique<Subject>();
}

void dae::ScoreComponent::Update()
{

}

void dae::ScoreComponent::Initialize()
{
	BaseComponent::Initialize();

}

void dae::ScoreComponent::AddScore(int score)
{
	m_Score += score;
	m_ScoreChangedEvent->NotifyAll({});
}

void dae::ScoreComponent::ResetScore()
{
	m_Score = 0;
	m_ScoreChangedEvent->NotifyAll({});
}

void dae::ScoreComponent::Notify(const Event& event)
{
	AddScore(event.value);
}
