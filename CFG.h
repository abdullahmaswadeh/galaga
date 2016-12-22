#pragma once

#ifndef CFG_H
#define CFG_H
#include "Music.h"

class CCFG
{
private:

public:
	CCFG(void);
	~CCFG(void);

	static int SCREEN_WIDTH, SCREEN_HEIGHT;
	static float HALF_SCREEN_W, HALF_SCREEN_H;
	static Music* Sounds;
	static bool muteMusic;
	static bool muteSounds;
	static float interpolation;
	static bool controlsEnabled;
	static bool fullScreen;

	//statistics
	static unsigned int shots;
	static unsigned int hits;

};

#endif
