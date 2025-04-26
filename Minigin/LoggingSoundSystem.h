#pragma once
#include "SoundSystem.h"
#include <memory>

namespace dae
{
	class LoggingSoundSystem final: public SoundSystem
	{
		
	public:
		LoggingSoundSystem(std::unique_ptr<SoundSystem>&& ss);
		virtual ~LoggingSoundSystem() = default;

		void Play(const sound_id id, const float volume) override;
		void PauseSound() override;
		void UnpauseSound() override;

	private: 
		std::unique_ptr<SoundSystem> _real_ss;
	};
}

