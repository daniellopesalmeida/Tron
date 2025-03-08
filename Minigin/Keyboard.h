#pragma once
#include <SDL.h>
#include <vector>
#include <iostream>

namespace dae
{

	class Keyboard
	{
	public:
		Keyboard();
		~Keyboard()=default;

		void Update();

		bool IsDownThisFrame(SDL_Scancode key);
		bool IsUpThisFrame(SDL_Scancode key);
		bool IsPressed(SDL_Scancode key);

	private: 

		std::vector<Uint8> m_CurrentState{};
		std::vector<Uint8> m_PreviousState{};
		
	};
}

