#pragma once
#include "ICommand.h"
#include <glm.hpp>

namespace dae
{
	class GameObject;

	class AxisCommand : public ICommand
	{
	public:
		void SetDirection(glm::vec2 direction) { m_Direction = direction; } 

	protected:
		glm::vec2 m_Direction;
		
	};

}