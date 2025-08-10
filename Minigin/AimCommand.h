#pragma once
#include "ICommand.h"
#include "ShootingComponent.h"
namespace dae
{
    class AimCommand : public ICommand
    {
	public:
		explicit MoveCommand(glm::vec2 direction, ShootingComponent* moveComp);
		void Execute() override;

	private:
		ShootingComponent* m_pShootComp;
    };

}

