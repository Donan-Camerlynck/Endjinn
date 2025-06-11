#include "MoveCommand.h"
#include "GameObject.h"
#include "TimeManager.h"

dae::MoveCommand::MoveCommand(float speed, glm::vec2 direction, BodyComponent* body)
	:m_Speed(speed), m_pBodyComp(body)
{
	m_Direction = glm::normalize(direction);
}

void dae::MoveCommand::Execute()
{
	if (!m_pBodyComp)
	{
		return;
	}
	glm::vec2 vel = m_Speed * m_Direction;
	m_pBodyComp->SetVelocity(vel);
}
