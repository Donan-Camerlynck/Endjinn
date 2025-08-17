#pragma once

namespace dae
{
	class GameModeBase
	{
	public:
		virtual void Setlevel(int levelNum) = 0;
		virtual void NextLevel() = 0;
		virtual void Update() = 0;
		virtual ~GameModeBase() = default;
	};
}


