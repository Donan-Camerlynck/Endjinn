#include "ShootCommand.h"

void dae::ShootCommand::Execute()
{
	m_pShootingComp->Shoot();
}
