#ifndef _LEVELS_H_
#define _LEVELS_H_
#include <vector>
#include "header.h"
#include "timer.h"
#include "texture.h"
#include <vector>

class LevelsUP {
private:
	Timer t;
	LTexture levelImage;
	std::vector<LTexture*>levels;
	int lvlcount = 0;

public:


	LevelsUP();
	~LevelsUP();
	void reload();
	void renderLevels();

};


#endif // !_LEVELS_H_
