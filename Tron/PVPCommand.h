#pragma once
#include "ICommand.h"
#include "GameModeManager.h"
namespace dae
{
	class PVPCommand : public ICommand
	{
	public:
		void Execute() override
		{
			GameModeManager::GetInstance().getGameMode()->Setlevel(3);
		}
	};
}