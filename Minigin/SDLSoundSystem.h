#pragma once  
#include "SoundSystem.h"  
#include <unordered_map>  
#include <SDL_mixer.h>  //? 
#include <string>
#include <queue>
#include <mutex>

namespace dae  
{  
	struct SoundData
	{
		sound_id id;
		float volume;
		SoundType type;
	};

class SDLSoundSystem final: public SoundSystem  
{  
public:  
	SDLSoundSystem();  
	~SDLSoundSystem() override;
	SDLSoundSystem(const SDLSoundSystem&) = delete;  
	SDLSoundSystem(SDLSoundSystem&&) = delete;  
	SDLSoundSystem& operator= (const SDLSoundSystem&) = delete;  
	SDLSoundSystem& operator= (const SDLSoundSystem&&) = delete;  

	void Play(const sound_id id, const float volume, SoundType type) override;  
	void PauseSound() override;  
	void UnpauseSound() override;  

	void LoadSound(const sound_id id, const std::string& path, SoundType type);

private:
	std::unique_ptr<class SDLSoundSystemImpl> m_pImpl;
	//void SoundThread();
	//
	//std::unordered_map<sound_id, Mix_Chunk*> m_SoundEffects;
	//std::unordered_map<sound_id, Mix_Music*> m_MusicTracks;
	//
	//std::queue<SoundData> m_EventQueue;
	//std::mutex m_QueueMutex;
	//std::condition_variable m_Condition;
	//std::atomic<bool> m_Running;
	//std::thread m_SoundWorker;
};  
}
