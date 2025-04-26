#pragma once
#include "SoundSystem.h"
#include <memory>

namespace dae
{
	class LoggingSoundSystem final: public SoundSystem
	{
		
	public:
		LoggingSoundSystem(std::unique_ptr<SoundSystem>&& ss);
		~LoggingSoundSystem() = default;
		LoggingSoundSystem(const LoggingSoundSystem&) = delete;
		LoggingSoundSystem(LoggingSoundSystem&&) = delete;
		LoggingSoundSystem& operator= (const LoggingSoundSystem&) = delete;
		LoggingSoundSystem& operator= (const LoggingSoundSystem&&) = delete;


		void Play(const sound_id id, const float volume, SoundType type) override;
		void PauseSound() override;
		void UnpauseSound() override;
		void LoadSound(const sound_id id, const std::string& filepath, SoundType type);

	private: 
		std::unique_ptr<SoundSystem> _real_ss;
	};
}

