#include "SDL.h"


#if _DEBUG
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"

#include "SceneManager.h"
#include "ResourceManager.h"
#include "BulletManager.h"
#include "TextComponent.h"
#include "GameObject.h"
#include "Scene.h"
#include "FPSComponent.h"
#include "SpriteComponent.h"
#include "RotationComponent.h"
#include "InputManager.h"
#include "MoveCommand.h"
#include "HealthComponent.h"
#include "HealthDisplayComponent.h"
#include "ScoreDisplayComponent.h"
#include "ScoreComponent.h"
#include "Level.h"
#include "ShootCommand.h"
#include "AimCommand.h"
#include <AIComponent.h>
#include "AIRoamState.h"
#include "SoundSystem.h"
#include "ShootingAIComponent.h"
#include "GameModeManager.h"
#include "SkipLevelCommand.h"
#include "GameMode.h"



void load()
{
	
	dae::SoundSystem::GetInstance();
	
	auto& input = dae::InputManager::GetInstance();

	

	auto& gamemodeManager = dae::GameModeManager::GetInstance();
	gamemodeManager.SetGameMode(std::make_unique<dae::GameMode>());
	gamemodeManager.getGameMode()->Setlevel(0);

	input.AddCommand(SDL_SCANCODE_F1, dae::InputEventType::Down, std::make_unique<dae::SkipLevelCommand>());
}

int main(int, char*[])
{
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}

