#pragma once
#include "BaseComponent.h"
#include <deque>
#include <glm.hpp>


namespace dae
{
	
	class AIComponent : public BaseComponent
	{
	public:
		AIComponent(GameObject* owner);
		virtual ~AIComponent() override;
		AIComponent(const AIComponent& other) = delete;
		AIComponent(AIComponent&& other) = delete;
		AIComponent& operator=(const AIComponent& other) = delete;
		AIComponent& operator=(AIComponent&& other) = delete;

		void MoveTo(GameObject* pTarget);
		void Update() override;

	private:
		float m_speed{ 150.f };

		std::deque<glm::vec2> m_Path;

		float m_PathCalcInterval{ 0.5f };
		float m_CalcTime{};

	};
}