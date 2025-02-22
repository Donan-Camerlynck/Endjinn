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



	auto go3 = std::make_unique<dae::GameObject>();
	go3->AddComponent<dae::SpriteComponent>("background.tga");
	scene.Add(std::move(go3));

	auto go2 = std::make_unique<dae::GameObject>();
	go2->AddComponent<dae::SpriteComponent>("logo.tga");
	go2->SetLocalPos(glm::vec3{ 216.f, 180.f, 1.f });
	scene.Add(std::move(go2));

	auto go = std::make_unique<dae::GameObject>();
	go->AddComponent<dae::TextComponent>(font, "Programming 4 Assignment");
	go->SetLocalPos(glm::vec3{ 80.f, 20.f, 1.f });
	scene.Add(std::move(go));

	auto fps = std::make_unique<dae::GameObject>();
	fps->AddComponent<dae::FPSComponent>();
	fps->AddComponent<dae::TextComponent>(font, "FPS");
	fps->SetLocalPos(glm::vec3{ 10.f, 10.f, 1.f });
	scene.Add(std::move(fps));

	auto go4 = std::make_unique<dae::GameObject>();
	go4->AddComponent<dae::SpriteComponent>("Digger.png");
	go4->SetLocalPos(glm::vec3{ 280.f, 20.f, 1.f });


	auto go5 = std::make_unique<dae::GameObject>();
	go5->AddComponent<dae::SpriteComponent>("Digger.png");
	go5->AddComponent<dae::RotationComponent>(30.f, 150.f);
	go5->SetParent(go4.get(), false);
	scene.Add(std::move(go4));
	scene.Add(std::move(go5));
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}