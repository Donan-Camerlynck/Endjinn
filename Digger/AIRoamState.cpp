#include "AIRoamState.h"
#include "GameObject.h"
#include "AIPathState.h"
#include "TimeManager.h"

dae::AIRoamState::AIRoamState(GameObject* owner, MovementComponent* moveComp)
	:m_pAIOwner(owner), m_pMoveComp(moveComp)
{
}

void dae::AIRoamState::Update()
{
	m_CurrentRoamTimer += dae::TimeManager::GetInstance().GetDeltaTime();
	std::vector<glm::vec2> moves{ {1,0},{-1,0},{0,1},{0,-1} };
	std::vector<glm::vec2> possibleMoves{};
	if (m_CurrentRoamTimer > m_MaxRoamInterval)
	{
		m_CurrentRoamTimer -= m_MaxRoamInterval;
		possibleMoves.clear();
		for (glm::vec2 move : moves)
		{
			if (m_pMoveComp->CanMoveTo(move))
			{
				possibleMoves.push_back(move);
			}
		}
	}
	if (!possibleMoves.empty())
	{
		glm::vec2 choice = possibleMoves[rand() % possibleMoves.size()];
		m_pMoveComp->Move(choice);
	}
	if (ShouldPath())
	{
		m_pAIOwner->GetComponent<AIComponent>()->SetState(std::make_unique<AIPathState>(m_pAIOwner, m_pMoveComp));
	}
}

void dae::AIRoamState::Exit()
{

}

void dae::AIRoamState::Enter()
{

}

bool dae::AIRoamState::ShouldPath()
{
	GameObject* target = m_pAIOwner->GetComponent<AIComponent>()->GetTarget();
	bool result{ glm::distance(target->GetWorldPos(), m_pAIOwner->GetWorldPos()) < m_pAIOwner->GetComponent<AIComponent>()->GetPathingDistance() };
	return result;
}