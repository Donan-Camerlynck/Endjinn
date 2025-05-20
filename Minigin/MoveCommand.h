#pragma once
#include "AxisCommand.h"
#include <glm.hpp>

namespace dae
{
	class GameObject;

	class MoveCommand : public AxisCommand
	{
	public:
		explicit MoveCommand(float speed, glm::vec2 direction, GameObject* gameObject);
		void Execute() override;

	private:
		GameObject* m_pGameObject;
		float m_Speed;


	};
}