#include "AIPathState.h"
#include "GameObject.h"
#include "AIComponent.h"
#include "AIRoamState.h"
#include "TimeManager.h"
#include "Level.h"

dae::AIPathState::AIPathState(GameObject* owner, MovementComponent* moveComp)
	:m_pAIOwner(owner), m_pMoveComp(moveComp), m_pAStar(std::make_unique<AStarPathfinding>(dae::Level::GetInstance().GetRows(), dae::Level::GetInstance().GetColumns()))
{

}

void dae::AIPathState::Update()
{
	m_CurrentPathCalcTime += dae::TimeManager::GetInstance().GetDeltaTime();

	if (m_CurrentPathCalcTime >= m_PathCalcInterval)
	{
		m_Path.clear();
		m_Path = m_pAStar->FindPath(m_pAIOwner->GetWorldPos(), m_pAIOwner->GetComponent<AIComponent>()->GetTarget()->GetWorldPos());
	}

	if (ShouldRoam())
	{
		m_pAIOwner->GetComponent<AIComponent>()->SetState(std::make_unique<AIPathState>(m_pAIOwner, m_pMoveComp));
	}
}

void dae::AIPathState::Exit()
{
}

void dae::AIPathState::Enter()
{
}

bool dae::AIPathState::ShouldRoam()
{
	GameObject* target = m_pAIOwner->GetComponent<AIComponent>()->GetTarget();
	bool result{ glm::distance(target->GetWorldPos(), m_pAIOwner->GetWorldPos()) >= m_pAIOwner->GetComponent<AIComponent>()->GetPathingDistance() };
	return result;
}
