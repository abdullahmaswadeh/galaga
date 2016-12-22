#pragma once
#ifndef _GAME_OBJECT_H_
#include "header.h"
#include <vector>
#include "Patterns.h"
#include "texture.h"

//objType
const int BULLET = 0;
const int CRAB = 1;
const int FLY = 2;
const int BOSS = 3;
const int ROCKET = 4;

class GameObject
{
public:

	//Texture
	LTexture *tex;

	//Animation Patterns
	PATTERN cur_pattern;
	PATTERNQUEUE PatternQueue;
	int cur_cmd = 0;
	int patternQueuePos = 0;

	//Coordinates
	GLfloat w, h, x, y;
	GLfloat v;
	GLfloat theta;
	GLfloat dt = 0;
	GLfloat dtheta = 0;
	GLfloat cosine = 0.0f;
	GLfloat sine = 0.0f; 
	GLfloat accel = 0.0f;
	float targetTheta = 0.0f;
	bool endPattern = false;

	//Dimensions
	float rightBound;
	float leftBound;
	float topBound;
	float bottomBound;

	int type;
	void updatePos();
	void setPatternQueue(PATTERNQUEUE &patternQueue);
	void clearPatternQueue();

	//special members for ships
	int slot;
	int id;
	bool attacking = false;
	bool contAttacking = false;
	bool endMotion = false;
	bool alive = true;

	GameObject *capShip = nullptr;
};

#endif // !_GAME_OBJECT_H_