#pragma once
#include "BaseComponent.h"
#include <glm.hpp>
namespace dae 
{
	class MovementComponent : public BaseComponent
	{
	public:
		MovementComponent(GameObject* owner, float speed);
		void Move(glm::vec2 direction);
		void Update() override;
		
	private:
		float m_Speed{};

		bool CanMoveTo(glm::vec2 direction);
		bool m_bNeedsToMove{ false };

		glm::vec2 m_DesiredPosition{};
	};
}


