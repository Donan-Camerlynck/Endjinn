#pragma once
#include "ICommand.h"
#include "ShootingComponent.h"
namespace dae
{
	class AimCommand : public ICommand
	{
	public:
		explicit AimCommand(glm::vec2 direction, ShootingComponent* moveComp);
		void Execute() override;

	private:
		glm::vec2 m_Direction;
		ShootingComponent* m_pShootComp;
	};

}
