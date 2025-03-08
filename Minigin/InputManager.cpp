#include <SDL.h>
#include "InputManager.h"
#include <backends/imgui_impl_sdl2.h>


bool dae::InputManager::ProcessInput(float deltaTime)
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
	UpdateKeyboardInput(deltaTime);
    UpdateControllerInput(deltaTime);

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

void dae::InputManager::UpdateKeyboardInput(float deltaTime)
{
    m_Keyboard->Update();

    for (auto& [key, command] : m_KeyboardCommands)
    {
        SDL_Scancode scancode = key.first;

        switch (key.second)
        {
        case KeyState::Pressed:
            if (m_Keyboard->IsDownThisFrame(scancode)) 
                command->Execute(deltaTime);
            break;

        case KeyState::Released:
            if (m_Keyboard->IsUpThisFrame(scancode))
                command->Execute(deltaTime);
            break;

        case KeyState::Down:
            if (m_Keyboard->IsPressed(scancode))
                command->Execute(deltaTime);
            break;
        }
    }

}



void dae::InputManager::AddController(int controllerIdx)
{
    // Check if controller already exists
    for (const auto& controller : m_Controllers)
    {
        if (controller->GetIndex() == controllerIdx) 
        {
            std::cout << "Controller " << controllerIdx << " is already added.\n";
            return;
        }
    }

    // Add new controller
    m_Controllers.push_back(std::make_unique<Controller>(controllerIdx));
    std::cout << "Controller " << controllerIdx << " added.\n";
}

void dae::InputManager::RemoveController(int controllerIdx)
{
    // Remove controller by index
    m_Controllers.erase(
        std::remove_if(m_Controllers.begin(), m_Controllers.end(),
            [controllerIdx](const std::unique_ptr<Controller>& controller)
            {
                return controller->GetIndex() == controllerIdx;
            }),
        m_Controllers.end()
    );

    std::cout << "Controller " << controllerIdx << " removed.\n";
}

//void dae::InputManager::DetectAndAddControllers()
//{
//    for (int i = 0; i < 4; ++i) // XInput supports up to 4 controllers
//    {
//        XINPUT_STATE state;
//        ZeroMemory(&state, sizeof(XINPUT_STATE));
//
//        if (XInputGetState(i, &state) == ERROR_SUCCESS) // Controller is connected
//        {
//            AddController(i); // Add the controller to InputManager
//        }
//        else
//        {
//            RemoveController(i); // Optionally remove the controller if it's disconnected
//        }
//    }
//}

void dae::InputManager::AddControllerCommand(int controllerIdx,Controller::GamepadButton button, const KeyState state, std::unique_ptr<Command> command)
{
    ControllerKey keyTuple = std::tuple(controllerIdx, button, state);
    m_ControllerCommands[keyTuple] = std::move(command);
}

void dae::InputManager::RemoveControllerCommand(int controllerIdx,Controller::GamepadButton button, const KeyState state)
{
    ControllerKey keyTuple = std::tuple(controllerIdx, button, state);
    m_ControllerCommands.erase(keyTuple);
}

void dae::InputManager::UpdateControllerInput(float deltaTime)
{
    for (auto& controller : m_Controllers)
    {
        controller->Update();
        int controllerIdx = controller->GetIndex(); // Get the controller index

        for (auto& [key, command] : m_ControllerCommands)
        {
            int assignedControllerIdx;
            Controller::GamepadButton button;
            KeyState state;
            std::tie(assignedControllerIdx, button, state) = key; // Extract values

            if (controllerIdx == assignedControllerIdx) // Ensure the correct controller executes the command
            {
                switch (state)
                {
                case KeyState::Pressed:
                    if (controller->IsDownThisFrame(button))
                        command->Execute(deltaTime);
                    break;
                case KeyState::Down:
                    if (controller->IsPressed(button))
                        command->Execute(deltaTime);
                    break;
                case KeyState::Released:
                    if (controller->IsUpThisFrame(button))
                        command->Execute(deltaTime);
                    break;
                }
            }
        }
        
    }
}
