#include "LoggingSoundSystem.h"
#include <iostream>

dae::LoggingSoundSystem::LoggingSoundSystem(std::unique_ptr<SoundSystem>&& ss)
	: _real_ss(std::move(ss))
{
	std::cout << "LoggingSoundSystem created" << std::endl;
}

void dae::LoggingSoundSystem::Play(const sound_id id, const float volume)
{
	_real_ss->Play(id, volume);
	std::cout << "Playing " << id << " at volume " << volume << std::endl;
}

void dae::LoggingSoundSystem::PauseSound()
{
	_real_ss->PauseSound();
	std::cout << "Paused sound" << std::endl;
}

void dae::LoggingSoundSystem::UnpauseSound()
{
	_real_ss->UnpauseSound();
	std::cout << "Unpaused sound" << std::endl;
}
