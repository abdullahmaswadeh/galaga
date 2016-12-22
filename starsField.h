#pragma once
#ifndef _STARSFIELD_
#define _STARSFIELD_
#include "header.h"
#include <vector>
#include "shapes.h"
#include "timer.h"

class StarsField {

public:
	void initSpace();
	void Render();
	void Update();
	static bool reverse;
	static bool easeDown;
	float revSpeed;

private:
	void moveStarsfield(rect &star);
	std::vector<star> starsField;
	float getNewSpeed();

};



#endif // !_STARSFIELD_
