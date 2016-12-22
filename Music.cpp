#include "Music.h"
#include "Resources.h"

/* ******************************************** */

Music::Music(void) {

	if (Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 1024) < 0)
	{
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
	}

    vMusic.push_back(loadMusic("intro.wav"));
	vMusic.push_back(loadMusic("pullRocket.wav"));
	vMusic.push_back(loadMusic("pull2.wav"));
	vMusic.push_back(loadMusic("captive.wav"));
	vMusic.push_back(loadMusic("gameOver.wav"));
	vMusic.push_back(loadMusic("imperfectBonus.wav"));
	vMusic.push_back(loadMusic("scoreUp.wav"));
	vMusic.push_back(loadMusic("perfectBonus.wav"));




	vChunk.push_back(loadChunk("levelup.wav"));
	vChunk.push_back(loadChunk("bullet.wav"));
	vChunk.push_back(loadChunk("crabDestroy.wav"));
	vChunk.push_back(loadChunk("flyDestroy.wav"));
	vChunk.push_back(loadChunk("bossDestroy_1.wav"));
	vChunk.push_back(loadChunk("bossDestroy_2.wav"));
	vChunk.push_back(loadChunk("attack.wav"));
	vChunk.push_back(loadChunk("rocketexp.wav"));
	vChunk.push_back(loadChunk("revolve.wav"));
	vChunk.push_back(loadChunk("challangeStart.wav"));


	setVolume(100);

	this->currentMusic = mNOTHING;
}

Music::~Music(void) {
	for (unsigned int i = 0; i < vMusic.size(); i++) {
		Mix_FreeMusic(vMusic[i]);
	}

	vMusic.clear();

	for (unsigned int i = 0; i < vChunk.size(); i++) {
		Mix_FreeChunk(vChunk[i]);
	}

	vChunk.clear();
}

/* ******************************************** */


void Music::PlayMusic() {
	if (CCFG::muteMusic) return;

	if (currentMusic != mNOTHING) {
		Mix_PlayMusic(vMusic[currentMusic - 1], 0);
		musicStopped = false;
	}
	else {
		StopMusic();
	}
}

void Music::PlayMusic(eMusic musicID, int loop) {
	if (CCFG::muteMusic) return;

	if (musicID != mNOTHING) {
		Mix_PlayMusic(vMusic[musicID - 1], loop);
		musicStopped = false;
		currentMusic = musicID;
	}
	else {
		StopMusic();
		currentMusic = mNOTHING;
	}
}

void Music::StopMusic() {
	if (!musicStopped) {
		Mix_HaltMusic();
		musicStopped = true;
	}
}

void Music::stopChunks(int id) {
	Mix_HaltChannel(id);

	Mix_HaltMusic();
}

void Music::PauseMusic() {
	if (Mix_PausedMusic() == 1) {
		Mix_ResumeMusic();
		musicStopped = false;
	}
	else {
		Mix_PauseMusic();
		musicStopped = true;
	}
}

/* ******************************************** */

void Music::PlayChunk(eChunk chunkID) {

	if (CCFG::muteSounds) return;

	int channel = chunkID;
	if (chunkID > 7) {
		channel = chunkID - 8;
	}

	Mix_VolumeChunk(vChunk[chunkID], iVolume);
	Mix_PlayChannel(channel, vChunk[chunkID], 0);
}

/* ******************************************** */

Mix_Music* Music::loadMusic(std::string fileName) {
	fileName = Resources::getSound(fileName);

	return Mix_LoadMUS(fileName.c_str());
}

Mix_Chunk* Music::loadChunk(std::string fileName) {
	fileName = Resources::getSound(fileName);
	return Mix_LoadWAV(fileName.c_str());
}

int Music::getVolume() {
	return iVolume;
}

void Music::setVolume(int iVolume) {
	this->iVolume = iVolume;
	Mix_VolumeMusic(iVolume);
}

void Music::volumeDown() {
	for (int i = 0; i < 10; i++) {
		if (i == 7)continue;
		Mix_Volume(i, 0);

	}

}

void Music::volumeUP() {
	for (int i = 0; i < 10; i++) {
		Mix_Volume(i, MIX_MAX_VOLUME);

	}
}
