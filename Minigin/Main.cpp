#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "TextComponent.h"
#include "GameObject.h"
#include "Scene.h"
#include "FPSComponent.h"
#include "SpriteComponent.h"
#include "RotationComponent.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);



	auto go3 = std::make_unique<dae::GameObject>(&scene);
	go3->AddComponent<dae::SpriteComponent>("background.tga");
	scene.Add(std::move(go3));
	
	auto go2 = std::make_unique<dae::GameObject>(&scene);
	go2->AddComponent<dae::SpriteComponent>("logo.tga");
	go2->SetLocalPos(glm::vec3{ 216.f, 180.f, 1.f });
	scene.Add(std::move(go2));
	
	auto go = std::make_unique<dae::GameObject>(&scene);
	go->AddComponent<dae::TextComponent>(font, "Programming 4 Assignment");
	go->SetLocalPos(glm::vec3{ 80.f, 20.f, 1.f });
	scene.Add(std::move(go));
	
	auto fps = std::make_unique<dae::GameObject>(&scene);
	fps->AddComponent<dae::FPSComponent>();
	fps->AddComponent<dae::TextComponent>(font, "FPS");
	fps->SetLocalPos(glm::vec3{ 10.f, 10.f, 1.f });
	scene.Add(std::move(fps));
	
	auto goRoot = std::make_unique<dae::GameObject>(&scene);
	auto rootObj = scene.Add(std::move(goRoot));
	rootObj->SetLocalPos(glm::vec3{ 200.f, 200.f, 1.f });

	auto go4 = std::make_unique<dae::GameObject>(&scene);
	go4->AddComponent<dae::SpriteComponent>("digger.png");
	go4->AddComponent<dae::RotationComponent>(30.f, 150.f);
	go4->SetLocalPos(glm::vec3{ 280.f, 20.f, 1.f });
	auto mainObj = scene.Add(std::move(go4));

	
	auto go5 = std::make_unique<dae::GameObject>(&scene);
	go5->AddComponent<dae::SpriteComponent>("digger2.png");
	go5->AddComponent<dae::RotationComponent>(60.f, 300.f);
	auto childObj = scene.Add(std::move(go5));

	mainObj->SetParent(rootObj, false);
	childObj->SetParent(mainObj, false);
	
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}