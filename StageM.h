#pragma once
#ifndef _STAGE_H_
#define _STAGE_H_

#include "header.h"
#include <vector>
#include "Ship.h"
#include "Resources.h"
#include "timer.h"

/* ----------------- */
const int numShips = 40;


//Stages Manager
class StageM {

public:

	struct Slot
	{
		float x;
		float y;
	};

	//exp
	struct Aexp {
		LTexture *tex;
		Timer t;
		int frame = 0;
		float x = 100;
		float y = 100;
		int maxFrame = 3;
	};

	//miniScores that shows on screen
	struct miniScore {
		Timer t;
		float x = 100;
		float y = 100;
		unsigned int value;
		float color[3] = { 1.0f, 1.0f, 1.0f };
	};

	struct pullRE {
		float x = 100.0f;
		float y = 100.0f;
		int frame = 0;
		bool render = false;
	};

	static Ship ships[numShips];
	static Slot slots[numShips];

	static int stage;
	static int state;
	static int MAX_GROUP_ATTACK;
	static pullRE pullR;

	//intro
	static int parkedElements;

	//number currently attacking ships
	static int attackingNum;

	static bool rocketPullAttack;

	/* ---------- */
	void initSlots();
	void texAnimate();
	void Init();
	static bool runIntro(bool reset = false);
	void distract();
	void Update();
	void Draw();
	static bool bonusStage;
	static int bonusHits;
	static int bonusGroupHits;

	void checkCollision();

	void attack();
	int findBySlot(int index);
	static void parkAll();
	static void nextStage();
	static void exp(GLfloat x, GLfloat y, LTexture *tex = &Resources::exp);
	static void pushMiniScore(GLfloat x, GLfloat y, unsigned int val , float color[3]);
	void UpdateExpsFrame();
	void renderMiniScores();
	static std::vector<Aexp> exps;
	static std::vector<miniScore> miniScores;

	bool initiated = false;

	/* ----------- */
	static int alives;
	int attackPos = 0;

	//attacking Pattern Queue
	static ATTACKINGPATTERNQUEUE *ATPQ;
	static Timer attTimer;


};

#endif // !_STAGE_H_
