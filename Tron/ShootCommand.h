#pragma once
#include "ICommand.h"
#include <GameObject.h>
#include "ShootingComponent.h"

namespace dae
{
	class ShootCommand : public ICommand
	{
	public:
		explicit ShootCommand(GameObject* gameObject, ShootingComponent* shootComp)
			: m_pGameObject(gameObject), m_pShootingComp(shootComp)
		{
		}
		void Execute() override;

	private:
		GameObject* m_pGameObject;
		ShootingComponent* m_pShootingComp;
	};

}