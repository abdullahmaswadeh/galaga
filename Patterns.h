#pragma once
#ifndef _PATTERN_H_
#define _PATTERN_H_
#include "header.h"
#include <vector>

const int TRANSLATE = 0;
const int ROTATE = 1;
const int TRANSLATE_TO = 2;
const int EXIT_LEFT = 3;
const int EXIT_RIGHT = 4;
const int ENTER_LEFT = 5;
const int ENTER_RIGHT = 6;
const int TRANSLATE_TO_Y = 7;
const int SET_POS = 8;
const int ENTER_TOP = 10;
const int FIND_PATH = 9;
const int MOVE_TOP = 11;
const int PULLROCKET = 12;
const int WAIT = 13;
const int EXIT_TOP = 14;


//Movements Patters
struct PatternAttr {
	int cmd;
	short order;
	GLfloat v;
	GLfloat x;
	GLfloat y;
	GLfloat theta;
	GLfloat max;
	GLfloat frames;
	int slot;
	bool action;
	bool shoot = false;
};

struct attackingPattern {
	int row;
	int direction;
	int delay;
	int slot;
	bool pullRocket = false;
	bool group = false;
};


//defs
typedef std::vector<PatternAttr> PATTERN;
typedef std::vector<PATTERN> PATTERNQUEUE;
typedef std::vector<attackingPattern> ATTACKINGPATTERNQUEUE;


class Patterns
{
public:

	//Intros Formations
	PATTERN pattern_0; //Top Left Down Park
	PATTERN pattern_0_mirror; //Top Left Down Park mirror

	PATTERN pattern_1; //Top Right Down Park
	PATTERN pattern_1_mirror; //Top Right Down Park


	PATTERN pattern_2; // Lower Left  Top Circle Park
	PATTERN pattern_2_mirror; // Lower Left  Top Circle Park mirror

	PATTERN pattern_3; // Lower Right Top Circle Park
	PATTERN pattern_3_mirror; // Lower Right Top Circle Park mirror

	//Essentials
	PATTERN findPath;  //Park Element to desired slot
	PATTERN findPath2;  //Park Element to desired slot
	PATTERN findPath_Rotate;         //Find Path Then Rotate

	//Attacks Movements

	//Flies
	PATTERN leftTakeoff;            //Fly Attack Left takeoff
	PATTERN LeftFlyrepeat;          //Fly Attack Left repeat
	PATTERN flyAttackLeftParking;   //Fly Attack ready to park

	PATTERN rightTakeoff;            //Fly Attack right takeoff
	PATTERN RightFlyrepeat;          //Fly Attack right repeat
	PATTERN flyAttackRightParking;   //Fly Attack right ready to park


	PATTERNQUEUE FlyAttackLeft;
	PATTERNQUEUE FlyAttackRight;

	//Crabs


	PATTERN crabTakeOffLeft;         //Crab Attack Left TakeOff
	PATTERN crabTakeOffRight;        //Crab Attack Right TakeOff
	PATTERN crabAttackLeftParking;   //Crab Attack Left Parking
	PATTERN crabAttackRightParking;  //Crab Attack Right Parking
	PATTERN crabRepeat;              //Crab Attack Left-Right Repeat


	PATTERNQUEUE CrabAttackLeft;
	PATTERNQUEUE CrabAttackRight;

	PATTERN bossLeftTakeOff;  //Boss Attack Left TakeOff
	PATTERN bossRightTakeOff;  //Boss Attack right TakeOff
	PATTERN bossFindPath;  //Boss Attack FindPath
	PATTERN bossRepeat;  //Boss Attack Repeat
	PATTERN bossAttackRightParking;  //Boss Attack right parking
	PATTERN bossAttackLeftParking;  //Boss Attack Left Parking

	PATTERNQUEUE BossAttackLeft;
	PATTERNQUEUE BossAttackRight;

	//pullRocket Attack Left
	PATTERN bossPullRocketAttackLeft;
	PATTERN bossPullRocketPark;
	PATTERNQUEUE bossPullRocketAttackLeftQ;

	//pull rocket attack right
	PATTERN bossPullRocketAttackRight;
	PATTERNQUEUE bossPullRocketAttackRightQ;

	//Rocket
	PATTERN RocketMoveToSlotP;
	PATTERNQUEUE rocketMoveToSlot;

	//Attacking Patterns
	ATTACKINGPATTERNQUEUE at1;
	ATTACKINGPATTERNQUEUE at2;
	ATTACKINGPATTERNQUEUE at3;


	PATTERN pattern_0_bonus1; //Top Bottom Bonus Stage 1
	PATTERN pattern_1_bonus1; //Top Bottom Bonus Stage 1
	PATTERN pattern_2_bonus1; //Top Bottom Bonus Stage 1
	PATTERN pattern_3_bonus1; //Top Bottom Bonus Stage 1


	void initPatterns();

};




#endif // !
