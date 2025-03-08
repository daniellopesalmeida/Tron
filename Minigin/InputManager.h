#pragma once
#include "Singleton.h"
#include <memory>
#include "Command.h"
#include "Keyboard.h" 
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

		bool ProcessInput();

		void AddKeyboardCommand(const SDL_Scancode key, const KeyState state, std::unique_ptr<Command> command);
		void RemoveKeyboardCommand(const SDL_Scancode key, const KeyState state);

		void UpdateKeyboardInput();

	private:
		std::unique_ptr<Keyboard> m_Keyboard{ std::make_unique<Keyboard>() };

		using KeyboardKey = std::pair<SDL_Scancode, KeyState>;
		using KeyboardCommandsMap = std::map<KeyboardKey, std::unique_ptr<Command>>;

		KeyboardCommandsMap m_KeyboardCommands;
		
	};

}
