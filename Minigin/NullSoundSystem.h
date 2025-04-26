#pragma once
#include "SoundSystem.h"

namespace dae
{
	class NullSoundSystem final: public SoundSystem
	{
	public:
		NullSoundSystem() = default;
		~NullSoundSystem() = default;
		NullSoundSystem(const NullSoundSystem&) = delete;
		NullSoundSystem(NullSoundSystem&&) = delete;
		NullSoundSystem& operator= (const NullSoundSystem&) = delete;
		NullSoundSystem& operator= (const NullSoundSystem&&) = delete;

		void Play(const sound_id id, const float volume, SoundType type) override;
		void PauseSound() override;
		void UnpauseSound() override;
		void LoadSound(const sound_id id, const std::string& filepath, SoundType type);
	};
}

