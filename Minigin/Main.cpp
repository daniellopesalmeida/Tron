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
#include "Scene.h"
#include "RenderComponent.h"
#include "TextComponent.h"
#include "FPSComponent.h"

void load()
{
	//auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");
	//
	//auto go = std::make_shared<dae::GameObject>();
	//go->SetTexture("background.tga");
	//scene.Add(go);
	//
	//go = std::make_shared<dae::GameObject>();
	//go->SetTexture("logo.tga");
	//go->SetPosition(216, 180);
	//scene.Add(go);
	//
	//auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	//auto to = std::make_shared<dae::TextObject>("Programming 4 Assignment", font);
	//to->SetPosition(80, 20);
	//scene.Add(to);

	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	auto backGround = std::make_shared<dae::GameObject>();
	backGround->AddComponent<dae::RenderComponent>()->SetTexture("background.tga");
	scene.Add(backGround);

	auto logo=  std::make_shared<dae::GameObject>();
	logo->AddComponent<dae::RenderComponent>()->SetTexture("logo.tga");
	logo->SetPosition(216, 180);
	scene.Add(logo);
	
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto title = std::make_shared<dae::GameObject>();
	title->AddComponent<dae::TextComponent>("Programming 4 Assignment", font);
	title->SetPosition(100, 0);
	scene.Add(title);

	auto fps= std::make_shared<dae::GameObject>();
	fps->AddComponent<dae::TextComponent>("0",font);
	fps->AddComponent<dae::FPSComponent>();
	fps->SetPosition(0, 300);
	scene.Add(fps);

}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}