#include <SDL.h>
//#include <glm/vec2.hpp> // Include glm for vec2

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
#include "RotationComponent.h"
#include "ThrashTheCacheComponent.h"
#include "InputManager.h"

void W01(dae::Scene& scene); 
void W02(dae::Scene& scene);
void W03(dae::Scene& scene);
void W04(dae::Scene& scene);

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Current Assignment: Week04");

	W04(scene);


}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}

void W01(dae::Scene& scene)
{
	auto backGround = std::make_shared<dae::GameObject>();
	backGround->AddComponent<dae::RenderComponent>()->SetTexture("background.tga");
	scene.Add(backGround);

	auto logo = std::make_shared<dae::GameObject>();
	logo->AddComponent<dae::RenderComponent>()->SetTexture("logo.tga");
	logo->SetPosition(216, 180);
	scene.Add(logo);

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto title = std::make_shared<dae::GameObject>();
	title->AddComponent<dae::TextComponent>("Programming 4 Assignment", font);
	title->SetPosition(100, 0);
	scene.Add(title);

	auto fps = std::make_shared<dae::GameObject>();
	fps->AddComponent<dae::TextComponent>("0", font);
	fps->AddComponent<dae::FPSComponent>();
	fps->SetPosition(0, 300);
	scene.Add(fps);
}

void W02(dae::Scene& scene)
{
	auto backGround = std::make_shared<dae::GameObject>();
	backGround->AddComponent<dae::RenderComponent>()->SetTexture("background.tga");
	scene.Add(backGround);

	auto logo = std::make_shared<dae::GameObject>();
	logo->AddComponent<dae::RenderComponent>()->SetTexture("logo.tga");
	logo->SetPosition(216, 180);
	scene.Add(logo);

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto title = std::make_shared<dae::GameObject>();
	title->AddComponent<dae::TextComponent>("Programming 4 Assignment", font);
	title->SetPosition(100, 0);
	scene.Add(title);

	auto fps = std::make_shared<dae::GameObject>();
	fps->AddComponent<dae::TextComponent>("0", font);
	fps->AddComponent<dae::FPSComponent>();
	fps->SetPosition(0, 300);
	scene.Add(fps);

	auto tronTank1 = std::make_shared<dae::GameObject>();
	tronTank1->AddComponent<dae::RenderComponent>()->SetTexture("blueTank.png");
	tronTank1->SetPosition(300, 300);
	scene.Add(tronTank1);

	auto tronTank2 = std::make_shared<dae::GameObject>();
	tronTank1->AddChild(tronTank2);
	tronTank2->AddComponent<dae::RenderComponent>()->SetTexture("blueTank.png");
	tronTank2->SetPosition(0, 0);
	scene.Add(tronTank2);

	tronTank1->AddComponent<dae::RotationComponent>(20.f, 10.f);
	tronTank2->AddComponent<dae::RotationComponent>(70.f, 3.f);
}

void W03(dae::Scene& scene)
{
	auto backGround = std::make_shared<dae::GameObject>();
	backGround->AddComponent<dae::RenderComponent>()->SetTexture("background.tga");
	scene.Add(backGround);

	auto logo = std::make_shared<dae::GameObject>();
	logo->AddComponent<dae::RenderComponent>()->SetTexture("logo.tga");
	logo->SetPosition(216, 180);
	scene.Add(logo);

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto title = std::make_shared<dae::GameObject>();
	title->AddComponent<dae::TextComponent>("Programming 4 Assignment", font);
	title->SetPosition(100, 0);
	scene.Add(title);

	auto fps = std::make_shared<dae::GameObject>();
	fps->AddComponent<dae::TextComponent>("0", font);
	fps->AddComponent<dae::FPSComponent>();
	fps->SetPosition(0, 300);
	scene.Add(fps);

	auto imgui = std::make_shared<dae::GameObject>();
	imgui->AddComponent<dae::ThrashTheCacheComponent>();
	scene.Add(imgui);
}

void W04(dae::Scene& scene)
{
	auto backGround = std::make_shared<dae::GameObject>();
	backGround->AddComponent<dae::RenderComponent>()->SetTexture("background.tga");
	scene.Add(backGround);

	auto logo = std::make_shared<dae::GameObject>();
	logo->AddComponent<dae::RenderComponent>()->SetTexture("logo.tga");
	logo->SetPosition(216, 180);
	scene.Add(logo);

	auto fontTitle = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto title = std::make_shared<dae::GameObject>();
	title->AddComponent<dae::TextComponent>("Programming 4 Assignment", fontTitle);
	title->SetPosition(100, 0);
	scene.Add(title);

	auto fontFPS = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf",20);
	auto fps = std::make_shared<dae::GameObject>();
	fps->AddComponent<dae::TextComponent>("0", fontFPS);
	fps->AddComponent<dae::FPSComponent>();
	fps->SetPosition(5, 10);
	scene.Add(fps);

	auto fontDescription = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 15);
	auto textBlueTank = std::make_shared<dae::GameObject>();
	textBlueTank->AddComponent<dae::TextComponent>("Use WASD to move the Blue Tank", fontDescription);
	textBlueTank->SetPosition(5, 50);
	scene.Add(textBlueTank);

	auto textRedTank = std::make_shared<dae::GameObject>();
	textBlueTank->AddChild(textRedTank);
	textRedTank->AddComponent<dae::TextComponent>("Use D-Pad to move the Red Tank", fontDescription);
	textRedTank->SetPosition(0, 20);
	scene.Add(textRedTank);

	float tankSpeed = 100.f;
	auto keyboardTank = std::make_shared<dae::GameObject>();
	keyboardTank->AddComponent<dae::RenderComponent>()->SetTexture("blueTank.png");
	keyboardTank->SetPosition(50, 350);
	scene.Add(keyboardTank);

	//keyboard input
	//up
	dae::InputManager::GetInstance().AddKeyboardCommand(SDL_SCANCODE_W, dae::KeyState::Down,
		std::make_unique<dae::Move>(keyboardTank.get(), glm::vec2{ 0, -1 }, tankSpeed));
	//down
	dae::InputManager::GetInstance().AddKeyboardCommand(SDL_SCANCODE_S, dae::KeyState::Down,
		std::make_unique<dae::Move>(keyboardTank.get(), glm::vec2{ 0, 1 }, tankSpeed));
	//right
	dae::InputManager::GetInstance().AddKeyboardCommand(SDL_SCANCODE_D, dae::KeyState::Down,
		std::make_unique<dae::Move>(keyboardTank.get(), glm::vec2{ 1, 0 }, tankSpeed));
	//left
	dae::InputManager::GetInstance().AddKeyboardCommand(SDL_SCANCODE_A, dae::KeyState::Down,
		std::make_unique<dae::Move>(keyboardTank.get(), glm::vec2{ -1, 0 }, tankSpeed));

	auto controllerTank = std::make_shared<dae::GameObject>();
	controllerTank->AddComponent<dae::RenderComponent>()->SetTexture("redTank.png");
	controllerTank->SetPosition(100, 350);
	scene.Add(controllerTank);

	dae::InputManager::GetInstance().AddController(0);
	dae::InputManager::GetInstance().AddControllerCommand(0, dae::Controller::GamepadButton::DPadUp, dae::KeyState::Down,
		std::make_unique<dae::Move>(controllerTank.get(), glm::vec2{ 0, -1 }, tankSpeed * 2));
	dae::InputManager::GetInstance().AddControllerCommand(0, dae::Controller::GamepadButton::DPadDown, dae::KeyState::Down,
		std::make_unique<dae::Move>(controllerTank.get(), glm::vec2{ 0, 1 }, tankSpeed * 2));
	dae::InputManager::GetInstance().AddControllerCommand(0, dae::Controller::GamepadButton::DPadRight, dae::KeyState::Down,
		std::make_unique<dae::Move>(controllerTank.get(), glm::vec2{ 1, 0 }, tankSpeed * 2));
	dae::InputManager::GetInstance().AddControllerCommand(0, dae::Controller::GamepadButton::DPadLeft, dae::KeyState::Down,
		std::make_unique<dae::Move>(controllerTank.get(), glm::vec2{ -1, 0 }, tankSpeed * 2));

	//debug
	dae::InputManager::GetInstance().AddControllerCommand(0, dae::Controller::GamepadButton::RightThumb, dae::KeyState::Down,
		std::make_unique<dae::Debug>(controllerTank.get(), "RightThumb"));


}
