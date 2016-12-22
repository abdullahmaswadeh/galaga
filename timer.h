#pragma once
#ifndef _TIMER_H_
#define _TIMER_H_

#include "header.h"

class Timer {

public:
	long startTime = 0;
	long currentTime = 0;
	long newTime = 0;
	bool paused = false;
	int acc = 0;
	int delayTime = 0;
	bool delayed = false;
	int delayCount = 0;
	void start();
	bool checkFrameLoop(int milliseconds);
	bool checkFrameLoopAll(int frames);
	bool checkFrameCap(int start, int end);
	bool checkFrameEnd(int end);
	void reset();
	void pause();
	void delay(int t);

};

#endif // !_TIMER_H_
