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
	fps->SetLocalPos(glm::vec3{ 10.f, 10.f, 1.f });
	scene.Add(std::move(fps));

	auto goRoot = std::make_unique<dae::GameObject>(&scene, dae::RenderLayer::BackGround);
	auto rootObj = scene.Add(std::move(goRoot));
	rootObj->SetLocalPos(glm::vec3{ 0.f, 0.f, 1.f });

	auto go4 = std::make_unique<dae::GameObject>(&scene, dae::RenderLayer::ObjectTop);
	go4->AddComponent<dae::SpriteComponent>("Sprites/RedTank.png");
	go4->AddComponent<dae::HealthComponent>(3);
	go4->AddComponent<dae::ScoreComponent>(0);
	go4->AddComponent<dae::MovementComponent>(50.f);
	go4->SetLocalPos(glm::vec2{ level.GetTileWidth() * 2 , level.GetTileHeight() * 2 });
	auto mainObj = scene.Add(std::move(go4));
	

	//auto go5 = std::make_unique<dae::GameObject>(&scene, dae::RenderLayer::ObjectTop);
	//go5->AddComponent<dae::SpriteComponent>("digger2.png");
	//go5->AddComponent<dae::RotationComponent>(60.f, 300.f);
	//auto childObj = scene.Add(std::move(go5));

	mainObj->SetParent(rootObj, false);
	//childObj->SetParent(mainObj, false);

	auto HealthDisplay = std::make_unique<dae::GameObject>(&scene, dae::RenderLayer::UI);
	HealthDisplay->AddComponent<dae::TextComponent>(fontSmall, "Player 1 health: ");
	HealthDisplay->AddComponent<dae::HealthDisplayComponent>(mainObj);
	HealthDisplay->SetLocalPos(glm::vec3{ 10.f, 100.f, 1.f });
	scene.Add(std::move(HealthDisplay));

	auto ScoreDisplay = std::make_unique<dae::GameObject>(&scene, dae::RenderLayer::UI);
	ScoreDisplay->AddComponent<dae::TextComponent>(fontSmall, "Player 1 score: ");
	ScoreDisplay->AddComponent<dae::ScoreDisplayComponent>(mainObj);
	ScoreDisplay->SetLocalPos(glm::vec3{ 10.f, 150.f, 1.f });
	scene.Add(std::move(ScoreDisplay));

	bulletManager.SpawnBullet(glm::vec2{ level.GetTileWidth() * 2 +2, level.GetTileHeight() * 2 +2 }, glm::vec2{100.f, 10.f}, mainObj);

	input.AddCommand(SDL_SCANCODE_A, dae::InputEventType::Pressed, std::make_unique<dae::MoveCommand>(glm::vec2{ -1.f, 0.f }, mainObj->GetComponent<dae::MovementComponent>()));
	input.AddCommand(SDL_SCANCODE_D, dae::InputEventType::Pressed, std::make_unique<dae::MoveCommand>(glm::vec2{ 1.f, 0.f }, mainObj->GetComponent<dae::MovementComponent>()));
	input.AddCommand(SDL_SCANCODE_W, dae::InputEventType::Pressed, std::make_unique<dae::MoveCommand>(glm::vec2{ 0.f, -1.f }, mainObj->GetComponent<dae::MovementComponent>()));
	input.AddCommand(SDL_SCANCODE_S, dae::InputEventType::Pressed, std::make_unique<dae::MoveCommand>(glm::vec2{ 0.f, 1.f }, mainObj->GetComponent<dae::MovementComponent>()));

	input.AddCommand(dae::GamepadKey::DPad_Left, dae::InputEventType::Pressed, std::make_unique<dae::MoveCommand>(glm::vec2{ -1.f, 0.f }, mainObj->GetComponent<dae::MovementComponent>()), 0);
	input.AddCommand(dae::GamepadKey::DPad_Right, dae::InputEventType::Pressed, std::make_unique<dae::MoveCommand>(glm::vec2{ 1.f, 0.f }, mainObj->GetComponent<dae::MovementComponent>()), 0);
	input.AddCommand(dae::GamepadKey::DPad_Up, dae::InputEventType::Pressed, std::make_unique<dae::MoveCommand>(glm::vec2{ 0.f, -1.f }, mainObj->GetComponent<dae::MovementComponent>()), 0);
	input.AddCommand(dae::GamepadKey::DPad_Down, dae::InputEventType::Pressed, std::make_unique<dae::MoveCommand>(glm::vec2{ 0.f, 1.f }, mainObj->GetComponent<dae::MovementComponent>()), 0);

	input.AddCommand(dae::GamepadAxis2D::LThumbStick, std::make_unique<dae::MoveCommand>(glm::vec2{ 0.f, 0.f }, mainObj->GetComponent<dae::MovementComponent>()), 0);

	input.AddCommand(SDL_SCANCODE_X, dae::InputEventType::Down, std::make_unique<dae::HealthCommand>(mainObj, 1));

	input.AddCommand(SDL_SCANCODE_Z, dae::InputEventType::Down, std::make_unique<dae::ScoreCommand>(mainObj, 1));

}

int main(int, char*[])
{
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}

