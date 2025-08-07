#pragma once
#include "AxisCommand.h"
#include <glm.hpp>
#include "MovementComponent.h"

namespace dae
{
	class GameObject;

	class MoveCommand : public AxisCommand
	{
	public:
		explicit MoveCommand(glm::vec2 direction, MovementComponent* moveComp);
		void Execute() override;

	private:
		MovementComponent* m_pMoveComp;

	};
}