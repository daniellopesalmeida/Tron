#pragma once

namespace dae 
{
	using sound_id = unsigned short;
	class SoundSystem
	{
	public:
		virtual ~SoundSystem() = default;
		virtual void Play(const sound_id id, const float volume) = 0;
		virtual void PauseSound() = 0;
		virtual void UnpauseSound() = 0;
	};
}

