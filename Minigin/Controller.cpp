#include <windows.h>
#include <Xinput.h>
#include "Controller.h"
#include <iostream>



class dae::Controller::ControllerImpl
{
public:
    ControllerImpl(int controllerIdx)
        : m_ControllerIdx(controllerIdx), m_WasConnected(false)
    {
        ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
        ZeroMemory(&m_PreviousState, sizeof(XINPUT_STATE));
    }

    void Update()
    {
        CopyMemory(&m_PreviousState, &m_CurrentState, sizeof(XINPUT_STATE));
        ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
        
        DWORD result = XInputGetState(m_ControllerIdx, &m_CurrentState);
        if (result != ERROR_SUCCESS)
        {
            // If the controller is not connected
            if (m_WasConnected)
            {
                std::cout << "Controller " << m_ControllerIdx  << " disconnected." << std::endl;
                m_WasConnected = false; 
            }
            return;
        }
        // If the controller is connected
        if (!m_WasConnected)
        {
            std::cout << "Controller " << m_ControllerIdx  << " connected." << std::endl;
            m_WasConnected = true;
        }
    }

    bool IsDownThisFrame(GamepadButton button)
    {
        return (m_CurrentState.Gamepad.wButtons & static_cast<WORD>(button)) &&
            !(m_PreviousState.Gamepad.wButtons & static_cast<WORD>(button));
    }

    bool IsUpThisFrame(GamepadButton button)
    {
        return !(m_CurrentState.Gamepad.wButtons & static_cast<WORD>(button)) &&
            (m_PreviousState.Gamepad.wButtons & static_cast<WORD>(button));
    }

    bool IsPressed(GamepadButton button)
    {
        return m_CurrentState.Gamepad.wButtons & static_cast<WORD>(button);
    }

    glm::vec2 GetLeftStick() const
    {
        XINPUT_STATE state;
        ZeroMemory(&state, sizeof(XINPUT_STATE));

        if (XInputGetState(m_ControllerIdx, &state) == ERROR_SUCCESS)
        {
            float normLX = fmaxf(-1.0f, (float)state.Gamepad.sThumbLX / 32767.0f);
            float normLY = fmaxf(-1.0f, (float)state.Gamepad.sThumbLY / 32767.0f);

            // Apply Deadzone
            float deadzone = 0.2f;
            glm::vec2 leftStick = {
                (fabs(normLX) < deadzone) ? 0.0f : normLX,
                (fabs(normLY) < deadzone) ? 0.0f : normLY
            };

            return leftStick;
        }
        return glm::vec2(0, 0);
    }

    glm::vec2 GetRightStick() const
    {
        XINPUT_STATE state;
        ZeroMemory(&state, sizeof(XINPUT_STATE));

        if (XInputGetState(m_ControllerIdx, &state) == ERROR_SUCCESS)
        {
            float normRX = fmaxf(-1.0f, (float)state.Gamepad.sThumbRX / 32767.0f);
            float normRY = fmaxf(-1.0f, (float)state.Gamepad.sThumbRY / 32767.0f);

            // Apply Deadzone
            float deadzone = 0.2f;
            glm::vec2 rightStick = {
                (fabs(normRX) < deadzone) ? 0.0f : normRX,
                (fabs(normRY) < deadzone) ? 0.0f : normRY
            };

            return rightStick;
        }
        return glm::vec2(0, 0);
    }

   

private:
    int m_ControllerIdx;  //(0, 1, 2, 3 for up to 4 controllers)
    bool m_WasConnected;  //connection state of the controller
    XINPUT_STATE m_CurrentState{};
    XINPUT_STATE m_PreviousState{}; 
};

dae::Controller::Controller(int controllerIdx):m_ControllerIdx{controllerIdx}
{
    m_pImpl = new ControllerImpl(controllerIdx);
}

dae::Controller::~Controller()
{
    delete m_pImpl;
}

void dae::Controller::Update()
{
    m_pImpl->Update();
}

bool dae::Controller::IsDownThisFrame(GamepadButton button)
{
	return m_pImpl->IsDownThisFrame(button);
}

bool dae::Controller::IsUpThisFrame(GamepadButton button)
{
	return m_pImpl->IsUpThisFrame(button);
}

bool dae::Controller::IsPressed(GamepadButton button)
{
	return m_pImpl->IsPressed(button);
}

glm::vec2 dae::Controller::GetLeftStick() const
{
    return m_pImpl->GetLeftStick();
}

glm::vec2 dae::Controller::GetRightStick() const
{
    return m_pImpl->GetRightStick();
}
