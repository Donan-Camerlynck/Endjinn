#pragma once
#include <SDL.h>
#include "GameMode.h"
#include "SceneManager.h"
#include "InputManager.h"
#include <MoveCommand.h>
#include "ShootCommand.h"
#include "AimCommand.h"
#include "Level.h"
#include "ScoreDisplayComponent.h"
#include "HealthDisplayComponent.h"
#include <BulletManager.cpp>
#include "HealthComponent.h"
#include <SpriteComponent.h>
#include <FPSComponent.h>
#include "ShootingAIComponent.h"
#include "AIRoamState.h"
#include "SkipLevelCommand.h"
#include <MuteCommand.h>
#include "PVECommand.h"
#include "PVPCommand.h"

void dae::GameMode::LoadLevel0()
{
	m_CurrentLevel = 0;
	dae::SceneManager::GetInstance().ClearScenes();
	// load scene 2
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto fontSmall = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 16);
	auto& bulletManager = dae::BulletManager::GetInstance();
	bulletManager.SetTexture("Sprites/BulletNPC.png");
	dae::Level& level = dae::Level::GetInstance();
	level.Load("LevelLayout0.csv");
	auto& scene2 = dae::SceneManager::GetInstance().CreateScene("Level2");
	auto fps2 = std::make_unique<dae::GameObject>(&scene2, dae::RenderLayer::UI);
	fps2->AddComponent<dae::FPSComponent>();
	fps2->AddComponent<dae::TextComponent>(fontSmall, "FPS");
	fps2->SetLocalPos(glm::vec2{ 10, 10 });
	scene2.Add(std::move(fps2));

	auto goRoot2 = std::make_unique<dae::GameObject>(&scene2, dae::RenderLayer::BackGround);
	auto rootObj2 = scene2.Add(std::move(goRoot2));
	rootObj2->SetLocalPos(glm::vec2{ 0, 0 });

	glm::vec2 playerSpawnPos2 = level.GetPlayerSpawn(0);
	auto go42 = std::make_unique<dae::GameObject>(&scene2, dae::RenderLayer::ObjectTop);
	go42->AddComponent<dae::SpriteComponent>("Sprites/RedTank.png");
	go42->AddComponent<dae::HealthComponent>(3);
	go42->AddComponent<dae::ScoreComponent>(0);
	go42->AddComponent<dae::MovementComponent>(125.f);
	go42->AddComponent<dae::ShootingComponent>(150.f, true);
	go42->SetLocalPos(playerSpawnPos2);
	auto mainObj2 = scene2.Add(std::move(go42), true);


	std::vector<glm::vec2> enemySpawns2 = level.GetAllEnemySpawns();

	for (auto enemySpawn : enemySpawns2)
	{
		auto go5 = std::make_unique<dae::GameObject>(&scene2, dae::RenderLayer::ObjectTop);
		go5->AddComponent<dae::SpriteComponent>("Sprites/GreenTank.png");
		go5->AddComponent<dae::HealthComponent>(3);
		go5->AddComponent<dae::ScoreComponent>(0);
		go5->AddComponent<dae::MovementComponent>(125.f);
		go5->AddComponent<dae::ShootingComponent>(150.f, false);
		go5->AddComponent<dae::ShootingAIComponent>(std::make_unique<dae::AIRoamState>(go5.get(), go5->GetComponent<dae::MovementComponent>()), 250, go5->GetComponent<dae::ShootingComponent>());
		go5->GetComponent<dae::AIComponent>()->SetTarget(mainObj2);
		go5->SetLocalPos(enemySpawn);
		auto enemyObj = scene2.Add(std::move(go5), false, true);
		enemyObj->SetParent(rootObj2, false);
		bulletManager.AddEnemy(enemyObj);
	}


	bulletManager.AddPlayer(mainObj2);


	mainObj2->SetParent(rootObj2, false);

	auto HealthDisplay2 = std::make_unique<dae::GameObject>(&scene2, dae::RenderLayer::UI);
	HealthDisplay2->AddComponent<dae::TextComponent>(fontSmall, "Player 1 health: ");
	HealthDisplay2->AddComponent<dae::HealthDisplayComponent>(mainObj2);
	HealthDisplay2->SetLocalPos(glm::ivec2{ 10, 100 });
	scene2.Add(std::move(HealthDisplay2));

	auto ScoreDisplay2 = std::make_unique<dae::GameObject>(&scene2, dae::RenderLayer::UI);
	ScoreDisplay2->AddComponent<dae::TextComponent>(fontSmall, "Player 1 score: ");
	ScoreDisplay2->AddComponent<dae::ScoreDisplayComponent>(mainObj2);
	ScoreDisplay2->SetLocalPos(glm::ivec2{ 10, 150 });
	scene2.Add(std::move(ScoreDisplay2));

	scene2.SetActive(true);


	GameObject* mainObj = scene2.GetPlayers()[0];
	dae::InputManager& input = dae::InputManager::GetInstance();
	input.ClearCommands();
	input.AddCommand(SDL_SCANCODE_A, dae::InputEventType::Pressed, std::make_unique<dae::MoveCommand>(glm::ivec2{ -1, 0 }, mainObj->GetComponent<dae::MovementComponent>()));
	input.AddCommand(SDL_SCANCODE_D, dae::InputEventType::Pressed, std::make_unique<dae::MoveCommand>(glm::ivec2{ 1, 0 }, mainObj->GetComponent<dae::MovementComponent>()));
	input.AddCommand(SDL_SCANCODE_W, dae::InputEventType::Pressed, std::make_unique<dae::MoveCommand>(glm::ivec2{ 0, -1 }, mainObj->GetComponent<dae::MovementComponent>()));
	input.AddCommand(SDL_SCANCODE_S, dae::InputEventType::Pressed, std::make_unique<dae::MoveCommand>(glm::ivec2{ 0, 1 }, mainObj->GetComponent<dae::MovementComponent>()));

	input.AddCommand(dae::GamepadKey::DPad_Left, dae::InputEventType::Pressed, std::make_unique<dae::MoveCommand>(glm::ivec2{ -1, 0 }, mainObj->GetComponent<dae::MovementComponent>()), 0);
	input.AddCommand(dae::GamepadKey::DPad_Right, dae::InputEventType::Pressed, std::make_unique<dae::MoveCommand>(glm::ivec2{ 1, 0 }, mainObj->GetComponent<dae::MovementComponent>()), 0);
	input.AddCommand(dae::GamepadKey::DPad_Up, dae::InputEventType::Pressed, std::make_unique<dae::MoveCommand>(glm::ivec2{ 0, -1 }, mainObj->GetComponent<dae::MovementComponent>()), 0);
	input.AddCommand(dae::GamepadKey::DPad_Down, dae::InputEventType::Pressed, std::make_unique<dae::MoveCommand>(glm::ivec2{ 0, 1 }, mainObj->GetComponent<dae::MovementComponent>()), 0);

	input.AddCommand(dae::GamepadAxis2D::LThumbStick, std::make_unique<dae::MoveCommand>(glm::ivec2{ 0, 0 }, mainObj->GetComponent<dae::MovementComponent>()), 0);


	input.AddCommand(SDL_SCANCODE_SPACE, dae::InputEventType::Down, std::make_unique<dae::ShootCommand>(mainObj, mainObj->GetComponent<dae::ShootingComponent>()));
	input.AddCommand(dae::GamepadKey::RShoulder, dae::InputEventType::Down, std::make_unique<dae::ShootCommand>(mainObj, mainObj->GetComponent<dae::ShootingComponent>()), 0);

	input.AddCommand(SDL_SCANCODE_L, dae::InputEventType::Pressed, std::make_unique<dae::AimCommand>(glm::vec2{ 1,0 }, mainObj->GetComponent<dae::ShootingComponent>()));
	input.AddCommand(SDL_SCANCODE_J, dae::InputEventType::Pressed, std::make_unique<dae::AimCommand>(glm::vec2{ -1,0 }, mainObj->GetComponent<dae::ShootingComponent>()));
	input.AddCommand(SDL_SCANCODE_I, dae::InputEventType::Pressed, std::make_unique<dae::AimCommand>(glm::vec2{ 0,-1 }, mainObj->GetComponent<dae::ShootingComponent>()));
	input.AddCommand(SDL_SCANCODE_K, dae::InputEventType::Pressed, std::make_unique<dae::AimCommand>(glm::vec2{ 0,1 }, mainObj->GetComponent<dae::ShootingComponent>()));

	input.AddCommand(dae::GamepadAxis2D::RThumbStick, std::make_unique<dae::AimCommand>(glm::ivec2{ 0, 0 }, mainObj->GetComponent<dae::ShootingComponent>()), 0, true);
	input.AddCommand(SDL_SCANCODE_F1, dae::InputEventType::Down, std::make_unique<dae::SkipLevelCommand>());
	input.AddCommand(SDL_SCANCODE_F2, dae::InputEventType::Down, std::make_unique<dae::MuteCommand>());
	input.AddCommand(SDL_SCANCODE_F3, dae::InputEventType::Down, std::make_unique<dae::PVPCommand>());

	scene2.Initialize();
}

void dae::GameMode::LoadLevel1()
{
	m_CurrentLevel = 1;
	dae::SceneManager::GetInstance().ClearScenes();
	// load scene 2
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto fontSmall = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 16);
	auto& bulletManager = dae::BulletManager::GetInstance();
	bulletManager.SetTexture("Sprites/BulletNPC.png");
	dae::Level& level = dae::Level::GetInstance();
	level.Load("LevelLayout1.csv");
	auto& scene2 = dae::SceneManager::GetInstance().CreateScene("Level2");
	auto fps2 = std::make_unique<dae::GameObject>(&scene2, dae::RenderLayer::UI);
	fps2->AddComponent<dae::FPSComponent>();
	fps2->AddComponent<dae::TextComponent>(fontSmall, "FPS");
	fps2->SetLocalPos(glm::vec2{ 10, 10 });
	scene2.Add(std::move(fps2));

	auto goRoot2 = std::make_unique<dae::GameObject>(&scene2, dae::RenderLayer::BackGround);
	auto rootObj2 = scene2.Add(std::move(goRoot2));
	rootObj2->SetLocalPos(glm::vec2{ 0, 0 });

	glm::vec2 playerSpawnPos2 = level.GetPlayerSpawn(0);
	auto go42 = std::make_unique<dae::GameObject>(&scene2, dae::RenderLayer::ObjectTop);
	go42->AddComponent<dae::SpriteComponent>("Sprites/RedTank.png");
	go42->AddComponent<dae::HealthComponent>(3);
	go42->AddComponent<dae::ScoreComponent>(0);
	go42->AddComponent<dae::MovementComponent>(125.f);
	go42->AddComponent<dae::ShootingComponent>(150.f, true);
	go42->SetLocalPos(playerSpawnPos2);
	auto mainObj2 = scene2.Add(std::move(go42), true);


	std::vector<glm::vec2> enemySpawns2 = level.GetAllEnemySpawns();

	for (auto enemySpawn : enemySpawns2)
	{
		auto go5 = std::make_unique<dae::GameObject>(&scene2, dae::RenderLayer::ObjectTop);
		go5->AddComponent<dae::SpriteComponent>("Sprites/GreenTank.png");
		go5->AddComponent<dae::HealthComponent>(3);
		go5->AddComponent<dae::ScoreComponent>(0);
		go5->AddComponent<dae::MovementComponent>(125.f);
		go5->AddComponent<dae::ShootingComponent>(150.f, false);
		go5->AddComponent<dae::ShootingAIComponent>(std::make_unique<dae::AIRoamState>(go5.get(), go5->GetComponent<dae::MovementComponent>()), 250, go5->GetComponent<dae::ShootingComponent>());
		go5->GetComponent<dae::AIComponent>()->SetTarget(mainObj2);
		go5->SetLocalPos(enemySpawn);
		auto enemyObj = scene2.Add(std::move(go5), false, true);
		enemyObj->SetParent(rootObj2, false);
		bulletManager.AddEnemy(enemyObj);
	}

	bulletManager.AddPlayer(mainObj2);

	mainObj2->SetParent(rootObj2, false);

	auto HealthDisplay2 = std::make_unique<dae::GameObject>(&scene2, dae::RenderLayer::UI);
	HealthDisplay2->AddComponent<dae::TextComponent>(fontSmall, "Player 1 health: ");
	HealthDisplay2->AddComponent<dae::HealthDisplayComponent>(mainObj2);
	HealthDisplay2->SetLocalPos(glm::ivec2{ 10, 100 });
	scene2.Add(std::move(HealthDisplay2));

	auto ScoreDisplay2 = std::make_unique<dae::GameObject>(&scene2, dae::RenderLayer::UI);
	ScoreDisplay2->AddComponent<dae::TextComponent>(fontSmall, "Player 1 score: ");
	ScoreDisplay2->AddComponent<dae::ScoreDisplayComponent>(mainObj2);
	ScoreDisplay2->SetLocalPos(glm::ivec2{ 10, 150 });
	scene2.Add(std::move(ScoreDisplay2));

	scene2.SetActive(true);

	GameObject* mainObj = scene2.GetPlayers()[0];
	dae::InputManager& input = dae::InputManager::GetInstance();
	input.ClearCommands();
	input.AddCommand(SDL_SCANCODE_A, dae::InputEventType::Pressed, std::make_unique<dae::MoveCommand>(glm::ivec2{ -1, 0 }, mainObj->GetComponent<dae::MovementComponent>()));
	input.AddCommand(SDL_SCANCODE_D, dae::InputEventType::Pressed, std::make_unique<dae::MoveCommand>(glm::ivec2{ 1, 0 }, mainObj->GetComponent<dae::MovementComponent>()));
	input.AddCommand(SDL_SCANCODE_W, dae::InputEventType::Pressed, std::make_unique<dae::MoveCommand>(glm::ivec2{ 0, -1 }, mainObj->GetComponent<dae::MovementComponent>()));
	input.AddCommand(SDL_SCANCODE_S, dae::InputEventType::Pressed, std::make_unique<dae::MoveCommand>(glm::ivec2{ 0, 1 }, mainObj->GetComponent<dae::MovementComponent>()));

	input.AddCommand(dae::GamepadKey::DPad_Left, dae::InputEventType::Pressed, std::make_unique<dae::MoveCommand>(glm::ivec2{ -1, 0 }, mainObj->GetComponent<dae::MovementComponent>()), 0);
	input.AddCommand(dae::GamepadKey::DPad_Right, dae::InputEventType::Pressed, std::make_unique<dae::MoveCommand>(glm::ivec2{ 1, 0 }, mainObj->GetComponent<dae::MovementComponent>()), 0);
	input.AddCommand(dae::GamepadKey::DPad_Up, dae::InputEventType::Pressed, std::make_unique<dae::MoveCommand>(glm::ivec2{ 0, -1 }, mainObj->GetComponent<dae::MovementComponent>()), 0);
	input.AddCommand(dae::GamepadKey::DPad_Down, dae::InputEventType::Pressed, std::make_unique<dae::MoveCommand>(glm::ivec2{ 0, 1 }, mainObj->GetComponent<dae::MovementComponent>()), 0);

	input.AddCommand(dae::GamepadAxis2D::LThumbStick, std::make_unique<dae::MoveCommand>(glm::ivec2{ 0, 0 }, mainObj->GetComponent<dae::MovementComponent>()), 0);

	input.AddCommand(SDL_SCANCODE_SPACE, dae::InputEventType::Down, std::make_unique<dae::ShootCommand>(mainObj, mainObj->GetComponent<dae::ShootingComponent>()));
	input.AddCommand(dae::GamepadKey::RShoulder, dae::InputEventType::Down, std::make_unique<dae::ShootCommand>(mainObj, mainObj->GetComponent<dae::ShootingComponent>()), 0);

	input.AddCommand(SDL_SCANCODE_L, dae::InputEventType::Pressed, std::make_unique<dae::AimCommand>(glm::vec2{ 1,0 }, mainObj->GetComponent<dae::ShootingComponent>()));
	input.AddCommand(SDL_SCANCODE_J, dae::InputEventType::Pressed, std::make_unique<dae::AimCommand>(glm::vec2{ -1,0 }, mainObj->GetComponent<dae::ShootingComponent>()));
	input.AddCommand(SDL_SCANCODE_I, dae::InputEventType::Pressed, std::make_unique<dae::AimCommand>(glm::vec2{ 0,-1 }, mainObj->GetComponent<dae::ShootingComponent>()));
	input.AddCommand(SDL_SCANCODE_K, dae::InputEventType::Pressed, std::make_unique<dae::AimCommand>(glm::vec2{ 0,1 }, mainObj->GetComponent<dae::ShootingComponent>()));

	input.AddCommand(dae::GamepadAxis2D::RThumbStick, std::make_unique<dae::AimCommand>(glm::ivec2{ 0, 0 }, mainObj->GetComponent<dae::ShootingComponent>()), 0, true);
	input.AddCommand(SDL_SCANCODE_F1, dae::InputEventType::Down, std::make_unique<dae::SkipLevelCommand>());
	input.AddCommand(SDL_SCANCODE_F2, dae::InputEventType::Down, std::make_unique<dae::MuteCommand>());
	input.AddCommand(SDL_SCANCODE_F3, dae::InputEventType::Down, std::make_unique<dae::PVPCommand>());

	scene2.Initialize();
}

void dae::GameMode::LoadLevel2()
{
	m_CurrentLevel = 2;
	dae::SceneManager::GetInstance().ClearScenes();
	// load scene 2
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto fontSmall = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 16);
	auto& bulletManager = dae::BulletManager::GetInstance();
	bulletManager.SetTexture("Sprites/BulletNPC.png");
	dae::Level& level = dae::Level::GetInstance();
	level.Load("LevelLayout2.csv");
	level.Load("LevelLayout2.csv");
	auto& scene2 = dae::SceneManager::GetInstance().CreateScene("Level2");
	auto fps2 = std::make_unique<dae::GameObject>(&scene2, dae::RenderLayer::UI);
	fps2->AddComponent<dae::FPSComponent>();
	fps2->AddComponent<dae::TextComponent>(fontSmall, "FPS");
	fps2->SetLocalPos(glm::vec2{ 10, 10 });
	scene2.Add(std::move(fps2));

	auto goRoot2 = std::make_unique<dae::GameObject>(&scene2, dae::RenderLayer::BackGround);
	auto rootObj2 = scene2.Add(std::move(goRoot2));
	rootObj2->SetLocalPos(glm::vec2{ 0, 0 });

	glm::vec2 playerSpawnPos2 = level.GetPlayerSpawn(0);
	auto go42 = std::make_unique<dae::GameObject>(&scene2, dae::RenderLayer::ObjectTop);
	go42->AddComponent<dae::SpriteComponent>("Sprites/RedTank.png");
	go42->AddComponent<dae::HealthComponent>(3);
	go42->AddComponent<dae::ScoreComponent>(0);
	go42->AddComponent<dae::MovementComponent>(125.f);
	go42->AddComponent<dae::ShootingComponent>(150.f, true);
	go42->SetLocalPos(playerSpawnPos2);
	auto mainObj2 = scene2.Add(std::move(go42), true);


	std::vector<glm::vec2> enemySpawns2 = level.GetAllEnemySpawns();

	for (auto enemySpawn : enemySpawns2)
	{
		auto go5 = std::make_unique<dae::GameObject>(&scene2, dae::RenderLayer::ObjectTop);
		go5->AddComponent<dae::SpriteComponent>("Sprites/GreenTank.png");
		go5->AddComponent<dae::HealthComponent>(3);
		go5->AddComponent<dae::ScoreComponent>(0);
		go5->AddComponent<dae::MovementComponent>(125.f);
		go5->AddComponent<dae::ShootingComponent>(150.f, false);
		go5->AddComponent<dae::ShootingAIComponent>(std::make_unique<dae::AIRoamState>(go5.get(), go5->GetComponent<dae::MovementComponent>()), 250, go5->GetComponent<dae::ShootingComponent>());
		go5->GetComponent<dae::AIComponent>()->SetTarget(mainObj2);
		go5->SetLocalPos(enemySpawn);
		auto enemyObj = scene2.Add(std::move(go5), false, true);
		enemyObj->SetParent(rootObj2, false);
		bulletManager.AddEnemy(enemyObj);
	}


	bulletManager.AddPlayer(mainObj2);


	mainObj2->SetParent(rootObj2, false);

	auto HealthDisplay2 = std::make_unique<dae::GameObject>(&scene2, dae::RenderLayer::UI);
	HealthDisplay2->AddComponent<dae::TextComponent>(fontSmall, "Player 1 health: ");
	HealthDisplay2->AddComponent<dae::HealthDisplayComponent>(mainObj2);
	HealthDisplay2->SetLocalPos(glm::ivec2{ 10, 100 });
	scene2.Add(std::move(HealthDisplay2));

	auto ScoreDisplay2 = std::make_unique<dae::GameObject>(&scene2, dae::RenderLayer::UI);
	ScoreDisplay2->AddComponent<dae::TextComponent>(fontSmall, "Player 1 score: ");
	ScoreDisplay2->AddComponent<dae::ScoreDisplayComponent>(mainObj2);
	ScoreDisplay2->SetLocalPos(glm::ivec2{ 10, 150 });
	scene2.Add(std::move(ScoreDisplay2));

	scene2.SetActive(true);

	
	GameObject* mainObj = scene2.GetPlayers()[0];
	dae::InputManager& input = dae::InputManager::GetInstance();
	input.ClearCommands();
	input.AddCommand(SDL_SCANCODE_A, dae::InputEventType::Pressed, std::make_unique<dae::MoveCommand>(glm::ivec2{ -1, 0 }, mainObj->GetComponent<dae::MovementComponent>()));
	input.AddCommand(SDL_SCANCODE_D, dae::InputEventType::Pressed, std::make_unique<dae::MoveCommand>(glm::ivec2{ 1, 0 }, mainObj->GetComponent<dae::MovementComponent>()));
	input.AddCommand(SDL_SCANCODE_W, dae::InputEventType::Pressed, std::make_unique<dae::MoveCommand>(glm::ivec2{ 0, -1 }, mainObj->GetComponent<dae::MovementComponent>()));
	input.AddCommand(SDL_SCANCODE_S, dae::InputEventType::Pressed, std::make_unique<dae::MoveCommand>(glm::ivec2{ 0, 1 }, mainObj->GetComponent<dae::MovementComponent>()));

	input.AddCommand(dae::GamepadKey::DPad_Left, dae::InputEventType::Pressed, std::make_unique<dae::MoveCommand>(glm::ivec2{ -1, 0 }, mainObj->GetComponent<dae::MovementComponent>()), 0);
	input.AddCommand(dae::GamepadKey::DPad_Right, dae::InputEventType::Pressed, std::make_unique<dae::MoveCommand>(glm::ivec2{ 1, 0 }, mainObj->GetComponent<dae::MovementComponent>()), 0);
	input.AddCommand(dae::GamepadKey::DPad_Up, dae::InputEventType::Pressed, std::make_unique<dae::MoveCommand>(glm::ivec2{ 0, -1 }, mainObj->GetComponent<dae::MovementComponent>()), 0);
	input.AddCommand(dae::GamepadKey::DPad_Down, dae::InputEventType::Pressed, std::make_unique<dae::MoveCommand>(glm::ivec2{ 0, 1 }, mainObj->GetComponent<dae::MovementComponent>()), 0);

	input.AddCommand(dae::GamepadAxis2D::LThumbStick, std::make_unique<dae::MoveCommand>(glm::ivec2{ 0, 0 }, mainObj->GetComponent<dae::MovementComponent>()), 0);

	input.AddCommand(SDL_SCANCODE_SPACE, dae::InputEventType::Down, std::make_unique<dae::ShootCommand>(mainObj, mainObj->GetComponent<dae::ShootingComponent>()));
	input.AddCommand(dae::GamepadKey::RShoulder, dae::InputEventType::Down, std::make_unique<dae::ShootCommand>(mainObj, mainObj->GetComponent<dae::ShootingComponent>()), 0);

	input.AddCommand(SDL_SCANCODE_L, dae::InputEventType::Pressed, std::make_unique<dae::AimCommand>(glm::vec2{ 1,0 }, mainObj->GetComponent<dae::ShootingComponent>()));
	input.AddCommand(SDL_SCANCODE_J, dae::InputEventType::Pressed, std::make_unique<dae::AimCommand>(glm::vec2{ -1,0 }, mainObj->GetComponent<dae::ShootingComponent>()));
	input.AddCommand(SDL_SCANCODE_I, dae::InputEventType::Pressed, std::make_unique<dae::AimCommand>(glm::vec2{ 0,-1 }, mainObj->GetComponent<dae::ShootingComponent>()));
	input.AddCommand(SDL_SCANCODE_K, dae::InputEventType::Pressed, std::make_unique<dae::AimCommand>(glm::vec2{ 0,1 }, mainObj->GetComponent<dae::ShootingComponent>()));

	input.AddCommand(dae::GamepadAxis2D::RThumbStick, std::make_unique<dae::AimCommand>(glm::ivec2{ 0, 0 }, mainObj->GetComponent<dae::ShootingComponent>()), 0, true);
	input.AddCommand(SDL_SCANCODE_F1, dae::InputEventType::Down, std::make_unique<dae::SkipLevelCommand>());
	input.AddCommand(SDL_SCANCODE_F2, dae::InputEventType::Down, std::make_unique<dae::MuteCommand>());
	input.AddCommand(SDL_SCANCODE_F3, dae::InputEventType::Down, std::make_unique<dae::PVPCommand>());

	scene2.Initialize();
}

void dae::GameMode::LoadLevelPvp()
{
	m_CurrentLevel = 3;
	dae::SceneManager::GetInstance().ClearScenes();
	// load scene 2
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto fontSmall = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 16);
	auto& bulletManager = dae::BulletManager::GetInstance();
	bulletManager.SetTexture("Sprites/BulletNPC.png");
	dae::Level& level = dae::Level::GetInstance();
	level.Load("LevelLayoutPVP.csv");
	auto& scene2 = dae::SceneManager::GetInstance().CreateScene("Level2");
	auto fps2 = std::make_unique<dae::GameObject>(&scene2, dae::RenderLayer::UI);
	fps2->AddComponent<dae::FPSComponent>();
	fps2->AddComponent<dae::TextComponent>(fontSmall, "FPS");
	fps2->SetLocalPos(glm::vec2{ 10, 10 });
	scene2.Add(std::move(fps2));

	auto goRoot2 = std::make_unique<dae::GameObject>(&scene2, dae::RenderLayer::BackGround);
	auto rootObj2 = scene2.Add(std::move(goRoot2));
	rootObj2->SetLocalPos(glm::vec2{ 0, 0 });

	glm::vec2 playerSpawnPos2 = level.GetPlayerSpawn(0);
	auto go42 = std::make_unique<dae::GameObject>(&scene2, dae::RenderLayer::ObjectTop);
	go42->AddComponent<dae::SpriteComponent>("Sprites/RedTank.png");
	go42->AddComponent<dae::HealthComponent>(3);
	go42->AddComponent<dae::ScoreComponent>(0);
	go42->AddComponent<dae::MovementComponent>(125.f);
	go42->AddComponent<dae::ShootingComponent>(150.f, true);
	go42->SetLocalPos(playerSpawnPos2);
	auto mainObj2 = scene2.Add(std::move(go42), true);

	glm::vec2 player2Spawn = level.GetEnemySpawn();

	auto go5 = std::make_unique<dae::GameObject>(&scene2, dae::RenderLayer::ObjectTop);
	go5->AddComponent<dae::SpriteComponent>("Sprites/BlueTank.png");
	go5->AddComponent<dae::HealthComponent>(3);
	go5->AddComponent<dae::ScoreComponent>(0);
	go5->AddComponent<dae::MovementComponent>(125.f);
	go5->AddComponent<dae::ShootingComponent>(150.f, false);
	go5->SetLocalPos(player2Spawn);
	auto enemyObj = scene2.Add(std::move(go5), false, true);
	enemyObj->SetParent(rootObj2, false);
	bulletManager.AddEnemy(enemyObj);
	
	bulletManager.AddPlayer(mainObj2);


	mainObj2->SetParent(rootObj2, false);

	auto HealthDisplay1 = std::make_unique<dae::GameObject>(&scene2, dae::RenderLayer::UI);
	HealthDisplay1->AddComponent<dae::TextComponent>(fontSmall, "Player 1 health: ");
	HealthDisplay1->AddComponent<dae::HealthDisplayComponent>(mainObj2);
	HealthDisplay1->SetLocalPos(glm::ivec2{ 50, 100 });
	scene2.Add(std::move(HealthDisplay1));

	auto ScoreDisplay1 = std::make_unique<dae::GameObject>(&scene2, dae::RenderLayer::UI);
	ScoreDisplay1->AddComponent<dae::TextComponent>(fontSmall, "Player 1 score: ");
	ScoreDisplay1->AddComponent<dae::ScoreDisplayComponent>(mainObj2);
	ScoreDisplay1->SetLocalPos(glm::ivec2{ 50, 50 });
	scene2.Add(std::move(ScoreDisplay1));

	auto HealthDisplay2 = std::make_unique<dae::GameObject>(&scene2, dae::RenderLayer::UI);
	HealthDisplay2->AddComponent<dae::TextComponent>(fontSmall, "Player 2 health: ");
	HealthDisplay2->AddComponent<dae::HealthDisplayComponent>(enemyObj);
	HealthDisplay2->SetLocalPos(glm::ivec2{ 500, 100 });
	scene2.Add(std::move(HealthDisplay2));

	auto ScoreDisplay2 = std::make_unique<dae::GameObject>(&scene2, dae::RenderLayer::UI);
	ScoreDisplay2->AddComponent<dae::TextComponent>(fontSmall, "Player 1 score: ");
	ScoreDisplay2->AddComponent<dae::ScoreDisplayComponent>(enemyObj);
	ScoreDisplay2->SetLocalPos(glm::ivec2{ 500, 50 });
	scene2.Add(std::move(ScoreDisplay2));

	scene2.SetActive(true);


	GameObject* mainObj = scene2.GetPlayers()[0];
	dae::InputManager& input = dae::InputManager::GetInstance();
	input.ClearCommands();
	input.AddCommand(SDL_SCANCODE_A, dae::InputEventType::Pressed, std::make_unique<dae::MoveCommand>(glm::ivec2{ -1, 0 }, mainObj->GetComponent<dae::MovementComponent>()));
	input.AddCommand(SDL_SCANCODE_D, dae::InputEventType::Pressed, std::make_unique<dae::MoveCommand>(glm::ivec2{ 1, 0 }, mainObj->GetComponent<dae::MovementComponent>()));
	input.AddCommand(SDL_SCANCODE_W, dae::InputEventType::Pressed, std::make_unique<dae::MoveCommand>(glm::ivec2{ 0, -1 }, mainObj->GetComponent<dae::MovementComponent>()));
	input.AddCommand(SDL_SCANCODE_S, dae::InputEventType::Pressed, std::make_unique<dae::MoveCommand>(glm::ivec2{ 0, 1 }, mainObj->GetComponent<dae::MovementComponent>()));

	input.AddCommand(dae::GamepadKey::DPad_Left, dae::InputEventType::Pressed, std::make_unique<dae::MoveCommand>(glm::ivec2{ -1, 0 }, mainObj->GetComponent<dae::MovementComponent>()), 1);
	input.AddCommand(dae::GamepadKey::DPad_Right, dae::InputEventType::Pressed, std::make_unique<dae::MoveCommand>(glm::ivec2{ 1, 0 }, mainObj->GetComponent<dae::MovementComponent>()), 1);
	input.AddCommand(dae::GamepadKey::DPad_Up, dae::InputEventType::Pressed, std::make_unique<dae::MoveCommand>(glm::ivec2{ 0, -1 }, mainObj->GetComponent<dae::MovementComponent>()), 1);
	input.AddCommand(dae::GamepadKey::DPad_Down, dae::InputEventType::Pressed, std::make_unique<dae::MoveCommand>(glm::ivec2{ 0, 1 }, mainObj->GetComponent<dae::MovementComponent>()), 1);

	input.AddCommand(dae::GamepadAxis2D::LThumbStick, std::make_unique<dae::MoveCommand>(glm::ivec2{ 0, 0 }, mainObj->GetComponent<dae::MovementComponent>()), 1);


	input.AddCommand(SDL_SCANCODE_SPACE, dae::InputEventType::Down, std::make_unique<dae::ShootCommand>(mainObj, mainObj->GetComponent<dae::ShootingComponent>()));
	input.AddCommand(dae::GamepadKey::RShoulder, dae::InputEventType::Down, std::make_unique<dae::ShootCommand>(mainObj, mainObj->GetComponent<dae::ShootingComponent>()), 1);

	input.AddCommand(SDL_SCANCODE_L, dae::InputEventType::Pressed, std::make_unique<dae::AimCommand>(glm::vec2{ 1,0 }, mainObj->GetComponent<dae::ShootingComponent>()));
	input.AddCommand(SDL_SCANCODE_J, dae::InputEventType::Pressed, std::make_unique<dae::AimCommand>(glm::vec2{ -1,0 }, mainObj->GetComponent<dae::ShootingComponent>()));
	input.AddCommand(SDL_SCANCODE_I, dae::InputEventType::Pressed, std::make_unique<dae::AimCommand>(glm::vec2{ 0,-1 }, mainObj->GetComponent<dae::ShootingComponent>()));
	input.AddCommand(SDL_SCANCODE_K, dae::InputEventType::Pressed, std::make_unique<dae::AimCommand>(glm::vec2{ 0,1 }, mainObj->GetComponent<dae::ShootingComponent>()));

	input.AddCommand(dae::GamepadAxis2D::RThumbStick, std::make_unique<dae::AimCommand>(glm::ivec2{ 0, 0 }, mainObj->GetComponent<dae::ShootingComponent>()), 1, true);
	input.AddCommand(SDL_SCANCODE_F3, dae::InputEventType::Down, std::make_unique<dae::PVECommand>());
	input.AddCommand(SDL_SCANCODE_F2, dae::InputEventType::Down, std::make_unique<dae::MuteCommand>());

	//player 2
	input.AddCommand(dae::GamepadKey::DPad_Left, dae::InputEventType::Pressed, std::make_unique<dae::MoveCommand>(glm::ivec2{ -1, 0 }, enemyObj->GetComponent<dae::MovementComponent>()), 0);
	input.AddCommand(dae::GamepadKey::DPad_Right, dae::InputEventType::Pressed, std::make_unique<dae::MoveCommand>(glm::ivec2{ 1, 0 }, enemyObj->GetComponent<dae::MovementComponent>()), 0);
	input.AddCommand(dae::GamepadKey::DPad_Up, dae::InputEventType::Pressed, std::make_unique<dae::MoveCommand>(glm::ivec2{ 0, -1 }, enemyObj->GetComponent<dae::MovementComponent>()), 0);
	input.AddCommand(dae::GamepadKey::DPad_Down, dae::InputEventType::Pressed, std::make_unique<dae::MoveCommand>(glm::ivec2{ 0, 1 }, enemyObj->GetComponent<dae::MovementComponent>()), 0);

	input.AddCommand(dae::GamepadAxis2D::LThumbStick, std::make_unique<dae::MoveCommand>(glm::ivec2{ 0, 0 }, enemyObj->GetComponent<dae::MovementComponent>()), 0);

	input.AddCommand(dae::GamepadKey::RShoulder, dae::InputEventType::Down, std::make_unique<dae::ShootCommand>(enemyObj, enemyObj->GetComponent<dae::ShootingComponent>()), 0);
	input.AddCommand(dae::GamepadAxis2D::RThumbStick, std::make_unique<dae::AimCommand>(glm::ivec2{ 0, 0 }, enemyObj->GetComponent<dae::ShootingComponent>()), 0, true);

	scene2.Initialize();
}

void dae::GameMode::Setlevel(int levelNum)
{
	m_CurrentLevel = levelNum;
	m_bLevelChangeFlag = true;
}

void dae::GameMode::NextLevel()
{
	switch (m_CurrentLevel)
	{
	case 0:
		m_CurrentLevel = 1;
		m_bLevelChangeFlag = true;
		break;
	case 1:
		m_bLevelChangeFlag = true;
		m_CurrentLevel = 2;
		break;
	case 2:
		m_bLevelChangeFlag = true;
		m_CurrentLevel = 0;
		break;
	}
}

void dae::GameMode::Update()
{
	if (m_bLevelChangeFlag)
	{
		BulletManager::GetInstance().ClearPlayersEnemies();
		SceneManager::GetInstance().End();
		SceneManager::GetInstance().ClearScenes();
		switch (m_CurrentLevel)
		{
		case 0:
			LoadLevel0();
			m_bLevelChangeFlag = false;
			break;
		case 1:
			LoadLevel1();
			m_bLevelChangeFlag = false;
			break;
		case 2:
			LoadLevel2();
			m_bLevelChangeFlag = false;
			break;
		case 3:
			LoadLevelPvp();
			m_bLevelChangeFlag = false;
			break;
		}
	}
}
