#pragma once

#include <iostream>
#include <map>
#include <string>
#include "SDL_mixer.h"

enum sound_type
{
	SOUND_MUSIC = 0,
	SOUND_SFX = 1
};

class SoundManager
{
public:
	static SoundManager* Instance() {
		if (s_pInstance == 0) {
			s_pInstance = new SoundManager();
			return s_pInstance;
		}
		return s_pInstance;
	}

	bool load(std::string fileName, std::string id, sound_type type);

	void playSound(std::string id, int loop);
	void playMusic(std::string id, int loop);

	void turnOff();
	void pauseMusic();
	void resumeMusic();

private:
	static SoundManager* s_pInstance;

	std::map<std::string, Mix_Chunk*> _sfxs;
	std::map<std::string, Mix_Music*> _music;

	SoundManager();
	~SoundManager();

	SoundManager(const SoundManager&);
	SoundManager& operator=(const SoundManager&);
};

typedef SoundManager TheSoundManager;

