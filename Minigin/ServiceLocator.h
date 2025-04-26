#pragma once
#include <memory>
#include "SoundSystem.h"
#include "NullSoundSystem.h"

namespace dae
{
	class ServiceLocator final
	{
		static std::unique_ptr<SoundSystem> _ss_instance;
	public:
		static SoundSystem& GetSoundSystem() { return *_ss_instance; }
		static void RegisterSoundSystem(std::unique_ptr<SoundSystem>&& ss) 
		{
			_ss_instance = ss == nullptr ? std::make_unique<NullSoundSystem>() : std::move(ss);
		};
	};
}

