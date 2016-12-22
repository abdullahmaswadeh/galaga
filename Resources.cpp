#include "Resources.h"


std::string Resources::getResourcePath(std::string filename, const std::string &subDir) {
#ifdef _WIN32
	const char PATH_SEP = '\\';
#else
	const char PATH_SEP = '/';
#endif
	static std::string baseRes;
	if (baseRes.empty()) {
		char *basePath = SDL_GetBasePath();
		if (basePath) {
			baseRes = basePath;
			SDL_free(basePath);
		}
		else {
			//std::cerr << "Error getting resource path: " << SDL_GetError() << std::endl;
			return "";
		}
		//We replace the last bin/ with res/ to get the the resource path
		size_t pos = baseRes.rfind("Debug");
		baseRes = baseRes.substr(0, pos) + "resources" + PATH_SEP;
	}
	return subDir.empty() ? baseRes : baseRes + subDir + PATH_SEP + filename;
}

std::string Resources::getImage(std::string filename) {
	return getResourcePath(filename, "images");
}

std::string Resources::getSound(std::string filename) {
	return getResourcePath(filename, "sounds");
}

std::string Resources::getFont(std::string filename) {
	return getResourcePath(filename, "fonts");
}

//Texutes
LTexture Resources::boss = LTexture();
LTexture Resources::bossBlue = LTexture();
LTexture Resources::crab = LTexture();
LTexture Resources::fly = LTexture();
LTexture Resources::rocket = LTexture();
LTexture Resources::bulletTex = LTexture();
LTexture Resources::cr_symbol = LTexture();
LTexture Resources::exp = LTexture();
LTexture Resources::expRocket = LTexture();
LTexture Resources::levelNum = LTexture();
LTexture Resources::troll = LTexture();


Text2D Resources::bigTitle = Text2D();
Text2D Resources::scoreWord = Text2D();
Text2D Resources::scoreWord2 = Text2D();
Text2D Resources::resultsWord = Text2D();
Text2D Resources::HighScore = Text2D();
Text2D Resources::PushSpaceKey = Text2D();
Text2D Resources::namcot = Text2D();
Text2D Resources::desc1 = Text2D();
Text2D Resources::desc2 = Text2D();
Text2D Resources::stageWord = Text2D();
Text2D Resources::gameStart = Text2D();
Text2D Resources::readyWord = Text2D();
Text2D Resources::score = Text2D();
Text2D Resources::hiScoreNum = Text2D();
Text2D Resources::fighterCaptured = Text2D();
Text2D Resources::framePerSecond = Text2D();
Text2D Resources::miniScore = Text2D();
Text2D Resources::bonusScore = Text2D();
Text2D Resources::perfectWord = Text2D();
Text2D Resources::developedBy = Text2D();



void Resources::initTextures() {

	boss.loadFromFile("boss.png");
	boss.cellWidth = 42.0f;
	boss.cellHeight = 41.0f;

	bossBlue.loadFromFile("bossBlue.png");
	bossBlue.cellWidth = 42.0f;
	bossBlue.cellHeight = 41.0f;

	crab.loadFromFile("crab.png");
	crab.cellWidth = 42.0f;
	crab.cellHeight = 28.0f;

	fly.loadFromFile("fly.png");
	fly.cellWidth = 42.0f;
	crab.cellHeight = 28.0f;

	exp.loadFromFile("exp.png");
	exp.cellWidth = 53.0f;
	exp.cellHeight = 39.0f;

	expRocket.loadFromFile("exp2.png");
	expRocket.cellWidth = 100.0f;
	expRocket.cellHeight = 100.0f;


	rocket.loadFromFile("rocket.png");
	rocket.cellWidth = 34.0f;
	rocket.cellHeight = 32.0f;


	bulletTex.loadFromFile("bullet.bmp");
	cr_symbol.loadFromFile("c.bmp");
	levelNum.loadFromFile("level.bmp");

	troll.loadFromFile("troll.png");
	troll.cellWidth = 122.0f;
	troll.cellHeight = 99.0f;

}

void Resources::initFonts() {

	TTF_Init();

	SDL_Color color = { 32 , 32, 244 };
	bigTitle.loadFont("atarifull.ttf", color, 105, "GALAGA", 0, 150);
	bigTitle.x = (float)(CCFG::SCREEN_WIDTH / 2 - bigTitle.sFont->w / 2);

	color = { 176, 32, 32 };
	scoreWord.loadFont("arialbd.ttf", color, 40, "SCORE", 150, 70);


	perfectWord.loadFont("arialbd.ttf", color, 40, "PERFECT !", 150, 70);





	resultsWord.loadFont("arialbd.ttf", color, 40, "-RESULTS-", 150, 70);

	color = { 255, 255, 255 };
	score.loadFont("atari.ttf", color, 18, "00", 200, 90);
	score.x = (float)(scoreWord.x + scoreWord.sFont->w) - score.sFont->w;



	color = { 176, 32, 32 };
	HighScore.loadFont("arialbd.ttf", color, 40, "HI-SCORE", 500, 70);

	color = { 244, 244, 244 };
	hiScoreNum.loadFont("atari.ttf", color, 18, "30000", 585, 90);
	hiScoreNum.x = (float)(HighScore.x + HighScore.sFont->w) - hiScoreNum.sFont->w - 20;

	color = { 72, 216, 244 };
	PushSpaceKey.loadFont("arialbd.ttf", color, 40, "PUSH  SPACE  KEY", 585, 290);
	PushSpaceKey.x = (float)(CCFG::SCREEN_WIDTH / 2 - PushSpaceKey.sFont->w / 2);

	color = { 72, 216, 244 };
	gameStart.loadFont("arialbd.ttf", color, 40, "GAME START !", 585, 100);
	gameStart.x = (float)((CCFG::SCREEN_WIDTH - 160) / 2 - gameStart.sFont->w / 2);
	gameStart.y = (float)(CCFG::SCREEN_HEIGHT / 2 - gameStart.sFont->h / 2);

	fighterCaptured.loadFont("arialbd.ttf", color, 40, "FIGHTER CAPTUERED !", 585, 100);
	fighterCaptured.x = (float)((CCFG::SCREEN_WIDTH - 200) / 2 - gameStart.sFont->w / 2);
	fighterCaptured.y = (float)(CCFG::SCREEN_HEIGHT / 2 - gameStart.sFont->h / 2);



	color = { 72, 216, 244 };
	std::string s = "STAGE";
	std::string s_con = s + "    " + std::to_string(1);
	stageWord.loadFont("arialbd.ttf", color, 40, s_con.c_str(), 585, 100);
	stageWord.x = (float)((CCFG::SCREEN_WIDTH - 160) / 2 - stageWord.sFont->w / 2);
	stageWord.y = (float)(CCFG::SCREEN_HEIGHT / 2 - stageWord.sFont->h / 2);

	bonusScore.loadFont("arialbd.ttf", color, 40, s_con.c_str(), 585, 100);



	color = { 216, 216, 32 };
	readyWord.loadFont("arialbd.ttf", color, 40, "READY !", 585, 100);
	readyWord.x = (float)((CCFG::SCREEN_WIDTH - 160) / 2 - readyWord.sFont->w / 2);
	readyWord.y = (float)(CCFG::SCREEN_HEIGHT / 2 - readyWord.sFont->h / 2);

	color = { 176, 32, 32 };
	namcot.loadFont("namco.ttf", color, 18, "namcot", 585, 370);
	namcot.x = (float)(CCFG::SCREEN_WIDTH / 2 - namcot.sFont->w / 2);


	color = { 244, 244, 244 };
	desc1.loadFont("arialbd.ttf", color, 40, "\u00A9  1981  1984  NAMCO  LTD.", 585, 440);
	desc1.x = (float)(CCFG::SCREEN_WIDTH / 2 - desc1.sFont->w / 2);

	color = { 244, 244, 244 };
	desc2.loadFont("arialbd.ttf", color, 40, "\u00A9  ALL RIGHTS RESERVED", 585, 480);
	desc2.x = (float)(CCFG::SCREEN_WIDTH / 2 - desc2.sFont->w / 2);


	color = { 255, 255, 255 };
	framePerSecond.loadFont("arialbd.ttf", color, 18, "FPS : ", 20, 20);


	color = { 244, 244, 244 };
	miniScore.loadFont("arialbd.ttf", color, 25, "Mini Score", 100, 100);

	color = { 255, 255, 255 };
	developedBy.loadFont("arialbd.ttf", color, 20, "DEVELOPED BY ABDULLAH MASWADEH", 150, 70);

}

LTexture & Resources::getTex(int type)
{
	switch (type)
	{
	case 1:
		return Resources::crab;
		break;
	case 2:
		return Resources::fly;
		break;
	case 3:
		return Resources::boss;
		break;
	default:
		return Resources::crab;
		break;
	}
}
