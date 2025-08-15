#pragma once
#include "BaseComponent.h"
#include <glm.hpp>
namespace dae 
{
	class MovementComponent : public BaseComponent
	{
	public:
		MovementComponent(GameObject* owner, float speed);
		void Move(glm::ivec2 direction);

		glm::vec2 SnapToGridIfClose(glm::vec2 pos, glm::vec2 direction, int tileWidth, int tileHeight, int snapPixels);
		
		void Update() override;
		void Render() const override;
		bool CanMoveTo(glm::ivec2 direction);
	private:
		float m_Speed{};

		bool m_bSnap{ false };
		bool m_bNeedsToMove{ false };
		
		glm::ivec2 m_DesiredPosition{};
		glm::ivec2 m_Direction{};
		glm::vec2 m_PosToCalcFrom{};
		glm::vec2 m_MoveVector{};
	};
}


