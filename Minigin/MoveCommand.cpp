#include "MoveCommand.h"
#include "GameObject.h"
#include "TimeManager.h"

dae::MoveCommand::MoveCommand(glm::ivec2 direction, MovementComponent* moveComp)
	:m_pMoveComp(moveComp)
{
	 m_Direction = direction;
}

void dae::MoveCommand::Execute()
{
	m_pMoveComp->Move(m_Direction);
}
