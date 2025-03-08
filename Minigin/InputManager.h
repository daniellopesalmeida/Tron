#pragma once
#include "Singleton.h"
#include <memory>
#include "Command.h"
#include "Keyboard.h" 
#include "Controller.h"
#include <map>

namespace dae
{
	enum class KeyState
	{
		Pressed,
		Down,
		Released
	};


	class InputManager final : public Singleton<InputManager>
	{
	public:

		bool ProcessInput(float deltaTime);
		//keyboard
		void AddKeyboardCommand(const SDL_Scancode key, const KeyState state, std::unique_ptr<Command> command);
		void RemoveKeyboardCommand(const SDL_Scancode key, const KeyState state);
		void UpdateKeyboardInput(float deltaTime);

		//controller
		void AddController(int controllerIdx);
		void RemoveController(int controllerIdx);
		//void DetectAndAddControllers();
		void AddControllerCommand(int controllerIdx,Controller::GamepadButton button, const KeyState state, std::unique_ptr<Command> command);
		void RemoveControllerCommand(int controllerIdx,Controller::GamepadButton button, const KeyState state);
		void UpdateControllerInput(float deltaTime);

	private:
		//keyboard
		std::unique_ptr<Keyboard> m_Keyboard{ std::make_unique<Keyboard>() };

		using KeyboardKey = std::pair<SDL_Scancode, KeyState>;
		using KeyboardCommandsMap = std::map<KeyboardKey, std::unique_ptr<Command>>;

		KeyboardCommandsMap m_KeyboardCommands;

		//controller
		std::vector<std::unique_ptr<Controller>> m_Controllers;
		
		using ControllerKey = std::tuple<int, Controller::GamepadButton, KeyState>;
		using ControllerCommandsMap = std::map<ControllerKey, std::unique_ptr<Command>>;
		
		std::map<ControllerKey, std::unique_ptr<Command>> m_ControllerCommands;
		
	};

}
