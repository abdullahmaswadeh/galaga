#include "stages.h"
#include "Formations.h"
#include "Objects.h"
#include "Elements.h"
#include "StageM.h"

stageFuncs stages::stagesArr[4];

void stages::init() {
	stagesArr[0] = &stage1;
	stagesArr[1] = &stage2;
	stagesArr[2] = &stage3;
	stagesArr[3] = &stage4;
}

void stages::loadStage(int index) {

	//call func

	//if (index > 2) return;

 	(*stagesArr[index])();
}

void stages::stage1() {

	//Load intro Formations
	Formations::TopBottom(0, 3, CRAB, 0 , Elements::patterns.pattern_0, 250.0f);
	Formations::TopBottom(4, 7,FLY, 0, Elements::patterns.pattern_1, 370.0f);
	Formations::LeftBottomTop(8, 15, BOSS, CRAB, Elements::patterns.pattern_2, 0.0f);
	Formations::RightBottomTop(16, 23, CRAB, 0, Elements::patterns.pattern_3, 0.0f);
	Formations::TopBottom(24, 31,FLY, 0, Elements::patterns.pattern_1, 370.0f);
	Formations::TopBottom(32, 39, FLY, 0 , Elements::patterns.pattern_0, 250.0f);

	StageM::ATPQ = &Elements::patterns.at1;

}

void stages::stage2() {

	//Load intro Formations
	Formations::TopBottom(0, 3, CRAB, 0, Elements::patterns.pattern_0, 250.0f);
	Formations::TopBottom(4, 7, FLY, 0, Elements::patterns.pattern_1, 370.0f);
	Formations::LeftBottomTop(8, 15, BOSS, CRAB, Elements::patterns.pattern_2, 0.0f, true);
	Formations::RightBottomTop(16, 23, CRAB, 0, Elements::patterns.pattern_3, 0.0f, true);
	Formations::TopBottom(24, 31, FLY, 0, Elements::patterns.pattern_1, 370.0f, true, 1);
	Formations::TopBottom(32, 39, FLY, 0, Elements::patterns.pattern_0, 250.0f, true);

	StageM::ATPQ = &Elements::patterns.at1;


	//shoots
	StageM::ships[0].shootTime.push_back(8);
	StageM::ships[4].shootTime.push_back(8);

	StageM::ships[8].shootTime.push_back(70);
	StageM::ships[12].shootTime.push_back(70);

	StageM::ships[16].shootTime.push_back(70);
	StageM::ships[20].shootTime.push_back(70);

	StageM::ships[24].shootTime.push_back(30);
	StageM::ships[28].shootTime.push_back(30);

	StageM::ships[32].shootTime.push_back(30);
	StageM::ships[36].shootTime.push_back(30);

}

void stages::stage3() {

	StageM::bonusStage = true;

	//Load intro Formations
	Formations::TopBottom(0, 3, FLY, 0, Elements::patterns.pattern_0_bonus1, 250.0f);
	Formations::TopBottom(4, 7, FLY, 0, Elements::patterns.pattern_1_bonus1, 350.0f);
	Formations::LeftBottomTop(8, 15, FLY, BOSS, Elements::patterns.pattern_2_bonus1, 0.0f);
	Formations::RightBottomTop(16, 23, FLY, 0, Elements::patterns.pattern_3_bonus1, 0.0f);
	Formations::TopBottom(24, 31, FLY, 0, Elements::patterns.pattern_1_bonus1, 370.0f);
	Formations::TopBottom(32, 39, FLY, 0, Elements::patterns.pattern_0_bonus1, 250.0f);


}


void stages::stage4() {

	//Load intro Formations
	Formations::TopBottom(0, 3, CRAB, 0, Elements::patterns.pattern_0, 250.0f);
	Formations::TopBottom(4, 7, FLY, 0, Elements::patterns.pattern_1, 370.0f);
	Formations::LeftBottomTop(8, 15, BOSS, CRAB, Elements::patterns.pattern_2, 0.0f, true);
	Formations::RightBottomTop(16, 23, CRAB, 0, Elements::patterns.pattern_3, 0.0f, true);
	Formations::TopBottom(24, 31, FLY, 0, Elements::patterns.pattern_1, 370.0f, true, 1);
	Formations::TopBottom(32, 39, FLY, 0, Elements::patterns.pattern_0, 250.0f, true);

	StageM::ATPQ = &Elements::patterns.at1;


	//shoots
	//StageM::ships[0].newRandomShots(8, 10);
	//StageM::ships[4].newRandomShots(8, 10);
	//StageM::ships[4].shootTime.push_back(8);


	for (int i = 0; i < 40; i++) {
		for (int x = 0; x < 10; x+=2) {
			StageM::ships[i].shootTime.push_back(x*x);
		}
	}

}
