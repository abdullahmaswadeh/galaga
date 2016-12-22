#include "StageM.h"
#include "Formations.h"
#include "Resources.h"
#include "CFG.h"
#include "Elements.h"

void Formations::TopBottom(int start, int end, int t1, int t2, PATTERN &p, float startX, bool mirror, int dir) {

	PATTERNQUEUE formationPatternQueue;
	PATTERNQUEUE formationPatternQueueMirror;
	formationPatternQueue.push_back(p);
	if(!StageM::bonusStage) formationPatternQueue.push_back(Elements::patterns.findPath);


	if (mirror) {

		if (dir == 1) {
			formationPatternQueueMirror.push_back(Elements::patterns.pattern_1_mirror);
			if (!StageM::bonusStage)formationPatternQueueMirror.push_back(Elements::patterns.findPath);

		}
		else {
			formationPatternQueueMirror.push_back(Elements::patterns.pattern_0_mirror);
			if (!StageM::bonusStage)formationPatternQueueMirror.push_back(Elements::patterns.findPath);
		}
	}

	GLfloat startTheta = (float)M_PI/2;
	GLfloat startY;
	int length = end - start;
	for (int i = 0; i <= length; i++) {

		StageM::ships[start].Reset();
		StageM::ships[start].id = i;

		if (!mirror) {
			startY = (-27.0f) - (i * 50.0f);

			StageM::ships[start].setPos(startX, startY);
			StageM::ships[start].setPatternQueue(formationPatternQueue);
		}
		else {

			if (i % 2 == 0) {
				startY = (-27.0f) - (i * 25.0f);
				StageM::ships[start].setPos(startX, startY);
				StageM::ships[start].setPatternQueue(formationPatternQueue);
			}
			else {
				StageM::ships[start].setPos(startX + 50.0f, startY);
				StageM::ships[start].setPatternQueue(formationPatternQueueMirror);
			}

		}

		StageM::ships[start].tex = &Resources::getTex(t1);
		StageM::ships[start].type = t1;

		StageM::ships[start].theta = startTheta;
		StageM::ships[start].alive = true;
		start++;
	}
}


void Formations::LeftBottomTop(int start, int end, int t1, int t2, PATTERN &p, float startX, bool mirror) {

	PATTERNQUEUE formationPatternQueue;
	PATTERNQUEUE formationPatternQueueMirror;
	formationPatternQueue.push_back(p);
	if (!StageM::bonusStage)formationPatternQueue.push_back(Elements::patterns.findPath);

	formationPatternQueueMirror.push_back(Elements::patterns.pattern_2_mirror);
	if (!StageM::bonusStage)formationPatternQueueMirror.push_back(Elements::patterns.findPath);

	//Second Group
	GLfloat startTheta = 0.0;

	GLfloat startY = CCFG::SCREEN_HEIGHT - 170.0f;

	if(StageM::bonusStage)
		 startY = CCFG::SCREEN_HEIGHT - 140.0f;


	//first group
	int length = end - start;
	for (int i = 0; i <= length; i++) {

		if (t2 == 0) t2 = t1;

		StageM::ships[start].Reset();
		StageM::ships[start].id = i;

		if (!mirror) {
			startX = (-60.0f) - (i * 50.0f);

			if (i % 2 == 0) {
				StageM::ships[start].tex = &Resources::getTex(t1);
				StageM::ships[start].type = t1;
			}
			else {
				StageM::ships[start].tex = &Resources::getTex(t2);
				StageM::ships[start].type = t2;
			}

			StageM::ships[start].setPos(startX, startY);
			StageM::ships[start].setPatternQueue(formationPatternQueue);

		}
		else {



			if (i % 2 == 0) {
				startX = (-60.0f) - (i * 25.0f);
				StageM::ships[start].tex = &Resources::getTex(t1);
				StageM::ships[start].type = t1;
				StageM::ships[start].setPos(startX, startY + 50.0f);

				StageM::ships[start].setPatternQueue(formationPatternQueueMirror);
			}
			else {
				StageM::ships[start].tex = &Resources::getTex(t2);
				StageM::ships[start].type = t2;
				StageM::ships[start].setPos(startX, startY);
				StageM::ships[start].setPatternQueue(formationPatternQueue);
			}




		}

		StageM::ships[start].theta = startTheta;
		StageM::ships[start].alive = true;

		start++;

	}


}


void Formations::RightBottomTop(int start, int end, int t1, int t2, PATTERN &p, float startX, bool mirror) {


	PATTERNQUEUE formationPatternQueue;
	PATTERNQUEUE formationPatternQueueMirror;
	formationPatternQueue.push_back(p);
	if (!StageM::bonusStage)formationPatternQueue.push_back(Elements::patterns.findPath);

	formationPatternQueueMirror.push_back(Elements::patterns.pattern_3_mirror);
	if (!StageM::bonusStage)formationPatternQueueMirror.push_back(Elements::patterns.findPath);

	//Second Group
	GLfloat startTheta = (float)M_PI;
	GLfloat startY = CCFG::SCREEN_HEIGHT - 170.0f;

	if (StageM::bonusStage)
		startY = CCFG::SCREEN_HEIGHT - 140.0f;


	//first group
	int length = end - start;
	for (int i = 0; i <= length; i++) {

		StageM::ships[start].Reset();
		StageM::ships[start].id = i;
		if (t2 == 0) t2 = t1;

		if (!mirror) {
			startX = (660.0f) + (i * 50.0f);

			if (i % 2 == 0) {
				StageM::ships[start].tex = &Resources::getTex(t1);
				StageM::ships[start].type = t1;
			}
			else {



				StageM::ships[start].tex = &Resources::getTex(t2);
				StageM::ships[start].type = t2;
			}

			StageM::ships[start].setPos(startX, startY);
			StageM::ships[start].setPatternQueue(formationPatternQueue);

		}
		else {



			if (i % 2 == 0) {
				startX = (660.0f) + (i * 25.0f);
				StageM::ships[start].tex = &Resources::getTex(t1);
				StageM::ships[start].type = t1;
				StageM::ships[start].setPos(startX, startY + 50.0f);

				StageM::ships[start].setPatternQueue(formationPatternQueueMirror);
			}
			else {
				StageM::ships[start].tex = &Resources::getTex(t2);
				StageM::ships[start].type = t2;
				StageM::ships[start].setPos(startX, startY);
				StageM::ships[start].setPatternQueue(formationPatternQueue);
			}

		}

		StageM::ships[start].theta = startTheta;

		StageM::ships[start].alive = true;

		start++;

	}


}
