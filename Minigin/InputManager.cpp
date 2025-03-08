#include <SDL.h>
#include "InputManager.h"
#include <backends/imgui_impl_sdl2.h>

bool dae::InputManager::ProcessInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		//if (e.type == SDL_KEYDOWN) {
		//	
		//}
		//if (e.type == SDL_MOUSEBUTTONDOWN) {
		//	
		//}
		// etc...

		//process event forImgui
		ImGui_ImplSDL2_ProcessEvent(&e);
	}
	UpdateKeyboardInput();

	return true;
}

void dae::InputManager::AddKeyboardCommand(const SDL_Scancode key, const KeyState state, std::unique_ptr<Command> command)
{
    KeyboardKey keyPair = std::pair(key, state);
	m_KeyboardCommands.emplace(keyPair, std::move(command));
}

void dae::InputManager::RemoveKeyboardCommand(const SDL_Scancode key, const KeyState state)
{
	KeyboardKey keyPair = std::pair(key, state);
	m_KeyboardCommands.erase(keyPair);
}

void dae::InputManager::UpdateKeyboardInput()
{
    m_Keyboard->Update();

    for (auto& [key, command] : m_KeyboardCommands)
    {
        SDL_Scancode scancode = key.first;

        switch (key.second)
        {
        case KeyState::Pressed:
            if (m_Keyboard->IsDownThisFrame(scancode)) 
                command->Execute();
            break;

        case KeyState::Released:
            if (m_Keyboard->IsUpThisFrame(scancode))
                command->Execute();
            break;

        case KeyState::Down:
            if (m_Keyboard->IsPressed(scancode))
                command->Execute();
            break;
        }
    }

}
