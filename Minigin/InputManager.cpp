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

    // Prioritized directional keys
    std::vector<std::pair<SDL_Scancode, KeyState>> priorityKeys = {
        {SDL_SCANCODE_W, KeyState::Down},
        {SDL_SCANCODE_S, KeyState::Down},
        {SDL_SCANCODE_A, KeyState::Down},
        {SDL_SCANCODE_D, KeyState::Down}
    };

    // Check prioritized keys first
    for (const auto& keyPair : priorityKeys)
    {
        auto it = m_KeyboardCommands.find(keyPair);
        if (it != m_KeyboardCommands.end())
        {
            const auto& [key, state] = keyPair;
            if ((state == KeyState::Pressed && m_Keyboard->IsDownThisFrame(key)) ||
                (state == KeyState::Released && m_Keyboard->IsUpThisFrame(key)) ||
                (state == KeyState::Down && m_Keyboard->IsPressed(key)))
            {
                it->second->Execute(deltaTime);
                break; 
            }
        }
    }

    // Process non-directional keys (like space, enter, etc.)
    for (auto& [key, command] : m_KeyboardCommands)
    {
        // Skip directional keys since we already handled them
        if (key == std::make_pair(SDL_SCANCODE_W, KeyState::Down) ||
            key == std::make_pair(SDL_SCANCODE_S, KeyState::Down) ||
            key == std::make_pair(SDL_SCANCODE_A, KeyState::Down) ||
            key == std::make_pair(SDL_SCANCODE_D, KeyState::Down))
            continue;

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
    for (const auto& controller : m_Controllers)
    {
        if (controller->GetIndex() == controllerIdx) 
        {
            std::cout << "Controller " << controllerIdx << " is already assigned.\n";
            return;
        }
    }

    m_Controllers.push_back(std::make_unique<Controller>(controllerIdx));
    std::cout << "Controller " << controllerIdx << " assigned.\n";
}

void dae::InputManager::RemoveController(int controllerIdx)
{
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
//    for (int i = 0; i < 4; ++i) 
//    {
//        XINPUT_STATE state;
//        ZeroMemory(&state, sizeof(XINPUT_STATE));
//
//        if (XInputGetState(i, &state) == ERROR_SUCCESS) 
//        {
//            AddController(i); 
//        }
//        else
//        {
//            RemoveController(i);
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
        int controllerIdx = controller->GetIndex();

        // Directional input handling for all key states (Pressed, Released, Down)
        std::vector<Controller::GamepadButton> directionalButtons = {
            Controller::GamepadButton::DPadUp,
            Controller::GamepadButton::DPadDown,
            Controller::GamepadButton::DPadLeft,
            Controller::GamepadButton::DPadRight
        };

        for (auto button : directionalButtons)
        {
            std::tuple<int, Controller::GamepadButton, KeyState> pressedKey = { controllerIdx, button, KeyState::Pressed };
            std::tuple<int, Controller::GamepadButton, KeyState> releasedKey = { controllerIdx, button, KeyState::Released };
            std::tuple<int, Controller::GamepadButton, KeyState> downKey = { controllerIdx, button, KeyState::Down };

            if (m_ControllerCommands.contains(pressedKey) && controller->IsDownThisFrame(button))
            {
                m_ControllerCommands[pressedKey]->Execute(deltaTime);
                break;
            }
            if (m_ControllerCommands.contains(releasedKey) && controller->IsUpThisFrame(button))
            {
                m_ControllerCommands[releasedKey]->Execute(deltaTime);
                break;
            }
            if (m_ControllerCommands.contains(downKey) && controller->IsPressed(button))
            {
                m_ControllerCommands[downKey]->Execute(deltaTime);
                break;
            }
        }

        // Handle all other buttons (non-directional)
        for (auto& [key, command] : m_ControllerCommands)
        {
            int assignedControllerIdx;
            Controller::GamepadButton button;
            KeyState state;
            std::tie(assignedControllerIdx, button, state) = key;

            // Skip if this controller doesn't match
            if (controllerIdx != assignedControllerIdx)
                continue;

            // Skip directional buttons here (already processed above)
            if (button == Controller::GamepadButton::DPadUp ||
                button == Controller::GamepadButton::DPadDown ||
                button == Controller::GamepadButton::DPadLeft ||
                button == Controller::GamepadButton::DPadRight)
                continue;

            switch (state)
            {
            case KeyState::Pressed:
                if (controller->IsDownThisFrame(button))
                    command->Execute(deltaTime);
                break;

            case KeyState::Released:
                if (controller->IsUpThisFrame(button))
                    command->Execute(deltaTime);
                break;

            case KeyState::Down:
                if (controller->IsPressed(button))
                    command->Execute(deltaTime);
                break;
            }
        }
    }
}

void dae::InputManager::ClearInputs()
{
    m_ControllerCommands.clear();
    m_KeyboardCommands.clear();
    m_Controllers.clear();
}
