
#include <SDL.h>
//#include <glm/vec2.hpp> // Include glm for vec2

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif


#include <steam_api.h>
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
#include "DisplayHealthComponent.h"
#include "DisplayScoreComponent.h"
#include "CSteamAchievements.h"
#include "DisplayAchievementsComponent.h"

// Defining our achievements
enum EAchievements
{
	ACH_WIN_ONE_GAME = 0,
	ACH_WIN_100_GAMES = 1,
	ACH_TRAVEL_FAR_ACCUM = 2,
	ACH_TRAVEL_FAR_SINGLE = 3,
};

// Achievement array which will hold data about the achievements and their state
dae::Achievement_t g_Achievements[] =
{
	_ACH_ID(ACH_WIN_ONE_GAME, "Winner"),
	_ACH_ID(ACH_WIN_100_GAMES, "Champion"),
	_ACH_ID(ACH_TRAVEL_FAR_ACCUM, "Interstellar"),
	_ACH_ID(ACH_TRAVEL_FAR_SINGLE, "Orbiter"),
};

// Global access to Achievements object
std::unique_ptr<dae::CSteamAchievements> g_SteamAchievements = nullptr;

void W01(dae::Scene& scene); 
void W02(dae::Scene& scene);
void W03(dae::Scene& scene);
void W04(dae::Scene& scene);
void W05(dae::Scene& scene);

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Current Assignment: Week05");

	W05(scene);


}

int main(int, char*[]) 
{
	if (!SteamAPI_Init())
	{
		std::cerr << "Fatal Error - Steam must be running to play this game (SteamAPI_Init() failed)." << std::endl;
		return 1;
	}
	else
	{
		g_SteamAchievements = std::make_unique<dae::CSteamAchievements>(g_Achievements, 4);
		std::cout << "Successfully initialized steam." << std::endl;
	}

	dae::Minigin engine("../Data/");
	engine.Run(load);
	SteamAPI_Shutdown();
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
	textBlueTank->GetComponent<dae::TextComponent>()->SetColor(SDL_Color(0, 0,255));
	textBlueTank->SetPosition(5, 50);
	scene.Add(textBlueTank);

	auto textRedTank = std::make_shared<dae::GameObject>();
	textBlueTank->AddChild(textRedTank);
	textRedTank->AddComponent<dae::TextComponent>("Use D-Pad to move the Red Tank", fontDescription);
	textRedTank->SetPosition(0, 20);
	textRedTank->GetComponent<dae::TextComponent>()->SetColor(SDL_Color(255, 0, 0));
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

void W05(dae::Scene& scene)
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

	auto fontFPS = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	auto fps = std::make_shared<dae::GameObject>();
	fps->AddComponent<dae::TextComponent>("0", fontFPS);
	fps->AddComponent<dae::FPSComponent>();
	fps->SetPosition(5, 10);
	scene.Add(fps);

	//blue tank description
	auto fontDescription = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 15);
	auto textBlueTank = std::make_shared<dae::GameObject>();
	textBlueTank->AddComponent<dae::TextComponent>("WASD to move the Blue Tank, C to take damage, Z to collect points and R to reset", fontDescription);
	textBlueTank->GetComponent<dae::TextComponent>()->SetColor(SDL_Color(100, 150, 255));
	textBlueTank->SetPosition(5, 50);
	scene.Add(textBlueTank);

	//red tank description
	auto textRedTank = std::make_shared<dae::GameObject>();
	textBlueTank->AddChild(textRedTank);
	textRedTank->AddComponent<dae::TextComponent>("D-Pad to move the Red Tank, X to take damage, A to collect points and Start to reset", fontDescription);
	textRedTank->SetPosition(0, 20);
	textRedTank->GetComponent<dae::TextComponent>()->SetColor(SDL_Color(255, 0, 0));
	scene.Add(textRedTank);

	//blue tank health display
	auto blueTankhealth = std::make_shared<dae::GameObject>();
	blueTankhealth->AddComponent<dae::TextComponent>("0",fontDescription)->SetColor(SDL_Color(100, 150, 255));
	blueTankhealth->AddComponent<dae::DisplayHealthComponent>();
	blueTankhealth->SetPosition(5, 100);
	scene.Add(blueTankhealth);

	//blue tank score display
	auto blueTankScore = std::make_shared<dae::GameObject>();
	blueTankScore->AddComponent<dae::TextComponent>("Score: 0", fontDescription)->SetColor(SDL_Color(100,150, 255));
	blueTankScore->AddComponent<dae::DisplayScoreComponent>();
	blueTankScore->SetPosition(5, 120);
	scene.Add(blueTankScore);

	//blue tank object
	float tankSpeed = 100.f;
	auto blueTank = std::make_shared<dae::GameObject>();
	blueTank->AddComponent<dae::RenderComponent>()->SetTexture("blueTank.png");
	blueTank->AddComponent<dae::PlayerStatsComponent>(5)->AddObserver(blueTankhealth->GetComponent<dae::DisplayHealthComponent>()); //add observers
	blueTank->GetComponent<dae::PlayerStatsComponent>()->AddObserver(blueTankScore->GetComponent<dae::DisplayScoreComponent>());
	blueTankhealth->GetComponent<dae::TextComponent>()->SetText("Health: " + std::to_string(blueTank->GetComponent<dae::PlayerStatsComponent>()->GetHealth()));
	blueTank->SetPosition(50, 350);
	scene.Add(blueTank);

	//keyboard input
	//up
	dae::InputManager::GetInstance().AddKeyboardCommand(SDL_SCANCODE_W, dae::KeyState::Down,
		std::make_unique<dae::Move>(blueTank.get(), glm::vec2{ 0, -1 }, tankSpeed));
	//down
	dae::InputManager::GetInstance().AddKeyboardCommand(SDL_SCANCODE_S, dae::KeyState::Down,
		std::make_unique<dae::Move>(blueTank.get(), glm::vec2{ 0, 1 }, tankSpeed));
	//right
	dae::InputManager::GetInstance().AddKeyboardCommand(SDL_SCANCODE_D, dae::KeyState::Down,
		std::make_unique<dae::Move>(blueTank.get(), glm::vec2{ 1, 0 }, tankSpeed));
	//left
	dae::InputManager::GetInstance().AddKeyboardCommand(SDL_SCANCODE_A, dae::KeyState::Down,
		std::make_unique<dae::Move>(blueTank.get(), glm::vec2{ -1, 0 }, tankSpeed));
	//take damage
	dae::InputManager::GetInstance().AddKeyboardCommand(SDL_SCANCODE_C, dae::KeyState::Released,
		std::make_unique<dae::TakeDamage>(blueTank.get()));
	//increase score
	dae::InputManager::GetInstance().AddKeyboardCommand(SDL_SCANCODE_Z, dae::KeyState::Released,
		std::make_unique<dae::IncreaseScore>(blueTank.get()));

	//red tank health display
	auto redTankHealth = std::make_shared<dae::GameObject>();
	redTankHealth->AddComponent<dae::TextComponent>("0", fontDescription)->SetColor(SDL_Color(255,0,0));
	redTankHealth->AddComponent<dae::DisplayHealthComponent>();
	redTankHealth->SetPosition(5, 140);
	scene.Add(redTankHealth);

	//red tank score display
	auto redTankScore = std::make_shared<dae::GameObject>();
	redTankScore->AddComponent<dae::TextComponent>("Score: 0", fontDescription)->SetColor(SDL_Color(255, 0, 0));
	redTankScore->AddComponent<dae::DisplayScoreComponent>();
	redTankScore->SetPosition(5, 160);
	scene.Add(redTankScore);

	

	//red tank object
	auto redTank = std::make_shared<dae::GameObject>();
	redTank->AddComponent<dae::RenderComponent>()->SetTexture("redTank.png");
	redTank->AddComponent<dae::PlayerStatsComponent>(5)->AddObserver(redTankHealth->GetComponent<dae::DisplayHealthComponent>()); //add observers
	redTank->GetComponent<dae::PlayerStatsComponent>()->AddObserver(redTankScore->GetComponent<dae::DisplayScoreComponent>());
	redTankHealth->GetComponent<dae::TextComponent>()->SetText("Health: " + std::to_string(redTank->GetComponent<dae::PlayerStatsComponent>()->GetHealth()));
	redTank->SetPosition(100, 350);
	scene.Add(redTank);

	//controller
	dae::InputManager::GetInstance().AddController(0);
	//up
	dae::InputManager::GetInstance().AddControllerCommand(0, dae::Controller::GamepadButton::DPadUp, dae::KeyState::Down,
		std::make_unique<dae::Move>(redTank.get(), glm::vec2{ 0, -1 }, tankSpeed * 2));
	//down
	dae::InputManager::GetInstance().AddControllerCommand(0, dae::Controller::GamepadButton::DPadDown, dae::KeyState::Down,
		std::make_unique<dae::Move>(redTank.get(), glm::vec2{ 0, 1 }, tankSpeed * 2));
	//right
	dae::InputManager::GetInstance().AddControllerCommand(0, dae::Controller::GamepadButton::DPadRight, dae::KeyState::Down,
		std::make_unique<dae::Move>(redTank.get(), glm::vec2{ 1, 0 }, tankSpeed * 2));
	//left
	dae::InputManager::GetInstance().AddControllerCommand(0, dae::Controller::GamepadButton::DPadLeft, dae::KeyState::Down,
		std::make_unique<dae::Move>(redTank.get(), glm::vec2{ -1, 0 }, tankSpeed * 2));
	//take damage
	dae::InputManager::GetInstance().AddControllerCommand(0, dae::Controller::GamepadButton::X, dae::KeyState::Released,
		std::make_unique<dae::TakeDamage>(redTank.get()));
	//increase score
	dae::InputManager::GetInstance().AddControllerCommand(0, dae::Controller::GamepadButton::A, dae::KeyState::Released,
		std::make_unique<dae::IncreaseScore>(redTank.get()));

	
	//achivement display observer
	if (g_SteamAchievements)
	{
		auto achievement = std::make_shared<dae::GameObject>();
		int achievThreshold = 100;
		achievement->AddComponent<dae::DisplayAchievementsComponent>(achievThreshold);
		blueTank->GetComponent<dae::PlayerStatsComponent>()->AddObserver(achievement->GetComponent<dae::DisplayAchievementsComponent>());
		redTank->GetComponent<dae::PlayerStatsComponent>()->AddObserver(achievement->GetComponent<dae::DisplayAchievementsComponent>());
		scene.Add(achievement);
	}
	
	//resets stats and achievments (i know its not the best way to reset the achievments with the stats but its just for showcase)
	dae::InputManager::GetInstance().AddKeyboardCommand(SDL_SCANCODE_R, dae::KeyState::Released,
		std::make_unique<dae::ResetAchievements>(blueTank.get()));

	dae::InputManager::GetInstance().AddControllerCommand(0, dae::Controller::GamepadButton::Start, dae::KeyState::Released,
		std::make_unique<dae::ResetAchievements>(redTank.get()));

}
