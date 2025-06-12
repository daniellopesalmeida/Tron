#include <SDL.h>

#if _DEBUG
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
#include "DisplayHealthComponent.h"
#include "DisplayScoreComponent.h"
#include "GameCommands.h"
#include <filesystem>
#include <ServiceLocator.h>
#include <SoundSystem.h>
#include <SDLSoundSystem.h>
#include <LoggingSoundSystem.h>
#include "PlayerCharacter.h"
#include "LevelCreator.h"


void W06(dae::Scene& scene);
void TestScene(dae::Scene& scene);
void StartMenu(dae::Scene& scene);

namespace fs = std::filesystem;
constexpr int MAX_TRAVERSAL = 5;

std::string FindDataFolder()
{
	fs::path currentDir = fs::current_path();
	fs::path dataPath = currentDir / "Data"; 

	int counter = 0;

	while (!fs::exists(dataPath) && counter < MAX_TRAVERSAL)
	{
		currentDir = currentDir.parent_path(); 
		dataPath = currentDir / "Data"; 
		counter++;
	}

	if (fs::exists(dataPath))
	{
		return dataPath.string();
	}
	else
	{
		throw std::runtime_error("Could not find 'Data' folder after traversing " + std::to_string(MAX_TRAVERSAL) + " levels.");
	}
}

void load()
{
	auto& testScene = dae::SceneManager::GetInstance().CreateScene("Test Scene");
	auto& testScene2 = dae::SceneManager::GetInstance().CreateScene("Test Scene2");

#if _DEBUG
	dae::ServiceLocator::RegisterSoundSystem(
		std::make_unique<dae::LoggingSoundSystem>(std::make_unique<dae::SDLSoundSystem>()));
#else
	dae::ServiceLocator::RegisterSoundSystem(std::make_unique<dae::SDLSoundSystem>());
#endif

	StartMenu(testScene);
	TestScene(testScene2);
	dae::SceneManager::GetInstance().SetScene(testScene2);
}
int main(int, char* []) 
{
	std::string dataPath = FindDataFolder();
	std::cout << "Found Data Path: " << dataPath << std::endl;
	dae::Minigin engine(dataPath);
	engine.Run(load);
	return 0;
}


void W06(dae::Scene& scene)
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
	fps->AddComponent<FPSComponent>();
	fps->SetPosition(5, 10);
	scene.Add(fps);

	auto tronFont = dae::ResourceManager::GetInstance().LoadFont("tronFont/tron.ttf", 15);

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
	blueTankhealth->AddComponent<dae::TextComponent>("# ", tronFont)->SetColor(SDL_Color(100, 150, 255));
	blueTankhealth->AddComponent<DisplayHealthComponent>();
	blueTankhealth->SetPosition(5, 100);
	scene.Add(blueTankhealth);

	//blue tank score display
	auto blueTankScore = std::make_shared<dae::GameObject>();
	blueTankScore->AddComponent<dae::TextComponent>("Score 0", tronFont)->SetColor(SDL_Color(100, 150, 255));
	blueTankScore->AddComponent<DisplayScoreComponent>();
	blueTankScore->SetPosition(5, 120);
	scene.Add(blueTankScore);

	//blue tank object
	float tankSpeed = 100.f;
	auto blueTank = std::make_shared<dae::GameObject>();
	blueTank->AddComponent<dae::RenderComponent>()->SetTexture("blueTank.png");
	blueTank->AddComponent<PlayerStatsComponent>(5)->AddObserver(blueTankhealth->GetComponent<DisplayHealthComponent>()); //add observers
	blueTank->GetComponent<PlayerStatsComponent>()->AddObserver(blueTankScore->GetComponent<DisplayScoreComponent>());
	blueTankhealth->GetComponent<dae::TextComponent>()->SetText("# " + std::to_string(blueTank->GetComponent<PlayerStatsComponent>()->GetHealth()));
	blueTank->SetPosition(50, 350);
	scene.Add(blueTank);

	auto blueTankText = std::make_shared<dae::GameObject>();
	blueTankText->AddComponent<dae::TextComponent>("P1", tronFont)->SetColor(SDL_Color(100, 150, 255));
	auto blueTankTextSize = blueTankText->GetComponent<dae::TextComponent>()->GetSize();
	auto blueTankTextureSize = blueTank->GetComponent<dae::RenderComponent>()->GetSize();
	blueTankText->SetPosition(float(blueTankTextureSize.x/2- blueTankTextSize.x/2), float(-blueTankTextSize.y-5));
	blueTank->AddChild(blueTankText);

	//keyboard input
	//up
	dae::InputManager::GetInstance().AddKeyboardCommand(SDL_SCANCODE_W, dae::KeyState::Down,
		std::make_unique<Move>(blueTank.get(), glm::vec2{ 0, -1 }, tankSpeed));
	//down
	dae::InputManager::GetInstance().AddKeyboardCommand(SDL_SCANCODE_S, dae::KeyState::Down,
		std::make_unique<Move>(blueTank.get(), glm::vec2{ 0, 1 }, tankSpeed));
	//right
	dae::InputManager::GetInstance().AddKeyboardCommand(SDL_SCANCODE_D, dae::KeyState::Down,
		std::make_unique<Move>(blueTank.get(), glm::vec2{ 1, 0 }, tankSpeed));
	//left
	dae::InputManager::GetInstance().AddKeyboardCommand(SDL_SCANCODE_A, dae::KeyState::Down,
		std::make_unique<Move>(blueTank.get(), glm::vec2{ -1, 0 }, tankSpeed));
	//take damage
	dae::InputManager::GetInstance().AddKeyboardCommand(SDL_SCANCODE_C, dae::KeyState::Released,
		std::make_unique<TakeDamage>(blueTank.get()));
	//increase score
	dae::InputManager::GetInstance().AddKeyboardCommand(SDL_SCANCODE_Z, dae::KeyState::Released,
		std::make_unique<IncreaseScore>(blueTank.get()));

	//red tank health display
	auto redTankHealth = std::make_shared<dae::GameObject>();
	redTankHealth->AddComponent<dae::TextComponent>("# ", tronFont)->SetColor(SDL_Color(255, 0, 0));
	redTankHealth->AddComponent<DisplayHealthComponent>();
	redTankHealth->SetPosition(5, 140);
	scene.Add(redTankHealth);

	//red tank score display
	auto redTankScore = std::make_shared<dae::GameObject>();
	redTankScore->AddComponent<dae::TextComponent>("Score 0", tronFont)->SetColor(SDL_Color(255, 0, 0));
	redTankScore->AddComponent<DisplayScoreComponent>();
	redTankScore->SetPosition(5, 160);
	scene.Add(redTankScore);



	//red tank object
	auto redTank = std::make_shared<dae::GameObject>();
	redTank->AddComponent<dae::RenderComponent>()->SetTexture("redTank.png",50);
	redTank->AddComponent<PlayerStatsComponent>(5)->AddObserver(redTankHealth->GetComponent<DisplayHealthComponent>()); //add observers
	redTank->GetComponent<PlayerStatsComponent>()->AddObserver(redTankScore->GetComponent<DisplayScoreComponent>());
	redTankHealth->GetComponent<dae::TextComponent>()->SetText("# " + std::to_string(redTank->GetComponent<PlayerStatsComponent>()->GetHealth()));
	redTank->SetPosition(100, 350);
	scene.Add(redTank);

	
	auto redTankText = std::make_shared<dae::GameObject>();
	redTankText->AddComponent<dae::TextComponent>("P2", tronFont)->SetColor(SDL_Color(255, 0, 0));
	auto redTankTextSize = redTankText->GetComponent<dae::TextComponent>()->GetSize();
	auto redTankTextureSize = redTank->GetComponent<dae::RenderComponent>()->GetSize();
	redTankText->SetPosition(float(redTankTextureSize.x / 2 - redTankTextSize.x / 2), float(-redTankTextSize.y-5));
	redTank->AddChild(redTankText);

	//controller
	dae::InputManager::GetInstance().AddController(0);
	//up
	dae::InputManager::GetInstance().AddControllerCommand(0, dae::Controller::GamepadButton::DPadUp, dae::KeyState::Down,
		std::make_unique<Move>(redTank.get(), glm::vec2{ 0, -1 }, tankSpeed * 2));
	//down
	dae::InputManager::GetInstance().AddControllerCommand(0, dae::Controller::GamepadButton::DPadDown, dae::KeyState::Down,
		std::make_unique<Move>(redTank.get(), glm::vec2{ 0, 1 }, tankSpeed * 2));
	//right
	dae::InputManager::GetInstance().AddControllerCommand(0, dae::Controller::GamepadButton::DPadRight, dae::KeyState::Down,
		std::make_unique<Move>(redTank.get(), glm::vec2{ 1, 0 }, tankSpeed * 2));
	//left
	dae::InputManager::GetInstance().AddControllerCommand(0, dae::Controller::GamepadButton::DPadLeft, dae::KeyState::Down,
		std::make_unique<Move>(redTank.get(), glm::vec2{ -1, 0 }, tankSpeed * 2));
	//take damage
	dae::InputManager::GetInstance().AddControllerCommand(0, dae::Controller::GamepadButton::X, dae::KeyState::Released,
		std::make_unique<TakeDamage>(redTank.get()));
	//increase score
	dae::InputManager::GetInstance().AddControllerCommand(0, dae::Controller::GamepadButton::A, dae::KeyState::Released,
		std::make_unique<IncreaseScore>(redTank.get()));



	//resets stats and achievments (i know its not the best way to reset the achievments with the stats but its just for showcase)
	dae::InputManager::GetInstance().AddKeyboardCommand(SDL_SCANCODE_R, dae::KeyState::Released,
		std::make_unique<ResetAchievements>(blueTank.get()));

	dae::InputManager::GetInstance().AddControllerCommand(0, dae::Controller::GamepadButton::Start, dae::KeyState::Released,
		std::make_unique<ResetAchievements>(redTank.get()));

	// sounds
	auto soundBindsText= std::make_shared<dae::GameObject>();
	soundBindsText->AddComponent<dae::TextComponent>("SpaceBar to pause music (sound effects on score increase and dmg taken)", fontDescription)->SetColor(SDL_Color(255, 255, 255));;
	soundBindsText->SetPosition(100, 100);
	scene.Add(soundBindsText);

	auto& ss = dae::ServiceLocator::GetSoundSystem();
	ss.LoadSound(1, "../Data/GameMusic.mp3", dae::SoundType::Music);
	ss.LoadSound(2, "../Data/Shoot.mp3", dae::SoundType::SoundEffect);
	ss.LoadSound(3, "../Data/Blip2.mp3", dae::SoundType::SoundEffect);
	ss.Play(1, 0.3f, dae::SoundType::Music);

	// spacebar to pause

	dae::InputManager::GetInstance().AddKeyboardCommand(SDL_SCANCODE_SPACE, dae::KeyState::Released,
		std::make_unique<PauseSounds>());

	

}

void TestScene(dae::Scene& scene)
{
	
	std::unordered_map<std::string, std::vector<glm::vec2>> positions{ };
	auto level = LevelCreator::LoadLevel(scene, "../Data/Levels/Level1.csv", positions, glm::vec2{ 250,150 });
	
	glm::vec2 p1Spawn = { };
	if (positions["P1"].size() > 0)
	{
		p1Spawn = positions["P1"][0];
	}

	glm::vec2 p2Spawn = {  }; 
	if (positions["P2"].size() > 0)
	{
		p2Spawn = positions["P2"][0];
	}

	float tankSpeed = 100.f;
	auto player1 = std::make_unique<dae::PlayerCharacter>(scene, p1Spawn.x, p1Spawn.y, 1);
	auto player2 = std::make_unique<dae::PlayerCharacter>(scene, p2Spawn.x, p2Spawn.y, 2);

	//keyboard input
	//up
	dae::InputManager::GetInstance().AddKeyboardCommand(SDL_SCANCODE_W, dae::KeyState::Down,
		std::make_unique<Move>(player1->GetPlayer().get(), glm::vec2{ 0, -1 }, tankSpeed));
	dae::InputManager::GetInstance().AddKeyboardCommand(SDL_SCANCODE_W, dae::KeyState::Released,
		std::make_unique<StopMove>(player1->GetPlayer().get()));
	//down
	dae::InputManager::GetInstance().AddKeyboardCommand(SDL_SCANCODE_S, dae::KeyState::Down,
		std::make_unique<Move>(player1->GetPlayer().get(), glm::vec2{ 0, 1 }, tankSpeed));
	dae::InputManager::GetInstance().AddKeyboardCommand(SDL_SCANCODE_S, dae::KeyState::Released,
		std::make_unique<StopMove>(player1->GetPlayer().get()));
	//right
	dae::InputManager::GetInstance().AddKeyboardCommand(SDL_SCANCODE_D, dae::KeyState::Down,
		std::make_unique<Move>(player1->GetPlayer().get(), glm::vec2{1, 0}, tankSpeed));
	dae::InputManager::GetInstance().AddKeyboardCommand(SDL_SCANCODE_D, dae::KeyState::Released,
		std::make_unique<StopMove>(player1->GetPlayer().get()));
	//left
	dae::InputManager::GetInstance().AddKeyboardCommand(SDL_SCANCODE_A, dae::KeyState::Down,
		std::make_unique<Move>(player1->GetPlayer().get(), glm::vec2{ -1, 0 }, tankSpeed));
	dae::InputManager::GetInstance().AddKeyboardCommand(SDL_SCANCODE_A, dae::KeyState::Released,
		std::make_unique<StopMove>(player1->GetPlayer().get()));
	// shoot
	dae::InputManager::GetInstance().AddKeyboardCommand(SDL_SCANCODE_SPACE, dae::KeyState::Pressed,
		std::make_unique<Shoot>(player1->GetWeapon().get()));

	//controller
	dae::InputManager::GetInstance().AddController(0);
	//up
	dae::InputManager::GetInstance().AddControllerCommand(0, dae::Controller::GamepadButton::DPadUp, dae::KeyState::Down,
		std::make_unique<Move>(player2->GetPlayer().get(), glm::vec2{ 0, -1 }, tankSpeed));
	dae::InputManager::GetInstance().AddControllerCommand(0, dae::Controller::GamepadButton::DPadUp, dae::KeyState::Released,
		std::make_unique<StopMove>(player2->GetPlayer().get()));
	//down
	dae::InputManager::GetInstance().AddControllerCommand(0, dae::Controller::GamepadButton::DPadDown, dae::KeyState::Down,
		std::make_unique<Move>(player2->GetPlayer().get(), glm::vec2{ 0, 1 }, tankSpeed ));
	dae::InputManager::GetInstance().AddControllerCommand(0, dae::Controller::GamepadButton::DPadDown, dae::KeyState::Released,
		std::make_unique<StopMove>(player2->GetPlayer().get()));
	//right
	dae::InputManager::GetInstance().AddControllerCommand(0, dae::Controller::GamepadButton::DPadRight, dae::KeyState::Down,
		std::make_unique<Move>(player2->GetPlayer().get(), glm::vec2{ 1, 0 }, tankSpeed ));
	dae::InputManager::GetInstance().AddControllerCommand(0, dae::Controller::GamepadButton::DPadRight, dae::KeyState::Released,
		std::make_unique<StopMove>(player2->GetPlayer().get()));
	//left
	dae::InputManager::GetInstance().AddControllerCommand(0, dae::Controller::GamepadButton::DPadLeft, dae::KeyState::Down,
		std::make_unique<Move>(player2->GetPlayer().get(), glm::vec2{ -1, 0 }, tankSpeed ));
	dae::InputManager::GetInstance().AddControllerCommand(0, dae::Controller::GamepadButton::DPadLeft, dae::KeyState::Released,
		std::make_unique<StopMove>(player2->GetPlayer().get()));
	// shoot
	dae::InputManager::GetInstance().AddControllerCommand(0, dae::Controller::GamepadButton::A, dae::KeyState::Pressed,
		std::make_unique<Shoot>(player2->GetWeapon().get()));
}

void StartMenu(dae::Scene& scene)
{
	auto tronLogo = std::make_shared<dae::GameObject>();
	auto texture = tronLogo->AddComponent<dae::RenderComponent>();
	texture->SetTexture("tron_marquee.jpg");
	texture->SetScale(0.40f);
	tronLogo->SetPosition(320.f - (texture->GetSize().x / 2), 0.f);
	scene.Add(tronLogo);

	
	auto font = dae::ResourceManager::GetInstance().LoadFont("tronFont/tron.ttf", 20);
	auto button = std::make_shared<dae::GameObject>();
	auto buttonText = button->AddComponent<dae::TextComponent>("Single Player",font);
	buttonText->SetBold(true);
	buttonText->SetColor(SDL_Color(150, 0, 255));
	button->SetPosition(320.f - (buttonText->GetSize().x/2), 310.f);
	scene.Add(button);
}
