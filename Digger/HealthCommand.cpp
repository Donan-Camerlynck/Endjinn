#include "HealthCommand.h"
#include "HealthComponent.h"
#include "GameObject.h"

void dae::HealthCommand::Execute()
{
	m_pGameObject->GetComponent<HealthComponent>()->DoDamage(m_HealthChange);
}
