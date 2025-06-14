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
#include "EnemyCharacter.h"
#include "EnemyComponent.h"
#include "GameMode.h"
#include "TextButtonComponent.h"


void VersusMode(dae::Scene& scene);
void SinglePlayerMode(dae::Scene& scene);
void StartMenu(dae::Scene& scene);
void SetupInputBindings();

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
	auto& StartScreenScene = dae::SceneManager::GetInstance().CreateScene("StartScreen");
	auto& VersusModeScene = dae::SceneManager::GetInstance().CreateScene("VersusMode");
	auto& SinglePlayerModeScene = dae::SceneManager::GetInstance().CreateScene("SinglePlayer");


#if _DEBUG
	dae::ServiceLocator::RegisterSoundSystem(
		std::make_unique<dae::LoggingSoundSystem>(std::make_unique<dae::SDLSoundSystem>()));
#else
	dae::ServiceLocator::RegisterSoundSystem(std::make_unique<dae::SDLSoundSystem>());
#endif

	StartMenu(StartScreenScene);
	VersusMode(VersusModeScene);
	SinglePlayerMode(SinglePlayerModeScene);
	dae::SceneManager::GetInstance().SetScene(StartScreenScene);
	
}
int main(int, char* []) 
{
	std::string dataPath = FindDataFolder();
	std::cout << "Found Data Path: " << dataPath << std::endl;
	dae::Minigin engine(dataPath);
	engine.Run(load);
	return 0;
}

void VersusMode(dae::Scene& scene)
{
	
	std::unordered_map<std::string, std::vector<glm::vec2>> positions{ };
	std::vector<glm::vec2> nodPos{};
	auto level = LevelCreator::LoadLevel(scene, "../Data/Levels/Level2.csv", positions, nodPos, glm::vec2{ 250,140 });
	
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

	if (positions["Enemy"].size() > 0)
	{
		for (const auto& enemyPos : positions["Enemy"])
		{
			auto enemy = std::make_unique<EnemyCharacter>(scene, enemyPos.x, enemyPos.y);
			enemy->SetTarget(player1->GetPlayer());
			enemy->GetEnemy()->GetComponent<EnemyComponent>()->SetNavigationNodes(nodPos);
		}
	}

	

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

	auto& ss = dae::ServiceLocator::GetSoundSystem();
	ss.LoadSound(1, "../Data/GameMusic.mp3", dae::SoundType::Music);
	ss.LoadSound(2, "../Data/Shoot.mp3", dae::SoundType::SoundEffect);
	ss.LoadSound(3, "../Data/Blip2.mp3", dae::SoundType::SoundEffect);
	ss.Play(1, 0.1f, dae::SoundType::Music);
}

void SinglePlayerMode(dae::Scene& scene)
{

	std::unordered_map<std::string, std::vector<glm::vec2>> positions{ };
	std::vector<glm::vec2> nodPos{};
	auto level = LevelCreator::LoadLevel(scene, "../Data/Levels/Level1.csv", positions, nodPos, glm::vec2{ 250,140 });

	glm::vec2 p1Spawn = { };
	if (positions["P1"].size() > 0)
	{
		p1Spawn = positions["P1"][0];
	}



	float tankSpeed = 100.f;
	auto player1 = std::make_unique<dae::PlayerCharacter>(scene, p1Spawn.x, p1Spawn.y, 1);
	

	if (positions["Enemy"].size() > 0)
	{
		for (const auto& enemyPos : positions["Enemy"])
		{
			auto enemy = std::make_unique<EnemyCharacter>(scene, enemyPos.x, enemyPos.y);
			enemy->SetTarget(player1->GetPlayer());
			enemy->GetEnemy()->GetComponent<EnemyComponent>()->SetNavigationNodes(nodPos);
		}
	}



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
		std::make_unique<Move>(player1->GetPlayer().get(), glm::vec2{ 1, 0 }, tankSpeed));
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


	auto& ss = dae::ServiceLocator::GetSoundSystem();
	ss.LoadSound(1, "../Data/GameMusic.mp3", dae::SoundType::Music);
	ss.LoadSound(2, "../Data/Shoot.mp3", dae::SoundType::SoundEffect);
	ss.LoadSound(3, "../Data/Blip2.mp3", dae::SoundType::SoundEffect);
	ss.Play(1, 0.1f, dae::SoundType::Music);
}

void StartMenu(dae::Scene& scene)
{
	auto tronLogo = std::make_shared<dae::GameObject>();
	auto texture = tronLogo->AddComponent<dae::RenderComponent>();
	texture->SetTexture("tron_marquee.jpg");
	texture->SetScale(0.80f);
	tronLogo->SetPosition(550.f - (texture->GetSize().x / 2), 0.f);
	scene.Add(tronLogo);

	std::vector<std::string> menuOptions{ "Versus","Single Player" };
	auto font = dae::ResourceManager::GetInstance().LoadFont("tronFont/tron.ttf", 40);
	auto button = std::make_shared<dae::GameObject>();
	auto buttonText = button->AddComponent<dae::TextComponent>("Versus",font);
	buttonText->SetBold(true);
	buttonText->SetColor(SDL_Color(150, 0, 255));
	button->SetPosition(550.f - (buttonText->GetSize().x/2), 400.f);
	button->AddComponent<TextButtonComponent>(menuOptions);
	scene.Add(button);

	dae::InputManager::GetInstance().AddKeyboardCommand(SDL_SCANCODE_LEFT, dae::KeyState::Pressed,
		std::make_unique<ScreenMoveLeft>(button.get()));
	dae::InputManager::GetInstance().AddKeyboardCommand(SDL_SCANCODE_RIGHT, dae::KeyState::Pressed,
		std::make_unique<ScreenMoveRight>(button.get()));
	dae::InputManager::GetInstance().AddKeyboardCommand(SDL_SCANCODE_RETURN, dae::KeyState::Pressed,
		std::make_unique<ScreenSelect>(button.get()));
}


