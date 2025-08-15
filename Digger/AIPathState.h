#pragma once
#include "AIState.h"
#include "MovementComponent.h"
#include <AStarPathFinding.h>
#include <memory>

namespace dae
{
	class AIComponent;

	class AIPathState : public AIState
	{
	public:
		AIPathState(GameObject* owner, MovementComponent* moveComp);
		~AIPathState() override = default;
		AIPathState(const AIPathState& other) = delete;
		AIPathState(AIPathState&& other) = delete;
		AIPathState& operator=(const AIPathState& other) = delete;
		AIPathState& operator=(AIPathState&& other) = delete;

		virtual void Update() override;
		virtual void Exit() override;
		virtual void Enter() override;
		virtual void Render() override;

	private:
		GameObject* m_pAIOwner;
		MovementComponent* m_pMoveComp;
		bool ShouldRoam();
		std::unique_ptr<AStarPathfinding> m_pAStar;

		float m_PathCalcInterval{ 0.5f };
		float m_CurrentPathCalcTime{};

		std::deque<glm::ivec2> m_Path{};
		glm::ivec2 m_TileSize{};

		glm::ivec2 m_CurrentPathNode{};
		glm::ivec2 m_NextPathNode{};

		bool m_bIsPathing{ false };
	};
}