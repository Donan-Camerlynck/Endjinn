#pragma once
#include "AxisCommand.h"
#include "ShootingComponent.h"
namespace dae
{
	class AimCommand : public AxisCommand
	{
	public:
		explicit AimCommand(glm::vec2 direction, ShootingComponent* moveComp);
		void Execute() override;

	private:
		ShootingComponent* m_pShootComp;
	};

}
