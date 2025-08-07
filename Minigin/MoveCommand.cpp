#include "MoveCommand.h"
#include "GameObject.h"
#include "TimeManager.h"

dae::MoveCommand::MoveCommand(glm::vec2 direction, MovementComponent* moveComp)
	:m_pMoveComp(moveComp)
{
	m_Direction = glm::normalize(direction);
}

void dae::MoveCommand::Execute()
{
	m_pMoveComp->Move(m_Direction);
}
