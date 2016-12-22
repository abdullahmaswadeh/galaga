#ifndef _SHIP_H_
#define _SHIP_H_
#include "header.h"
#include "Objects.h"
#include "Rocket.h"
#include "timer.h"

class Ship: public GameObject {

public:


	bool parked = false;
	bool bossoneAttack = false;
	unsigned int bonus = 0;

	int texFrame = 0;
	int Bosshits = 2;

	void Reset();
	void setPos(GLfloat x, GLfloat y);
	void distract();
	void update();
	void draw();

	void newRandomShots(int startRange, int endRange);

	Rocket *rocket = nullptr;
	bool attack(bool bossAttack = false, int dir = 0, bool pullRocket = false);
	void destroy(bool all = false);

	void updateBounds();

	void shoot();



	//shoot
	Timer mTimer = Timer();
	std::vector<int> shootTime;


	float formation_offset = 0.0f;
};

#endif // !_SHIP_H_

