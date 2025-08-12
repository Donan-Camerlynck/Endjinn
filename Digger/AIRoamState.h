#pragma once
#include "AIComponent.h"
#include "MovementComponent.h"

namespace dae
{
	class AIRoamState : public AIState
	{
	public:
		AIRoamState(GameObject* owner, MovementComponent* moveComp);
		~AIRoamState() override = default;
		AIRoamState(const AIRoamState& other) = delete;
		AIRoamState(AIRoamState&& other) = delete;
		AIRoamState& operator=(const AIRoamState& other) = delete;
		AIRoamState& operator=(AIRoamState&& other) = delete;


		virtual void Update() override;
		virtual void Exit() override;
		virtual void Enter() override;

	private:
		GameObject* m_pAIOwner;
		MovementComponent* m_pMoveComp;
		bool ShouldPath();
		float m_MaxRoamInterval{1.f};
		float m_CurrentRoamTimer{};
	};
}