#pragma once
#include <string>

namespace dae 
{
	enum class SoundType
	{
		SoundEffect,
		Music
	};
	using sound_id = unsigned short;
	class SoundSystem
	{
	public:
		virtual ~SoundSystem() = default;
		virtual void Play(const sound_id id, const float volume, SoundType type) = 0;
		virtual void PauseSound() = 0;
		virtual void UnpauseSound() = 0;
		virtual void LoadSound(const sound_id id, const std::string& filepath, SoundType type) = 0;
	};
}

