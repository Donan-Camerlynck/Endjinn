#include "AimCommand.h"

dae::AimCommand::AimCommand(glm::vec2 direction, ShootingComponent* shootComp)
	:m_Direction(direction), m_pShootComp(shootComp)
{

}

void dae::AimCommand::Execute()
{
	m_pShootComp->SetDirection(m_Direction);
}
