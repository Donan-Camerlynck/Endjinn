#pragma once
#include "BaseComponent.h"
#include <deque>
#include <glm.hpp>

#include <memory>
#include "AIState.h"

namespace dae
{
	
	class AIComponent : public BaseComponent
	{
	public:
		AIComponent(GameObject* owner, std::unique_ptr<AIState> state, int pathingDistance);
		virtual ~AIComponent() override = default;
		AIComponent(const AIComponent& other) = delete;
		AIComponent(AIComponent&& other) = delete;
		AIComponent& operator=(const AIComponent& other) = delete;
		AIComponent& operator=(AIComponent&& other) = delete;

		//void MoveTo(GameObject* pTarget);
		void Update() override;
		void Render() const override;
		GameObject* GetTarget() { return m_pTarget; }
		void SetTarget(GameObject* target);
		int GetPathingDistance() { return m_PathingDistance; }
		void SetState(std::unique_ptr<AIState> newState);

	private:
		std::unique_ptr<AIState> m_pState;
		float m_speed{ 150.f };
		int m_PathingDistance{};

		std::deque<glm::ivec2> m_Path;

		float m_PathCalcInterval{ 0.5f };
		float m_CalcTime{};

		GameObject* m_pTarget;
	};
}