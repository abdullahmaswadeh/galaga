#pragma once
#ifndef _PHYSIX_H_
#define _PHYSIX_H_
#include "shapes.h"
#include "Ship.h"
#include "Bullet.h"
#include "Text.h"

//Distance between points
GLfloat Distance(GLfloat dX0, GLfloat dY0, GLfloat dX1, GLfloat dY1);

//Random Float Numbers
float RandomFloat(float a, float b);

float CalcShortestRot(float from, float to);

bool CalcShortestRotDirection(float from, float to);

bool BulletShipCollision(Ship &ship, Bullet &bullet);

bool BulletRocketCollision(Rocket & r, Bullet & b);

bool R_RCollision(Rocket & r, Rocket & r2);

void pullRocket(GameObject *ship);

void DrawArc(float cx, float cy, float r, float start, float end, int num_segments, int color);

void releaseRocket();

void dumpRocket(bool reset = false);

float posCenter(Text2D & txt, bool nav);

void DrawPulling(int frame, float cx, float cy);

#endif // !_PHYSIX_H_
