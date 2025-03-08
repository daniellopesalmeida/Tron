#include "Keyboard.h"

dae::Keyboard::Keyboard() :m_CurrentState(SDL_NUM_SCANCODES), m_PreviousState(SDL_NUM_SCANCODES)

{
	for (int i = 0; i < SDL_NUM_SCANCODES; ++i)
	{
		m_CurrentState[i] = 0;
		m_PreviousState[i] = 0;
	}
}

void dae::Keyboard::Update()
{
	SDL_PumpEvents();
	m_PreviousState = m_CurrentState;

	int size{};
	const Uint8* state = SDL_GetKeyboardState(&size);

	for (int i = 0; i < size; ++i)
	{
		m_CurrentState[i] = state[i];
	}
}

bool dae::Keyboard::IsDownThisFrame(SDL_Scancode key)
{
	return m_CurrentState[key] && !m_PreviousState[key];
}

bool dae::Keyboard::IsUpThisFrame(SDL_Scancode key)
{
	return !m_CurrentState[key] && m_PreviousState[key];
}

bool dae::Keyboard::IsPressed(SDL_Scancode key)
{
	return m_CurrentState[key];
}
