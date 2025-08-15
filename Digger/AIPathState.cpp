#include "AIPathState.h"
#include "GameObject.h"
#include "AIComponent.h"
#include "AIRoamState.h"
#include "TimeManager.h"
#include "Level.h"
#include <Renderer.h>

dae::AIPathState::AIPathState(GameObject* owner, MovementComponent* moveComp)
	:m_pAIOwner(owner), m_pMoveComp(moveComp), m_pAStar(std::make_unique<AStarPathfinding>(dae::Level::GetInstance().GetRows(), dae::Level::GetInstance().GetColumns()))
{

}

void dae::AIPathState::Update()
{
	m_CurrentPathCalcTime += dae::TimeManager::GetInstance().GetDeltaTime();
	
	if (m_CurrentPathCalcTime >= m_PathCalcInterval || !m_bIsPathing)
	{
		m_Path.clear();
		m_Path = m_pAStar->FindPath(m_pAIOwner->GetWorldPos(), m_pAIOwner->GetComponent<AIComponent>()->GetTarget()->GetWorldPos());
		m_bIsPathing = true;
	}

	if (!m_Path.empty())
	{
		glm::ivec2 aiPos = m_pAIOwner->GetWorldPos();
		glm::ivec2 target = m_Path.front();

		// Movement direction toward current target
		glm::vec2 direction = target - aiPos;
		if (glm::length(direction) > 0.0f)
		{
			direction = glm::normalize(direction);
			m_pMoveComp->Move(direction);
		}

		// Direction-aware check to see if we passed or reached the target
		bool reached = false;
		if (direction.x > 0 && aiPos.x >= target.x) reached = true;
		if (direction.x < 0 && aiPos.x <= target.x) reached = true;
		if (direction.y > 0 && aiPos.y >= target.y) reached = true;
		if (direction.y < 0 && aiPos.y <= target.y) reached = true;

		if (reached)
		{
			m_Path.pop_front();
			m_bIsPathing = false;
		}
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

void dae::AIPathState::Render()
{
	dae::Renderer& renderer = dae::Renderer::GetInstance();
	for (auto& node : m_Path)
	{
		renderer.RenderDebugBox(static_cast<float>(node.x), static_cast<float>(node.y), 5.f, 5.f);
	}
}

bool dae::AIPathState::ShouldRoam()
{
	GameObject* target = m_pAIOwner->GetComponent<AIComponent>()->GetTarget();
	bool result{ glm::distance(target->GetWorldPos(), m_pAIOwner->GetWorldPos()) >= m_pAIOwner->GetComponent<AIComponent>()->GetPathingDistance() };
	return result;
}
