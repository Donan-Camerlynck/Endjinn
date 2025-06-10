#pragma once
#include "AxisCommand.h"
#include <glm.hpp>
#include "BodyComponent.h"

namespace dae
{
	class GameObject;

	class MoveCommand : public AxisCommand
	{
	public:
		explicit MoveCommand(float speed, glm::vec2 direction, BodyComponent* body);
		void Execute() override;

	private:
		BodyComponent* m_pBodyComp;
		float m_Speed;


	};
}