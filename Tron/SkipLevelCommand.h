#pragma once
#include "ICommand.h"
#include "GameModeManager.h"
namespace dae
{
	class SkipLevelCommand : public ICommand
	{
	public:
		void Execute() override
		{
			GameModeManager::GetInstance().getGameMode()->NextLevel();
		}
	};
}