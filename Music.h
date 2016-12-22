#pragma once

#ifndef MUSIC_H
#define MUSIC_H

#include <SDL2/SDL_mixer.h>
#include <vector>
#include <string>

class Music
{
private:
	std::vector<Mix_Music*> vMusic;
	std::vector<Mix_Chunk*> vChunk;

	int iVolume;
public:
	Music(void);
	~Music(void);

	bool musicStopped;

	enum eMusic {
		mNOTHING,
		intro,
		pullRocket,
		pull2,
		captive,
		gameOver,
		imperfectBonus,
		scoreUp,
		perfectBonus
	};

	eMusic currentMusic;

	enum eChunk {
		levelUp,
		bullet,
		crabDestroy,
		flyDestroy,
		bossDestroy_1,
		bossDestroy_2,
		attack,
		rocketexp,
		revolve,
		challangeStart
	};


	void PlayMusic();
	void PlayMusic(eMusic musicID, int loop = 0);
	void StopMusic();
	void PauseMusic();
	void stopChunks(int id);
	void PlayChunk(eChunk chunkID);

	Mix_Music* loadMusic(std::string fileName);
	Mix_Chunk* loadChunk(std::string fileName);

	// -- get & set

	int getVolume();
	void setVolume(int iVolume);
	void volumeDown();
	void volumeUP();
};

#endif
