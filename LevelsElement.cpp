#include "LevelsElement.h"
#include "Game.h"
#include "Resources.h"
/* ******************************************** */


LevelsUP::LevelsUP() {

}

LevelsUP::~LevelsUP() {}

void LevelsUP::reload() {

	if ((int)levels.size() == StageM::stage -1) return;

	static int state = 0;
	static	Timer lt;
	lt.start();

	if (state == 0) {
		levels.clear();
		state = 1;
		if (StageM::bonusStage) CCFG::Sounds->PlayChunk(CCFG::Sounds->challangeStart);
	}

	if (state == 1) {

		if(lt.checkFrameLoop(135)){
			levels.push_back(&Resources::levelNum);
			if (!StageM::bonusStage) CCFG::Sounds->PlayChunk(CCFG::Sounds->levelUp);
		}


		if ((int)levels.size() == StageM::stage -1) { state = 0;  lt.reset(); }

	}


}

void LevelsUP::renderLevels() {




	//Render Levels
	glColor3f(1, 1, 0.615f);
	for (int i = 0;i<(int)levels.size();i++) {
		float x = 640;
		if (i > 0) {
			x = (float)(levels[i - 1]->x + levels[i - 1]->getWidth() + 3);
		}

		levels[i]->render(x, 390.0f);
	}

}
