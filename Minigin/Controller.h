#pragma once
//#include <Xinput.h>
#include <memory>
#include <glm.hpp>

namespace dae
{
	class Controller
	{
	public:
    
        enum class GamepadButton
        {
            A = 0x1000,               // XINPUT_GAMEPAD_A
            B = 0x2000,               // XINPUT_GAMEPAD_B
            X = 0x4000,               // XINPUT_GAMEPAD_X
            Y = 0x8000,               // XINPUT_GAMEPAD_Y
            DPadUp = 0x0001,          // XINPUT_GAMEPAD_DPAD_UP
            DPadDown = 0x0002,        // XINPUT_GAMEPAD_DPAD_DOWN
            DPadLeft = 0x0004,        // XINPUT_GAMEPAD_DPAD_LEFT
            DPadRight = 0x0008,       // XINPUT_GAMEPAD_DPAD_RIGHT
            LeftShoulder = 0x0100,    // XINPUT_GAMEPAD_LEFT_SHOULDER
            RightShoulder = 0x0200,   // XINPUT_GAMEPAD_RIGHT_SHOULDER
            Start = 0x0010,           // XINPUT_GAMEPAD_START
            Back = 0x0020,            // XINPUT_GAMEPAD_BACK
            LeftThumb = 0x0040,       // XINPUT_GAMEPAD_LEFT_THUMB
            RightThumb = 0x0080,      // XINPUT_GAMEPAD_RIGHT_THUMB

        };
    
        Controller(int controllerIdx);
        ~Controller();
        
        void Update();
        
        bool IsDownThisFrame(GamepadButton button);
        bool IsUpThisFrame(GamepadButton button);
        bool IsPressed(GamepadButton button);
        glm::vec2 GetLeftStick() const;
        glm::vec2 GetRightStick() const;

        int GetIndex() const { return m_ControllerIdx; }
    
    
    private:
        class ControllerImpl;
        ControllerImpl* m_pImpl;
        int m_ControllerIdx;
	};
}
