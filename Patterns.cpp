#include "Patterns.h"
#include "Objects.h"
#include "StageM.h"

//Patterns
void Patterns::initPatterns() {

	//	PatternAttr p;
	GLfloat speed = 8.0f;
	GLfloat attackingSpeed = 5.5f;
	PatternAttr p;

	//Essential Patterns
#pragma region Essentials

	/*------------Park Element-----------------*/
	p.cmd = FIND_PATH;
	p.v = speed;
	p.theta = -1.0f;
	findPath.push_back(p);

	/*------------Park Element Then Rotate -----------------*/
	p.cmd = FIND_PATH;
	p.v = attackingSpeed;
	p.theta = 0.0f;
	findPath_Rotate.push_back(p);

	/*---------------------------*/

	p.cmd = ROTATE;
	p.v = 0.0f;
	p.theta = (float)M_PI / 8.0f;
	p.max = (float)M_PI;
	findPath_Rotate.push_back(p);

	/*------------Park Element attacking speed-----------------*/
	p.cmd = FIND_PATH;
	p.v = attackingSpeed;
	p.theta = -1.0f;
	findPath2.push_back(p);

#pragma endregion


/*----- Formations Patterns -------*/

	//Top Left to Bottom Intro
#pragma region Top Left Formation

	/*----------- Pattern 0 Top Left ----------*/
	p.cmd = ENTER_TOP;
	p.v = speed;
	p.y = 25.0f;
	pattern_0.push_back(p);

	/*-------------------------------*/
	p.cmd = ROTATE;
	p.v = speed;
	p.theta = (float)-M_PI / 30.0f;
	p.max = (float)-M_PI / 3.0f;
	pattern_0.push_back(p);

	/*------------------------------*/
	p.cmd = TRANSLATE;
	p.v = speed;
	p.frames = 250.0f;
	pattern_0.push_back(p);

	/*-------------------------------*/
	p.cmd = ROTATE;
	p.v = speed;
	p.theta = (float)M_PI / 35.0f;
	p.max =   5 * (float)M_PI / 6.0f;
	pattern_0.push_back(p);

#pragma endregion


#pragma region Top Left Formation Mirror

	/*----------- Pattern 0 Top Left ----------*/
	p.cmd = ENTER_TOP;
	p.v = speed;
	p.y = 25.0f;
	pattern_0_mirror.push_back(p);

	/*-------------------------------*/
	p.cmd = ROTATE;
	p.v = speed;
	p.theta = (float)-M_PI / 30.0f;
	p.max = (float)-M_PI / 3.0f;
	pattern_0_mirror.push_back(p);

	/*------------------------------*/
	p.cmd = TRANSLATE;
	p.v = speed;
	p.frames = 250.0f;
	pattern_0_mirror.push_back(p);

	/*-------------------------------*/
	p.cmd = ROTATE;
	p.v = speed;
	p.theta = (float)M_PI / 35.0f;
	p.max = 5 * (float)M_PI / 6.0f;
	pattern_0_mirror.push_back(p);

#pragma endregion

	//Top Right to Bottom
#pragma region Top Right Formation


	/*----------- Pattern 1 Top Right ----------*/
	p.cmd = ENTER_TOP;
	p.v = speed;
	p.y = 25.0f;
	pattern_1.push_back(p);

	/*-------------------------------*/
	p.cmd = ROTATE;
	p.v = speed;
	p.theta = (float)M_PI / 30.0f;
	p.max = (float)M_PI / 3.0f;
	pattern_1.push_back(p);

	/*------------------------------*/
	p.cmd = TRANSLATE;
	p.v = speed;
	p.frames = 250.0f;
	pattern_1.push_back(p);

	/*-------------------------------*/
	p.cmd = ROTATE;
	p.v = speed;
	p.theta = -(float)M_PI / 35.0f;
	p.max = -5 * (float)M_PI / 6.0f;
	pattern_1.push_back(p);


#pragma endregion

#pragma region Top Right Formation

	/*----------- Pattern 1 Top Right ----------*/
	p.cmd = ENTER_TOP;
	p.v = speed;
	p.y = 25.0f;
	pattern_1_mirror.push_back(p);

	/*-------------------------------*/
	p.cmd = ROTATE;
	p.v = speed;
	p.theta = (float)M_PI / 30.0f;
	p.max = (float)M_PI / 3.0f;
	pattern_1_mirror.push_back(p);

	/*------------------------------*/
	p.cmd = TRANSLATE;
	p.v = speed;
	p.frames = 250.0f;
	pattern_1_mirror.push_back(p);

	/*-------------------------------*/
	p.cmd = ROTATE;
	p.v = speed;
	p.theta = -(float)M_PI / 35.0f;
	p.max = -5 * (float)M_PI / 6.0f;
	pattern_1_mirror.push_back(p);


#pragma endregion


	//Lower Left to Top
#pragma region Lower Left to top - circle then park

	/*------------------------------*/
	p.cmd = ENTER_LEFT;
	p.v = speed;
	p.x = -50.0f;
	pattern_2.push_back(p);

	/*-------------------------------*/
	p.cmd = ROTATE;
	p.v = speed;
	p.theta = -(float)M_PI / 6.0f;
	p.max = -(float)M_PI / 6.0f;
	pattern_2.push_back(p);

	/*-------------------------------*/
	p.cmd = TRANSLATE;
	p.v = speed;
	p.frames = 290.0f;
	pattern_2.push_back(p);

	/*-------------------------------*/
	p.cmd = ROTATE;
	p.v = speed;
	p.theta = -(float)M_PI / 25.0f;
	p.max = -(float)M_PI * 2.0f;
	pattern_2.push_back(p);

#pragma endregion


#pragma region Lower Left to top Mirror - circle then park

	/*------------------------------*/
	p.cmd = ENTER_LEFT;
	p.v = speed;
	p.x = -50.0f;
	pattern_2_mirror.push_back(p);

	/*-------------------------------*/
	p.cmd = ROTATE;
	p.v = speed;
	p.theta = -(float)M_PI / 6.0f;
	p.max = -(float)M_PI / 6.0f;
	pattern_2_mirror.push_back(p);

	/*-------------------------------*/
	p.cmd = TRANSLATE;
	p.v = speed;
	p.frames = 325.0f;
	pattern_2_mirror.push_back(p);

	/*-------------------------------*/
	p.cmd = ROTATE;
	p.v = speed * 1.5f;
	p.theta = -(float)M_PI / 25.0f;
	p.max = -(float)M_PI * 2.0f;
	pattern_2_mirror.push_back(p);

#pragma endregion

	//Lower Right to Top
#pragma region Lower Right to top circle then Park

	/*------------------------------*/
	p.cmd = ENTER_RIGHT;
	p.v = speed;
	p.x = 660.0f;
	pattern_3.push_back(p);

	/*-------------------------------*/
	p.cmd = ROTATE;
	p.v = speed;
	p.theta = (float)M_PI / 6.0f;
	p.max = (float)M_PI / 6.0f;
	pattern_3.push_back(p);

	/*-------------------------------*/
	p.cmd = TRANSLATE;
	p.v = speed;
	p.frames = 290.0f;
	pattern_3.push_back(p);

	/*-------------------------------*/
	p.cmd = ROTATE;
	p.v = speed;
	p.theta = (float)M_PI / 25.0f;
	p.max = (float)M_PI * 2.0f;
	pattern_3.push_back(p);



#pragma endregion


#pragma region Lower Right to top Mirror - circle then park

	/*------------------------------*/
	p.cmd = ENTER_RIGHT;
	p.v = speed;
	p.x = 660.0f;
	pattern_3_mirror.push_back(p);

	/*-------------------------------*/
	p.cmd = ROTATE;
	p.v = speed;
	p.theta = (float)M_PI / 6.0f;
	p.max = (float)M_PI / 6.0f;
	pattern_3_mirror.push_back(p);

	/*-------------------------------*/
	p.cmd = TRANSLATE;
	p.v = speed;
	p.frames = 290.0f;
	pattern_3_mirror.push_back(p);

	/*-------------------------------*/
	p.cmd = ROTATE;
	p.v = speed * 1.5f;
	p.theta = (float)M_PI / 25.0f;
	p.max = (float)M_PI * 2.0f;
	pattern_3_mirror.push_back(p);

#pragma endregion



#pragma region Left Takeoff

	/*----------- Pattern Left TakeOff ----------*/
	p.cmd = ROTATE;
	p.v = attackingSpeed;
	p.theta = (float)M_PI / 4.0f;
	p.max = (float)M_PI / 4.0f;
	leftTakeoff.push_back(p);

	/*-------------------------------*/
	p.cmd = ROTATE;
	p.v = attackingSpeed;
	p.theta = -5 * (float)M_PI / 60.0f;
	p.max = -5 * (float)M_PI / 4.0f;
	leftTakeoff.push_back(p);

#pragma endregion


#pragma region Fly Attack Left Parking

	/*-------------------------------*/
	p.cmd = ROTATE;
	p.v = attackingSpeed;
	p.theta = -(float)M_PI / 40.0f;
	p.max =  -(float)M_PI / 4.0f;
	flyAttackLeftParking.push_back(p);

	/*-------------------------------*/
	p.cmd = TRANSLATE_TO_Y;
	p.v = attackingSpeed;
	p.y = 280.0f;
	flyAttackLeftParking.push_back(p);

	/*-------------------------------*/

	p.cmd = ROTATE;
	p.v = attackingSpeed;
	p.theta = -(float)M_PI / 70.0f;
	p.max = -(float)M_PI / 6.0f;
	flyAttackLeftParking.push_back(p);

	/*-------------------------------*/


	p.cmd = TRANSLATE;
	p.v = attackingSpeed;
	p.frames = 40.0f;
	flyAttackLeftParking.push_back(p);

	/*-------------------------------*/

	p.cmd = ROTATE;
	p.v = attackingSpeed;
	p.theta = (float)M_PI / 70.0f;
	p.max =  5.0f * (float)M_PI / 12.0f;
	flyAttackLeftParking.push_back(p);

	/*-------------------------------*/

	p.cmd = TRANSLATE_TO_Y;
	p.v = attackingSpeed;
	p.y = 500.0f;
	flyAttackLeftParking.push_back(p);

	/*-------------------------------*/

	p.cmd = ROTATE;
	p.v = attackingSpeed;
	p.theta = (float)M_PI / 60.0f;
	p.max = (float)M_PI;
	flyAttackLeftParking.push_back(p);




#pragma endregion


#pragma region Fly Attack Left Repeat

	/*--------------------------*/
	p.cmd = ROTATE;
	p.v = attackingSpeed;
	p.theta = (float)M_PI / 45.0f;
	p.max = (float)M_PI;
	LeftFlyrepeat.push_back(p);

	/*--------------------------*/
	p.cmd = TRANSLATE_TO_Y;
	p.v = attackingSpeed;
	p.y = 610.0f;
	LeftFlyrepeat.push_back(p);

	/*--------------------------*/

	p.cmd = MOVE_TOP;
	p.x = -1;
	p.v = attackingSpeed;
	LeftFlyrepeat.push_back(p);

	/*--------------------------*/
	p.cmd = TRANSLATE_TO_Y;
	p.v = attackingSpeed;
	p.y = 250.0f;
	LeftFlyrepeat.push_back(p);

#pragma endregion

	//add Flye Left Attack to pattern queue
	FlyAttackLeft.push_back(leftTakeoff);
	FlyAttackLeft.push_back(flyAttackLeftParking);
	FlyAttackLeft.push_back(LeftFlyrepeat);
	FlyAttackLeft.push_back(findPath2);


#pragma region Right Fly Takeoff

	/*----------- Pattern Left TakeOff ----------*/
	p.cmd = ROTATE;
	p.v = attackingSpeed;
	p.theta = -(float)M_PI / 4.0f;
	p.max = -(float)M_PI / 4.0f;
	rightTakeoff.push_back(p);

	/*-------------------------------*/
	p.cmd = ROTATE;
	p.v = attackingSpeed;
	p.theta = 5 * (float)M_PI / 60.0f;
	p.max = 5 * (float)M_PI / 4.0f;
	rightTakeoff.push_back(p);

#pragma endregion


#pragma region Fly Attack Left Parking

	/*-------------------------------*/
	p.cmd = ROTATE;
	p.v = attackingSpeed;
	p.theta = (float)M_PI / 40.0f;
	p.max = (float)M_PI / 4.0f;
	flyAttackRightParking.push_back(p);

	/*-------------------------------*/
	p.cmd = TRANSLATE_TO_Y;
	p.v = attackingSpeed;
	p.y = 280.0f;
	flyAttackRightParking.push_back(p);

	/*-------------------------------*/

	p.cmd = ROTATE;
	p.v = attackingSpeed;
	p.theta = (float)M_PI / 70.0f;
	p.max = (float)M_PI / 6.0f;
	flyAttackRightParking.push_back(p);

	/*-------------------------------*/


	p.cmd = TRANSLATE;
	p.v = attackingSpeed;
	p.frames = 40.0f;
	flyAttackRightParking.push_back(p);

	/*-------------------------------*/

	p.cmd = ROTATE;
	p.v = attackingSpeed;
	p.theta = -(float)M_PI / 70.0f;
	p.max = -5.0f * (float)M_PI / 12.0f;
	flyAttackRightParking.push_back(p);

	/*-------------------------------*/

	p.cmd = TRANSLATE_TO_Y;
	p.v = attackingSpeed;
	p.y = 500.0f;
	flyAttackRightParking.push_back(p);

	/*-------------------------------*/

	p.cmd = ROTATE;
	p.v = attackingSpeed;
	p.theta = -(float)M_PI / 60.0f;
	p.max = -(float)M_PI;
	flyAttackRightParking.push_back(p);




#pragma endregion


#pragma region Fly Attack Left Repeat

	/*--------------------------*/
	p.cmd = ROTATE;
	p.v = attackingSpeed;
	p.theta = -(float)M_PI / 45.0f;
	p.max = -(float)M_PI;
	RightFlyrepeat.push_back(p);

	/*--------------------------*/
	p.cmd = TRANSLATE_TO_Y;
	p.v = attackingSpeed;
	p.y = 610.0f;
	RightFlyrepeat.push_back(p);

	/*--------------------------*/

	p.cmd = MOVE_TOP;
	p.x = -1;
	RightFlyrepeat.push_back(p);


	/*--------------------------*/
	p.cmd = TRANSLATE_TO_Y;
	p.v = attackingSpeed;
	p.y = 250.0f;
	RightFlyrepeat.push_back(p);

#pragma endregion

	//add Fly Right Attack to pattern queue
	FlyAttackRight.push_back(rightTakeoff);
	FlyAttackRight.push_back(flyAttackRightParking);
	FlyAttackRight.push_back(RightFlyrepeat);
	FlyAttackRight.push_back(findPath2);



#pragma region Left Takeoff Crab

	/*-------------------------------*/
	p.cmd = ROTATE;
	p.v = attackingSpeed;
	p.theta = -(float)M_PI/10.0f;
	p.max =  -(float)M_PI;
	crabTakeOffLeft.push_back(p);

#pragma endregion

#pragma region Crab Attack Left

	/*-------------------------------*/

	p.cmd = TRANSLATE_TO_Y;
	p.v = attackingSpeed;
	p.y = 220.0f;

	crabAttackLeftParking.push_back(p);


	/*-------------------------------*/

	p.cmd = ROTATE;
	p.v = attackingSpeed;
	p.theta = -(float)M_PI / 50.0f;
	p.max = -(float)M_PI / 2.0f;
	crabAttackLeftParking.push_back(p);

	/*-------------------------------*/

	p.cmd = TRANSLATE;
	p.v = attackingSpeed;
	p.frames = 40.0f;

	crabAttackLeftParking.push_back(p);

	/*-------------------------------*/

	p.cmd = ROTATE;
	p.v = attackingSpeed;
	p.theta = (float)M_PI / 40.0f;
	p.max = (float)M_PI / 2.0f;
	crabAttackLeftParking.push_back(p);

	/*-------------------------------*/

	p.cmd = TRANSLATE;
	p.v = attackingSpeed;
	p.frames = 10.0f;
	crabAttackLeftParking.push_back(p);

	/*-------------------------------*/

	p.cmd = ROTATE;
	p.v = attackingSpeed;
	p.theta = (float)M_PI / 50.0f;
	p.max = (float)M_PI / 2.0f;
	crabAttackLeftParking.push_back(p);

	/*-------------------------------*/


	p.cmd = TRANSLATE;
	p.v = attackingSpeed;
	p.frames = 10.0f;
	crabAttackLeftParking.push_back(p);

	/*-------------------------------*/


	p.cmd = ROTATE;
	p.v = attackingSpeed;
	p.theta = -(float)M_PI / 50.0f;
	p.max = -(float)M_PI / 2.0f;
	crabAttackLeftParking.push_back(p);

	/* ---------------------------- */

	p.cmd = TRANSLATE_TO_Y;
	p.v = attackingSpeed;
	p.y = 620.0f;
	crabAttackLeftParking.push_back(p);

	/*-----------------------------*/

	p.cmd = MOVE_TOP;
	crabAttackLeftParking.push_back(p);


	/* ---------------------------- */
	p.cmd = TRANSLATE_TO_Y;
	p.v = attackingSpeed;
	p.y = 220.0f;
	crabRepeat.push_back(p);


#pragma endregion

	CrabAttackLeft.push_back(crabTakeOffLeft);
	CrabAttackLeft.push_back(crabAttackLeftParking);
	CrabAttackLeft.push_back(crabRepeat);
	CrabAttackLeft.push_back(findPath_Rotate);



#pragma region Right Takeoff Crab

	/*-------------------------------*/
	p.cmd = ROTATE;
	p.v = attackingSpeed;
	p.theta = (float)M_PI / 10.0f;
	p.max =   (float)M_PI;
	crabTakeOffRight.push_back(p);

#pragma endregion

#pragma region Crab Attack Right

	/*-------------------------------*/

	p.cmd = TRANSLATE_TO_Y;
	p.v = attackingSpeed;
	p.y = 220.0f;

	crabAttackRightParking.push_back(p);


	/*-------------------------------*/

	p.cmd = ROTATE;
	p.v = attackingSpeed;
	p.theta = (float)M_PI / 50.0f;
	p.max = (float)M_PI / 2.0f;
	crabAttackRightParking.push_back(p);

	/*-------------------------------*/

	p.cmd = TRANSLATE;
	p.v = attackingSpeed;
	p.frames = 40.0f;

	crabAttackRightParking.push_back(p);

	/*-------------------------------*/

	p.cmd = ROTATE;
	p.v = attackingSpeed;
	p.theta = -(float)M_PI / 40.0f;
	p.max =   -(float)M_PI / 2.0f;
	crabAttackRightParking.push_back(p);

	/*-------------------------------*/

	p.cmd = TRANSLATE;
	p.v = attackingSpeed;
	p.frames = 10.0f;
	crabAttackRightParking.push_back(p);

	/*-------------------------------*/

	p.cmd = ROTATE;
	p.v = attackingSpeed;
	p.theta = -(float)M_PI / 50.0f;
	p.max =   -(float)M_PI / 2.0f;
	crabAttackRightParking.push_back(p);

	/*-------------------------------*/


	p.cmd = TRANSLATE;
	p.v = attackingSpeed;
	p.frames = 10.0f;
	crabAttackRightParking.push_back(p);

	/*-------------------------------*/


	p.cmd = ROTATE;
	p.v = attackingSpeed;
	p.theta = (float)M_PI / 50.0f;
	p.max = (float)M_PI / 2.0f;
	crabAttackRightParking.push_back(p);

	/* ---------------------------- */

	p.cmd = TRANSLATE_TO_Y;
	p.v = attackingSpeed;
	p.y = 620.0f;
	crabAttackRightParking.push_back(p);

	/*-----------------------------*/

	p.cmd = MOVE_TOP;
	crabAttackRightParking.push_back(p);


	/* ---------------------------- */
	p.cmd = TRANSLATE_TO_Y;
	p.v = attackingSpeed;
	p.y = 220.0f;
	crabRepeat.push_back(p);


#pragma endregion

	CrabAttackRight.push_back(crabTakeOffRight);
	CrabAttackRight.push_back(crabAttackRightParking);
	CrabAttackRight.push_back(crabRepeat);
	CrabAttackRight.push_back(findPath_Rotate);


#pragma region Boss Attack Right


	/*----------- Pattern Boss Attack Right ----------*/
	p.cmd = ROTATE;
	p.v = attackingSpeed;
	p.theta = (float)M_PI/10.0f;
	p.max = (float)M_PI;
	bossRightTakeOff.push_back(p);

	/*-------------------------------*/
	p.cmd = ROTATE;
	p.v = attackingSpeed;
	p.theta = (float)M_PI / 50.0f;
	p.max = (float)M_PI / 4.0f;
	bossAttackRightParking.push_back(p);

	/*-------------------------------*/

	p.cmd = TRANSLATE_TO_Y;
	p.v = attackingSpeed;
	p.y = 100.0f;

	bossRepeat.push_back(p);

	/*-------------------------------*/

	p.cmd = TRANSLATE;
	p.v = attackingSpeed;
	p.frames = 130.0f;

	bossAttackRightParking.push_back(p);

	/*-------------------------------*/

	p.cmd = ROTATE;
	p.v = attackingSpeed;
	p.theta = (float)M_PI/35.0f;
	p.max = (float)M_PI * 2.0f;
	bossAttackRightParking.push_back(p);

	/*-------------------------------*/
	p.cmd = TRANSLATE;
	p.v = attackingSpeed;
	p.frames = 150;
	bossAttackRightParking.push_back(p);

	/*-------------------------------*/

	p.cmd = ROTATE;
	p.v = attackingSpeed;
	p.theta = -(float)M_PI / 120.0f;
	p.max = -(float)M_PI / 4.0f;
	bossAttackRightParking.push_back(p);

	/*-------------------------------*/

	p.cmd = TRANSLATE_TO_Y;
	p.v = attackingSpeed;
	p.y = 620.0f;
	bossAttackRightParking.push_back(p);

	/*-----------------------------*/

	p.cmd = MOVE_TOP;
	bossAttackRightParking.push_back(p);

#pragma endregion

	BossAttackRight.push_back(bossRightTakeOff);
	BossAttackRight.push_back(bossAttackRightParking);
	BossAttackRight.push_back(bossRepeat);
	BossAttackRight.push_back(findPath_Rotate);


#pragma region Boss Attack Left


	/*----------- Pattern Boss Attack Left ----------*/
	p.cmd = ROTATE;
	p.v = attackingSpeed;
	p.theta = -(float)M_PI / 10.0f;
	p.max = -(float)M_PI;
	bossLeftTakeOff.push_back(p);

	/*-------------------------------*/
	p.cmd = ROTATE;
	p.v = attackingSpeed;
	p.theta = -(float)M_PI / 50.0f;
	p.max = -(float)M_PI / 4.0f;
	bossAttackLeftParking.push_back(p);

	/*-------------------------------*/

	p.cmd = TRANSLATE;
	p.v = attackingSpeed;
	p.frames = 130.0f;

	bossAttackLeftParking.push_back(p);

	/*-------------------------------*/

	p.cmd = ROTATE;
	p.v = attackingSpeed;
	p.theta = -(float)M_PI / 35.0f;
	p.max = -(float)M_PI * 2.0f;
	bossAttackLeftParking.push_back(p);

	/*-------------------------------*/
	p.cmd = TRANSLATE;
	p.v = attackingSpeed;
	p.frames = 150;
	bossAttackLeftParking.push_back(p);

	/*-------------------------------*/

	p.cmd = ROTATE;
	p.v = attackingSpeed;
	p.theta = (float)M_PI / 120.0f;
	p.max =   (float)M_PI / 4.0f;
	bossAttackLeftParking.push_back(p);

	/*-------------------------------*/

	p.cmd = TRANSLATE_TO_Y;
	p.v = attackingSpeed;
	p.y = 620.0f;
	bossAttackLeftParking.push_back(p);

	/*-----------------------------*/

	p.cmd = MOVE_TOP;
	bossAttackLeftParking.push_back(p);

#pragma endregion

	BossAttackLeft.push_back(bossLeftTakeOff);
	BossAttackLeft.push_back(bossAttackLeftParking);
	BossAttackLeft.push_back(bossRepeat);
	BossAttackLeft.push_back(findPath_Rotate);



#pragma region Attack Left Pull Rocket

	/*---------------------------*/
	p.cmd = ROTATE;
	p.v = attackingSpeed;
	p.theta = -(float)M_PI / 17.0f;
	p.max = -(float)M_PI;
	bossPullRocketAttackLeft.push_back(p);


	/*---------------------------*/
	p.cmd = ROTATE;
	p.v = attackingSpeed;
	p.theta = -(float)M_PI / 80.0f;
	p.max = -(float)M_PI / 6.0f;
	bossPullRocketAttackLeft.push_back(p);

	/*---------------------------*/
	p.cmd = TRANSLATE_TO_Y;
	p.v = attackingSpeed;
	p.y = 290.0f;
	bossPullRocketAttackLeft.push_back(p);

	/*---------------------------*/
	p.cmd = ROTATE;
	p.v = attackingSpeed;
	p.theta = (float)M_PI / 80.0f;
	p.max = (float)M_PI / 6.0f;
	bossPullRocketAttackLeft.push_back(p);

	/*---------------------------*/
	p.cmd = PULLROCKET;
	bossPullRocketAttackLeft.push_back(p);

	/*---------------------------*/
	p.cmd = ROTATE;
	p.v = 0.0f;
	p.theta = -(float)M_PI / 15.0f;
	p.max = -(float)M_PI;
	bossPullRocketAttackLeft.push_back(p);


	bossPullRocketAttackLeftQ.push_back(bossPullRocketAttackLeft);

	// If didn't capture the rocket continue
	/*---------------------------*/
	p.cmd = TRANSLATE_TO_Y;
	p.y = 620.0f;
	p.v = attackingSpeed;
	bossPullRocketPark.push_back(p);

	/*---------------------------*/
	p.cmd = MOVE_TOP;
	p.x = -1;
	bossPullRocketPark.push_back(p);

#pragma endregion


#pragma region Attack Right Pull Rocket

	/*---------------------------*/
	p.cmd = ROTATE;
	p.v = attackingSpeed;
	p.theta = (float)M_PI / 17.0f;
	p.max = (float)M_PI;
	bossPullRocketAttackRight.push_back(p);


	/*---------------------------*/
	p.cmd = ROTATE;
	p.v = attackingSpeed;
	p.theta = (float)M_PI / 80.0f;
	p.max = (float)M_PI / 6.0f;
	bossPullRocketAttackRight.push_back(p);

	/*---------------------------*/
	p.cmd = TRANSLATE_TO_Y;
	p.v = attackingSpeed;
	p.y = 290.0f;
	bossPullRocketAttackRight.push_back(p);

	/*---------------------------*/
	p.cmd = ROTATE;
	p.v = attackingSpeed;
	p.theta = -(float)M_PI / 80.0f;
	p.max = -(float)M_PI / 6.0f;
	bossPullRocketAttackRight.push_back(p);

	/*---------------------------*/
	p.cmd = PULLROCKET;
	bossPullRocketAttackRight.push_back(p);

	/*---------------------------*/
	p.cmd = ROTATE;
	p.v = 0.0f;
	p.theta = -(float)M_PI / 15.0f;
	p.max = -(float)M_PI;
	bossPullRocketAttackRight.push_back(p);


	bossPullRocketAttackRightQ.push_back(bossPullRocketAttackRight);


#pragma endregion

#pragma region Rocket
	//RocketMoveToSlotP.push_back();

	p.cmd = WAIT;
	p.v = 0.0f;
	p.frames = 14;
	p.max = 200;
	RocketMoveToSlotP.push_back(p);

	rocketMoveToSlot.push_back(RocketMoveToSlotP);
	rocketMoveToSlot.push_back(findPath2);
#pragma endregion



	float bonusSpeed = 7.5f;

#pragma region Top Left / Right Bonus Stage 1

	/*----------- Pattern 0 Top Left ----------*/
	p.cmd = ENTER_TOP;
	p.v = bonusSpeed;
	p.y = 170.0f;
	pattern_0_bonus1.push_back(p);

	/*-------------------------------*/
	p.cmd = ROTATE;
	p.v = bonusSpeed;
	p.theta = (float)-M_PI / 70.0f;
	p.max = (float)-M_PI / 3.0f;
	pattern_0_bonus1.push_back(p);

	/*------------------------------*/
	p.cmd = TRANSLATE;
	p.v = bonusSpeed;
	p.frames = 140.0f;
	pattern_0_bonus1.push_back(p);

	/*-------------------------------*/
	p.cmd = ROTATE;
	p.v = bonusSpeed;
	p.theta = -(float)M_PI / 30.0f;
	p.max =  - (float)M_PI;
	pattern_0_bonus1.push_back(p);

	/*-------------------------------*/
	p.cmd = EXIT_TOP;
	p.v = bonusSpeed;
	p.y = -20.0f;
	pattern_0_bonus1.push_back(p);


	/* -------------------------- right side ---------------------- */

	p.cmd = ENTER_TOP;
	p.v = bonusSpeed;
	p.y = 170.0f;
	pattern_1_bonus1.push_back(p);

	/*-------------------------------*/
	p.cmd = ROTATE;
	p.v = bonusSpeed;
	p.theta = (float)M_PI / 70.0f;
	p.max = (float)M_PI / 3.0f;
	pattern_1_bonus1.push_back(p);

	/*------------------------------*/
	p.cmd = TRANSLATE;
	p.v = bonusSpeed;
	p.frames = 140.0f;
	pattern_1_bonus1.push_back(p);

	/*-------------------------------*/
	p.cmd = ROTATE;
	p.v = bonusSpeed;
	p.theta = (float)M_PI / 30.0f;
	p.max = (float)M_PI;
	pattern_1_bonus1.push_back(p);

	/*-------------------------------*/
	p.cmd = EXIT_TOP;
	p.v = bonusSpeed;
	p.y = -20.0f;
	pattern_1_bonus1.push_back(p);

#pragma endregion

#pragma region Lower Left/Right to top - Bonus Stage 1

	/*------------------------------*/
	p.cmd = ENTER_LEFT;
	p.v = bonusSpeed;
	p.x = -50.0f;
	pattern_2_bonus1.push_back(p);

	/*-------------------------------*/
	p.cmd = TRANSLATE;
	p.v = bonusSpeed;
	p.frames = 350.0f;
	pattern_2_bonus1.push_back(p);

	/*-------------------------------*/
	p.cmd = ROTATE;
	p.v = bonusSpeed;
	p.theta = -(float)M_PI / 50.0f;
	p.max = -(float)M_PI / 2.0f;
	pattern_2_bonus1.push_back(p);

	/*-------------------------------*/
	p.cmd = TRANSLATE;
	p.v = bonusSpeed;
	p.frames = 170.0f;
	pattern_2_bonus1.push_back(p);

	/*-------------------------------*/
	p.cmd = ROTATE;
	p.v = bonusSpeed;
	p.theta = -(float)M_PI / 30.0f;
	p.max = -(float)M_PI;
	pattern_2_bonus1.push_back(p);


	/*-------------------------------*/
	p.cmd = TRANSLATE;
	p.v = bonusSpeed;
	p.frames = 170.0f;
	pattern_2_bonus1.push_back(p);


	/*-------------------------------*/
	p.cmd = ROTATE;
	p.v = bonusSpeed;
	p.theta = -(float)M_PI / 30.0f;
	p.max = -3*(float)M_PI / 4.0f;
	pattern_2_bonus1.push_back(p);

	/*-------------------------------*/
	p.cmd = EXIT_RIGHT;
	p.v = bonusSpeed;
	p.x = 700.0f;
	pattern_2_bonus1.push_back(p);


	/* ------------------------------------ Right ----------------------------------------*/

	p.cmd = ENTER_RIGHT;
	p.v = bonusSpeed;
	p.x = 660.0f;
	pattern_3_bonus1.push_back(p);

	/*-------------------------------*/
	p.cmd = TRANSLATE;
	p.v = bonusSpeed;
	p.frames = 350.0f;
	pattern_3_bonus1.push_back(p);

	/*-------------------------------*/
	p.cmd = ROTATE;
	p.v = bonusSpeed;
	p.theta = (float)M_PI / 50.0f;
	p.max = (float)M_PI / 2.0f;
	pattern_3_bonus1.push_back(p);

	/*-------------------------------*/
	p.cmd = TRANSLATE;
	p.v = bonusSpeed;
	p.frames = 170.0f;
	pattern_3_bonus1.push_back(p);

	/*-------------------------------*/
	p.cmd = ROTATE;
	p.v = bonusSpeed;
	p.theta = (float)M_PI / 30.0f;
	p.max = (float)M_PI;
	pattern_3_bonus1.push_back(p);


	/*-------------------------------*/
	p.cmd = TRANSLATE;
	p.v = bonusSpeed;
	p.frames = 170.0f;
	pattern_3_bonus1.push_back(p);


	/*-------------------------------*/
	p.cmd = ROTATE;
	p.v = bonusSpeed;
	p.theta = (float)M_PI / 30.0f;
	p.max = 3 * (float)M_PI / 4.0f;
	pattern_3_bonus1.push_back(p);

	/*-------------------------------*/
	p.cmd = EXIT_LEFT;
	p.v = bonusSpeed;
	p.x = -40.0f;
	pattern_3_bonus1.push_back(p);


#pragma endregion


#pragma region Attacking Pattern 1

	attackingPattern t;


	t.row = 4;
	t.direction = 0;
	t.delay = 160;
	at1.push_back(t);

	t.row = 2;
	t.direction = 0;
	t.delay = 140;
	at1.push_back(t);


	t.row = 0;
	t.direction = 1;
	t.delay = 160;
	t.group = true;
	t.pullRocket = false;
	at1.push_back(t);


	t.row = 3;
	t.direction = 0;
	t.delay = 130;
	at1.push_back(t);


	t.row = 0;
	t.direction = 0;
	t.delay = 180;
	t.pullRocket = false;
	at1.push_back(t);

	t.row = 2;
	t.direction = 1;
	t.delay = 160;
	at1.push_back(t);


	t.row = 4;
	t.direction = 1;
	t.delay = 120;
	at1.push_back(t);


	t.row = 0;
	t.direction = 0;
	t.delay = 160;
	t.pullRocket = true;
	at1.push_back(t);

	t.row = 4;
	t.direction = 0;
	t.delay = 130;
	at1.push_back(t);


	t.row = 0;
	t.direction = 0;
	t.delay = 100;
	t.pullRocket = false;
	at1.push_back(t);


	t.row = 3;
	t.direction = 1;
	t.delay = 120;
	at1.push_back(t);


	t.row = 1;
	t.direction = 0;
	t.delay = 160;
	at1.push_back(t);

	t.row = 3;
	t.direction = 1;
	t.delay = 20;
	at1.push_back(t);


	t.row = 1;
	t.direction = 0;
	t.delay = 80;
	at1.push_back(t);


	t.row = 4;
	t.direction = 0;
	t.delay = 150;
	at1.push_back(t);


#pragma endregion
}
