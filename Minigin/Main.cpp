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

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);



	auto bo = std::make_shared<dae::GameObject>();
	bo->AddComponent<dae::SpriteComponent>("background.tga");
	scene.Add(bo);

	auto lo = std::make_shared<dae::GameObject>();
	lo->AddComponent<dae::SpriteComponent>("logo.tga");
	lo->SetPosition(416, 280);
	scene.Add(lo);

	auto fo = std::make_shared<dae::GameObject>();
	fo->AddComponent<dae::TextComponent>(font, "FPS");
	fo->AddComponent<dae::FPSComponent>();
	fo->SetPosition(216, 180);
	scene.Add(fo);

	auto to = std::make_unique<dae::GameObject>();
	to->AddComponent<dae::TextComponent>(font, "Programming 4 Assignment");
	to->SetPosition( 80.f, 20.f);
	scene.Add(std::move(to));
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}