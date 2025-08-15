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
	m_TileSize.x = dae::Level::GetInstance().GetTileWidth() /2;
	m_TileSize.y = dae::Level::GetInstance().GetTileHeight() /2;
}

void dae::AIPathState::Update()
{
	UpdateMovement();

	if (ShouldRoam())
	{
		m_pAIOwner->GetComponent<AIComponent>()->SetState(std::make_unique<AIRoamState>(m_pAIOwner, m_pMoveComp));
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

void dae::AIPathState::UpdateMovement()
{
	m_CurrentPathCalcTime += dae::TimeManager::GetInstance().GetDeltaTime();

	bool reached{ false };
	glm::vec2 direction{};

	if (!m_Path.empty())
	{
		glm::ivec2 aiPos = m_pAIOwner->GetWorldPos();
		glm::ivec2 target = m_Path.front();
		direction = target - aiPos;
		reached = glm::length(direction) < 1.f;


		if (direction.x > 0)
		{
			direction.x = 1;
		}
		if (direction.x < 0)
		{
			direction.x = -1;
		}
		if (direction.y > 0)
		{
			direction.y = 1;
		}
		if (direction.y < 0)
		{
			direction.y = -1;
		}

		if (reached)
		{
			m_Path.pop_front();
			m_bIsPathing = false;
		}
		if (direction.x != 0 || direction.y != 0)
		{
			direction = glm::normalize(direction);
			m_pMoveComp->Move(direction);
		}
	}

	if (m_CurrentPathCalcTime >= m_PathCalcInterval || !m_bIsPathing)
	{
		m_CurrentPathCalcTime = 0;
		m_Path.clear();
		m_Path = m_pAStar->FindPath(m_pAIOwner->GetWorldPos(), m_pAIOwner->GetComponent<AIComponent>()->GetTarget()->GetWorldPos());
		m_bIsPathing = true;
	}
}