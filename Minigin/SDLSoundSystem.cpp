#include "SDLSoundSystem.h"
#include <iostream>

dae::SDLSoundSystem::SDLSoundSystem() : m_Running(true), m_SoundWorker(&SDLSoundSystem::SoundThread, this)
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		std::cerr << "Mix_OpenAudio failed: " << Mix_GetError() << '\n';
	}
	else
		std::cout << "SDLSoundSystem created" << std::endl;
}

dae::SDLSoundSystem::~SDLSoundSystem()
{
	m_Running = false;
	m_Condition.notify_all();
	if (m_SoundWorker.joinable())
		m_SoundWorker.join();

	for (auto& [id, chunk] : m_SoundEffects)
		Mix_FreeChunk(chunk);
	for (auto& [id, music] : m_MusicTracks)
		Mix_FreeMusic(music);

	Mix_CloseAudio();
}

void dae::SDLSoundSystem::Play(const sound_id id , const float volume, SoundType type )
{
	{
		std::lock_guard lock(m_QueueMutex);
		m_EventQueue.push({ id, volume, type });
	}
	m_Condition.notify_one();
}

void dae::SDLSoundSystem::PauseSound()
{
	Mix_Pause(-1);
	Mix_PauseMusic();
}

void dae::SDLSoundSystem::UnpauseSound()
{
	Mix_Resume(-1);
	Mix_ResumeMusic();
}

void dae::SDLSoundSystem::LoadSound(const sound_id id, const std::string& path, SoundType type)
{
	if (type == SoundType::SoundEffect)
	{
		if (m_SoundEffects.contains(id)) return;

		Mix_Chunk* chunk = Mix_LoadWAV(path.c_str());
		if (!chunk)
		{
			std::cerr << "Failed to load effect: " << path << " - " << Mix_GetError() << '\n';
			return;
		}
		m_SoundEffects[id] = chunk;
	}
	else if (type == SoundType::Music)
	{
		if (m_MusicTracks.contains(id)) return;

		Mix_Music* music = Mix_LoadMUS(path.c_str());
		if (!music)
		{
			std::cerr << "Failed to load music: " << path << " - " << Mix_GetError() << '\n';
			return;
		}
		m_MusicTracks[id] = music;
	}
}

void dae::SDLSoundSystem::SoundThread()
{
	while (m_Running)
	{
		SoundData cmd;

		{
			std::unique_lock lock(m_QueueMutex);
			m_Condition.wait(lock, [this] { return !m_EventQueue.empty() || !m_Running; });

			if (!m_Running)
				break;

			cmd = m_EventQueue.front();
			m_EventQueue.pop();
		}

		if (cmd.type == SoundType::SoundEffect)
		{
			auto it = m_SoundEffects.find(cmd.id);
			if (it != m_SoundEffects.end())
			{
				int channel = Mix_PlayChannel(-1, it->second, 0);
				if (channel != -1)
					Mix_Volume(channel, static_cast<int>(cmd.volume * MIX_MAX_VOLUME));
			}
		}
		else if (cmd.type == SoundType::Music)
		{
			auto it = m_MusicTracks.find(cmd.id);
			if (it != m_MusicTracks.end())
			{
				Mix_VolumeMusic(static_cast<int>(cmd.volume * MIX_MAX_VOLUME));
				Mix_PlayMusic(it->second, -1);
			}
		}
	}
}
