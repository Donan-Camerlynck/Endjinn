#pragma once
#include "Singleton.h"
#include "GamemodeBase.h"

namespace dae
{
	class GameMode : public GameModeBase
	{
	public:
		
		void Setlevel(int levelNum);
		void NextLevel();
		void Update();

	private:
		void LoadLevel0();
		void LoadLevel1();
		void LoadLevel2();
		void LoadLevelPvp();
		int m_CurrentLevel{};
		bool m_bLevelChangeFlag = false;
	};
}


