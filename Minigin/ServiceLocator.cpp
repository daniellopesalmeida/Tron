#include "ServiceLocator.h"

std::unique_ptr<dae::SoundSystem> dae::ServiceLocator::_ss_instance{ std::make_unique<NullSoundSystem>() };