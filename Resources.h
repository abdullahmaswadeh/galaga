#pragma once
#ifndef _RES_PATH_H
#define _RES_PATH_H

#include "header.h"
#include "texture.h"
#include "Text.h"

class Resources {

public:

	//Textures
	static LTexture boss;
	static LTexture bossBlue;
	static LTexture fly;
	static LTexture crab;
	static LTexture rocket;
	static LTexture cr_symbol;
	static LTexture bulletTex;
	static LTexture exp;
	static LTexture expRocket;
	static LTexture levelNum;
	static LTexture troll;
	
	
	//Fonts - Words
	static Text2D bigTitle;
	static Text2D scoreWord;
	static Text2D scoreWord2;
	static Text2D resultsWord;
	static Text2D HighScore;
	static Text2D PushSpaceKey;
	static Text2D namcot;
	static Text2D desc1;
	static Text2D desc2;
	static Text2D stageWord;
	static Text2D gameStart;
	static Text2D readyWord;
	static Text2D score;
	static Text2D hiScoreNum;
	static Text2D fighterCaptured;
	static Text2D framePerSecond;
	static Text2D miniScore;
	static Text2D bonusScore;
	static Text2D perfectWord;
	static Text2D developedBy;

	static std::string getResourcePath(std::string filename, const std::string &subDir = "");
	static std::string getImage(std::string filename);
	static std::string getSound(std::string filename);
	static std::string getFont(std::string filename);

	static void initTextures();
	static void initFonts();
	static LTexture &getTex(int type);

	//LTexture soldier;
	//LTexture fly;
};



#endif
