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
#include "HealthCommand.h"
#include "ScoreDisplayComponent.h"
#include "ScoreComponent.h"
#include "ScoreComand.h"
#include "Level.h"
#include "ShootCommand.h"
#include "AimCommand.h"
#include <AIComponent.h>
#include "AIRoamState.h"



void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto fontSmall = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 16);

	auto& input = dae::InputManager::GetInstance();

	auto& level = dae::Level::GetInstance();
	level.Load("LevelLayout0.csv");

	auto& bulletManager = dae::BulletManager::GetInstance();
	bulletManager.SetTexture("Sprites/BulletNPC.png");
	

	/*auto go3 = std::make_unique<dae::GameObject>(&scene, dae::RenderLayer::BackGround);
	go3->AddComponent<dae::SpriteComponent>("background.tga");
	scene.Add(std::move(go3));*/

	/*auto go2 = std::make_unique<dae::GameObject>(&scene, dae::RenderLayer::BackGround);
	go2->AddComponent<dae::SpriteComponent>("logo.tga");
	go2->SetLocalPos(glm::vec3{ 216.f, 180.f, 1.f });
	scene.Add(std::move(go2));*/

	//auto go = std::make_unique<dae::GameObject>(&scene, dae::RenderLayer::UI);
	//go->AddComponent<dae::TextComponent>(font, "Programming 4 Assignment");
	//go->SetLocalPos(glm::vec3{ 80.f, 20.f, 1.f });
	//scene.Add(std::move(go));

	auto fps = std::make_unique<dae::GameObject>(&scene, dae::RenderLayer::UI);
	fps->AddComponent<dae::FPSComponent>();
	fps->AddComponent<dae::TextComponent>(fontSmall, "FPS");
	fps->SetLocalPos(glm::vec2{ 10, 10});
	scene.Add(std::move(fps));

	auto goRoot = std::make_unique<dae::GameObject>(&scene, dae::RenderLayer::BackGround);
	auto rootObj = scene.Add(std::move(goRoot));
	rootObj->SetLocalPos(glm::vec2{ 0, 0});

	auto go4 = std::make_unique<dae::GameObject>(&scene, dae::RenderLayer::ObjectTop);
	go4->AddComponent<dae::SpriteComponent>("Sprites/RedTank.png");
	go4->AddComponent<dae::HealthComponent>(3);
	go4->AddComponent<dae::ScoreComponent>(0);
	go4->AddComponent<dae::MovementComponent>(100.f);
	go4->AddComponent<dae::ShootingComponent>(150.f);
	go4->SetLocalPos(glm::ivec2{ level.GetTileWidth() *1.5f  , level.GetTileHeight() *1.5f});
	auto mainObj = scene.Add(std::move(go4));

	auto go5 = std::make_unique<dae::GameObject>(&scene, dae::RenderLayer::ObjectTop);
	go5->AddComponent<dae::SpriteComponent>("Sprites/GreenTank.png");
	go5->AddComponent<dae::HealthComponent>(3);
	go5->AddComponent<dae::ScoreComponent>(0);
	go5->AddComponent<dae::MovementComponent>(100.f);
	go5->AddComponent<dae::AIComponent>( std::make_unique<dae::AIRoamState>(go5.get(), go5->GetComponent<dae::MovementComponent>()));
	go5->GetComponent<dae::AIComponent>()->SetTarget(mainObj);
	go5->SetLocalPos(glm::vec2{ level.GetTileWidth() *1.5f  , level.GetTileHeight() * 18.5f });
	auto enemyObj = scene.Add(std::move(go5));
	

	//auto go5 = std::make_unique<dae::GameObject>(&scene, dae::RenderLayer::ObjectTop);
	//go5->AddComponent<dae::SpriteComponent>("digger2.png");
	//go5->AddComponent<dae::RotationComponent>(60.f, 300.f);
	//auto childObj = scene.Add(std::move(go5));

	mainObj->SetParent(rootObj, false);
	enemyObj->SetParent(rootObj, false);

	auto HealthDisplay = std::make_unique<dae::GameObject>(&scene, dae::RenderLayer::UI);
	HealthDisplay->AddComponent<dae::TextComponent>(fontSmall, "Player 1 health: ");
	HealthDisplay->AddComponent<dae::HealthDisplayComponent>(mainObj);
	HealthDisplay->SetLocalPos(glm::ivec2{ 10, 100 });
	scene.Add(std::move(HealthDisplay));

	auto ScoreDisplay = std::make_unique<dae::GameObject>(&scene, dae::RenderLayer::UI);
	ScoreDisplay->AddComponent<dae::TextComponent>(fontSmall, "Player 1 score: ");
	ScoreDisplay->AddComponent<dae::ScoreDisplayComponent>(mainObj);
	ScoreDisplay->SetLocalPos(glm::ivec2{ 10, 150});
	scene.Add(std::move(ScoreDisplay));

	

	input.AddCommand(SDL_SCANCODE_A, dae::InputEventType::Pressed, std::make_unique<dae::MoveCommand>(glm::ivec2{ -1, 0 }, mainObj->GetComponent<dae::MovementComponent>()));
	input.AddCommand(SDL_SCANCODE_D, dae::InputEventType::Pressed, std::make_unique<dae::MoveCommand>(glm::ivec2{ 1, 0 }, mainObj->GetComponent<dae::MovementComponent>()));
	input.AddCommand(SDL_SCANCODE_W, dae::InputEventType::Pressed, std::make_unique<dae::MoveCommand>(glm::ivec2{ 0, -1 }, mainObj->GetComponent<dae::MovementComponent>()));
	input.AddCommand(SDL_SCANCODE_S, dae::InputEventType::Pressed, std::make_unique<dae::MoveCommand>(glm::ivec2{ 0, 1 }, mainObj->GetComponent<dae::MovementComponent>()));

	input.AddCommand(dae::GamepadKey::DPad_Left, dae::InputEventType::Pressed, std::make_unique<dae::MoveCommand>(glm::ivec2{ -1, 0 }, mainObj->GetComponent<dae::MovementComponent>()), 0);
	input.AddCommand(dae::GamepadKey::DPad_Right, dae::InputEventType::Pressed, std::make_unique<dae::MoveCommand>(glm::ivec2{ 1, 0 }, mainObj->GetComponent<dae::MovementComponent>()), 0);
	input.AddCommand(dae::GamepadKey::DPad_Up, dae::InputEventType::Pressed, std::make_unique<dae::MoveCommand>(glm::ivec2{ 0, -1 }, mainObj->GetComponent<dae::MovementComponent>()), 0);
	input.AddCommand(dae::GamepadKey::DPad_Down, dae::InputEventType::Pressed, std::make_unique<dae::MoveCommand>(glm::ivec2{ 0, 1 }, mainObj->GetComponent<dae::MovementComponent>()), 0);

	input.AddCommand(dae::GamepadAxis2D::LThumbStick, std::make_unique<dae::MoveCommand>(glm::ivec2{ 0, 0 }, mainObj->GetComponent<dae::MovementComponent>()), 0);

	input.AddCommand(SDL_SCANCODE_X, dae::InputEventType::Down, std::make_unique<dae::HealthCommand>(mainObj, 1));

	input.AddCommand(SDL_SCANCODE_Z, dae::InputEventType::Down, std::make_unique<dae::ScoreCommand>(mainObj, 1));

	input.AddCommand(SDL_SCANCODE_SPACE, dae::InputEventType::Down, std::make_unique<dae::ShootCommand>(mainObj, mainObj->GetComponent<dae::ShootingComponent>()));

	input.AddCommand(SDL_SCANCODE_L, dae::InputEventType::Down, std::make_unique<dae::AimCommand>(glm::vec2{1,0}, mainObj->GetComponent<dae::ShootingComponent>()));
	input.AddCommand(SDL_SCANCODE_J, dae::InputEventType::Down, std::make_unique<dae::AimCommand>(glm::vec2{ -1,0 }, mainObj->GetComponent<dae::ShootingComponent>()));
	input.AddCommand(SDL_SCANCODE_I, dae::InputEventType::Down, std::make_unique<dae::AimCommand>(glm::vec2{ 0,-1 }, mainObj->GetComponent<dae::ShootingComponent>()));
	input.AddCommand(SDL_SCANCODE_K, dae::InputEventType::Down, std::make_unique<dae::AimCommand>(glm::vec2{ 0,1 }, mainObj->GetComponent<dae::ShootingComponent>()));

}

int main(int, char*[])
{
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}

