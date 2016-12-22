#include "timer.h"

void Timer::start() {
	if (!paused) {
		if (startTime == 0) {
			startTime = SDL_GetTicks();
		}
		acc++;
		newTime = SDL_GetTicks() - startTime;

		if (this->delayed) {

			if (delayCount < delayTime) {
				delayCount++;
			}
			else {
				delayed = false;
				delayCount = 0;
				delayTime = 0;
			}

		}
	}
}

bool Timer::checkFrameLoop(int milliseconds) {

	if (newTime == 0) return true;

	if ((newTime - currentTime) >= milliseconds) {
		currentTime = newTime;
		return true;
	}

	return false;
}


bool Timer::checkFrameLoopAll(int frames) {

	if (acc % frames == 0) {
		return true;
	}
	return false;
}


bool Timer::checkFrameCap(int start, int end) {

	if (newTime >= start && newTime <= end) {
		return true;
	}

	return false;
}


bool Timer::checkFrameEnd(int end) {
	if (newTime >= end) {
		return true;
	}
	return false;
}

void Timer::pause() {
	paused = true;
	//newTime = 0;
	//currentTime = 0;
}

void Timer::reset() {
	newTime = 0;
	currentTime = 0;
	startTime = 0;
	delayCount = 0;
	acc = 0;
	delayTime = 0;
	delayed = false;
	paused = false;
}

void Timer::delay(int i) {
	this->delayTime = i;
	delayed = true;
}
