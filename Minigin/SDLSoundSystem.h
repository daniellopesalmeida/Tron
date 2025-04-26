#pragma once
#include "SoundSystem.h"

namespace dae
{
	class SDLSoundSystem final: public SoundSystem
	{
		SDLSoundSystem();
		~SDLSoundSystem() = default;

		void Play(const sound_id id, const float volume);
		void PauseSound();
		void UnpauseSound();
	};
}

