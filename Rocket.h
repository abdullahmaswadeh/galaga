#pragma once

#ifndef _ROCKET_H
#define _ROCKET_H
#include "header.h"
#include "Bullet.h"


class Rocket : public GameObject {
public:

	float speedX;

	//screen bounds
	float boundLeft;
	float boundRight;


	int state = 1;
	int captuered = 0;
	bool enabled = false;
	bool moveToSlot = false;

	bool pulling = false;
	float color[3] = { 1.0f, 1.0f, 1.0f };


	float slotX = 0;
	float slotY = 0;


	void init();
	void render();
	void update();
	void updateBounds();
	void destroy(bool byR = false);
	void shootBullet();
	void updateMovementBounds();
	void setCenterPos();
	void reset();

};


#endif // !_ROCKET_H
