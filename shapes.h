#include "header.h"

//Rectangle

#ifndef shape_H
#define shape_H
class shape {
public:
	GLfloat width, height, x, y, vectorLeft, vectorRight, vectorTop, vectorBottom, speedX, speedY, initX, initY;
	GLfloat R = 1.0f, G = 1.0f, B = 1.0f;
	void setColor(GLfloat R, GLfloat G, GLfloat B);
};

#endif // !rec


#ifndef rec_H
#define rec_H
class rect : public shape {
public:
	rect();
	rect(GLfloat x, GLfloat y, GLfloat width, GLfloat height, GLfloat speedX, GLfloat speedY);
	void init(GLfloat x, GLfloat y, GLfloat width, GLfloat height, GLfloat speedX, GLfloat speedY);
	rect(GLfloat x, GLfloat y, GLfloat width, GLfloat height);
	void draw();
	void updateVectors();
};

#endif // !rec


#pragma once
#ifndef star_H
#define star_H
class star : public rect {
public:
	GLfloat angleDir;
	star(GLfloat x, GLfloat y, GLfloat width, GLfloat height);
};

#endif // !rec


