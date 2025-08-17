#pragma once
#include "Singleton.h"
#include <memory>
#include "GameModeBase.h"

namespace dae
{
	class GameModeManager : public Singleton<GameModeManager>
	{
	public:
		void SetGameMode(std::unique_ptr<GameModeBase> gameMode) { m_GameMode = std::move(gameMode); }
		GameModeBase* getGameMode() { return m_GameMode.get(); }
		void Update() { m_GameMode->Update(); }
		~GameModeManager() = default;
	private:
		std::unique_ptr<GameModeBase> m_GameMode;
	};
}