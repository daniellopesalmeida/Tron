#pragma once
#include "SoundSystem.h"

namespace dae
{
	class NullSoundSystem final: public SoundSystem
	{
	public:
		NullSoundSystem() = default;
		~NullSoundSystem() = default;

		void Play(const sound_id id, const float volume) override;
		void PauseSound() override;
		void UnpauseSound() override;
	};
}

