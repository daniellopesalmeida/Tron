#include "LoggingSoundSystem.h"
#include <iostream>

dae::LoggingSoundSystem::LoggingSoundSystem(std::unique_ptr<SoundSystem>&& ss)
	: _real_ss(std::move(ss))
{
	std::cout << "LoggingSoundSystem created" << std::endl;
}

void dae::LoggingSoundSystem::Play(const sound_id id, const float volume, SoundType type)
{
	_real_ss->Play(id, volume,type);
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

void dae::LoggingSoundSystem::LoadSound(const sound_id id, const std::string& filepath, SoundType type)
{
	_real_ss->LoadSound(id, filepath, type);
	std::cout << "Loading sound id: " << id << " from file: " << filepath << std::endl;
}
