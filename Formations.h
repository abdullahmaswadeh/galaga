#pragma once
#ifndef _FORMATIONS_H_
#define _FORMATIONS_H_
#include "header.h"
#include <vector>
#include "Patterns.h"

class Formations {

public:
	static void TopBottom(int start, int end, int t1, int t2, PATTERN &p, float startX, bool mirror = false, int dir = 0);
	static void LeftBottomTop(int start, int end, int t1, int t2, PATTERN & p, float startX, bool mirror = false);
	static void RightBottomTop(int start, int end, int t1, int t2, PATTERN & p, float startX , bool mirror = false);

};

#endif // !_FORMATIONS_H_
