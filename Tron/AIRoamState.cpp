#include "AIRoamState.h"
#include "GameObject.h"
#include "AIPathState.h"
#include "TimeManager.h"
#include <iostream>

dae::AIRoamState::AIRoamState(GameObject* owner, MovementComponent* moveComp)
	:m_pAIOwner(owner), m_pMoveComp(moveComp)
{
}

void dae::AIRoamState::Update()
{
	m_CurrentRoamTimer += dae::TimeManager::GetInstance().GetDeltaTime();
	std::vector<glm::ivec2> moves{ {1,0},{-1,0},{0,-1},{0,1} };
	std::vector<glm::ivec2> possibleMoves{};
	m_PreviousNumberOptions = m_CurrentNumberOptions;

	for (glm::ivec2 move : moves)
	{
		if (m_pMoveComp->CanMoveTo(move))
		{
			possibleMoves.push_back(move);
		}
	}

	m_CurrentNumberOptions = static_cast<int>(possibleMoves.size());

	if (m_CurrentRoamTimer >= m_MaxRoamInterval || m_CurrentNumberOptions > m_PreviousNumberOptions)
	{
		m_CurrentRoamTimer = 0;
		
		
		if (!possibleMoves.empty())
		{
			
			for (auto& move : possibleMoves)
			{
				std::cout << move.x << ", " << move.y << std::endl;
			}
			m_Choice = possibleMoves[rand() % possibleMoves.size()];
		}
		else
		{
			m_CurrentRoamTimer = m_MaxRoamInterval;
		}
	}
	
	m_pMoveComp->Move(m_Choice);
	
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

void dae::AIRoamState::Render()
{
}

bool dae::AIRoamState::ShouldPath()
{
	GameObject* target = m_pAIOwner->GetComponent<AIComponent>()->GetTarget();
	bool result{ glm::distance(target->GetWorldPos(), m_pAIOwner->GetWorldPos()) < m_pAIOwner->GetComponent<AIComponent>()->GetPathingDistance() };
	return result;
}