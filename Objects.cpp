#include "Objects.h"
#include "StageM.h"
#include "physix.h"
#include <cmath>

void GameObject::updatePos() {

	if ((int)PatternQueue.size() == 0) return;

	PATTERN p = this->PatternQueue[patternQueuePos];

	if ((int)p.size() == 0) return;


	int i = this->cur_cmd;

	if ((int)p.size() == 0) return;


	if (StageM::stage == 5) accel = 2.0f;

	float velocity = p[i].v;
	if (accel > 0.0f && p[i].v > 0.0f) {
		velocity += accel;
	}


	switch (p[i].cmd) {

	case ENTER_LEFT:
		this->v = velocity;
		if (this->x >= p[i].x) {
			this->cur_cmd++;
		}
		break;

	case ENTER_RIGHT:
		this->v = velocity;
		if (this->x <= p[i].x) {
			this->cur_cmd++;
		}
		break;

	case ENTER_TOP:
		this->v = velocity;
		if (this->y >= p[i].y) {
			this->cur_cmd++;
		}
		break;



	case SET_POS:
		this->v = velocity;
		this->x = p[i].x;
		this->y = p[i].y;
		this->theta = p[i].theta;
		break;



	case MOVE_TOP:

		if (this->contAttacking) {
			int rnd = 0;
			if (StageM::slots[this->slot].x <= 335.0f) {
				rnd = rand() % 5 + 30;
			}
			else {
				rnd = rand() % 5 + 35;
			}

			if (this->type == BOSS && (this->slot == 0 || this->slot == 1)) {
				rnd = rand() % 3 + 4;
			}

			if (this->type == BOSS && (this->slot == 2 || this->slot == 3)) {
				rnd = rand() % 3 + 9;
			}

			this->x = StageM::slots[rnd].x;

			if (this->type == ROCKET && this->capShip != nullptr) {
				this->x = this->capShip->x;
			}
		}
		else {
			this->x = StageM::slots[this->slot].x;
		}


		this->y = -10.0f;
		this->v = 0.0f;
		this->theta = (float)M_PI / 2.0f;
		this->cur_cmd++;

		break;

	case EXIT_LEFT:
		this->v = velocity;
		if (this->x + w / 2 <= p[i].x) {
			this->cur_cmd++;
			this->alive = false;
			this->endMotion = true;
			StageM::alives--;
		}
		break;
	case EXIT_RIGHT:
		this->v = velocity;
		if (this->x - w / 2 >= p[i].x) {
			this->cur_cmd++;
			this->alive = false;
			this->endMotion = true;
			StageM::alives--;
		}
		break;

	case EXIT_TOP:
		this->v = velocity;
		if (this->y - h / 2 <= p[i].y) {
			this->cur_cmd++;
			this->alive = false;
			this->endMotion = true;
			StageM::alives--;
		}
		break;


	case PULLROCKET:
		v = 0.0f;
		pullRocket(this);
		return;
		break;

	case WAIT:
		this->v = 0.0f;
		this->dt += p[i].frames;
		if (this->dt >= p[i].max) {
			this->dt = 0;
			this->cur_cmd++;
		}


		break;
	case TRANSLATE_TO:
		this->v = velocity;

		if (this->v < 0) {
			if (this->x <= p[i].x) {
				this->cur_cmd++;
			}
		}
		else {
			if (this->x >= p[i].x) {
				this->cur_cmd++;
			}
		}

		break;

	case TRANSLATE:
		this->v = velocity;
		this->dt += this->v;

		if (this->v < 0) {
			if (this->dt <= p[i].frames) {
				this->dt = 0;
				this->cur_cmd++;
			}
		}
		else {

			if (this->dt >= p[i].frames) {
				this->dt = 0;
				this->cur_cmd++;
			}
		}
		break;


	case TRANSLATE_TO_Y:
		this->v = velocity;

		if (this->v < 0) {
			if (this->y <= p[i].y) {
				this->cur_cmd++;
			}
		}
		else {
			if (this->y >= p[i].y) {
				this->cur_cmd++;
			}
		}
		break;


	case ROTATE:
		this->v = velocity;

		if(p[i].v != 0){
			this->dtheta += p[i].theta + (accel / p[i].v)*p[i].theta;
			this->theta += p[i].theta + (accel / p[i].v)*p[i].theta;
		}
		else {
			this->dtheta += p[i].theta;
			this->theta += p[i].theta;
		}

		if (p[i].max < 0) {
			if (this->dtheta <= p[i].max) {
				this->theta -= this->dtheta - p[i].max;
				this->dtheta = 0;
				this->cur_cmd++;
			}
		}
		else {
			if (this->dtheta >= p[i].max) {
				this->theta -= this->dtheta - p[i].max;
				this->dtheta = 0;
				this->cur_cmd++;
			}
		}

		break;


		//Only for Ships
	case FIND_PATH:


		this->v = velocity;

		//Get goal slot coords
		float xp = StageM::slots[slot].x;
		float yp = StageM::slots[slot].y;


		if (this->type == ROCKET) {
			yp -= 40.0f;
		}

		//find distance and angle between object and goal
		float distance = Distance(xp, yp, x, y);


		if(theta != targetTheta){
			targetTheta = atan2f(yp - this->y, xp - this->x);
		}



		//find critical theta
		dtheta = (std::abs(CalcShortestRot(theta, targetTheta)) * 180.0f /(float)M_PI) / distance / (float)M_PI * 2.0f;


		float ang1 = theta * 180.0f / (float)M_PI;
		float ang2 = targetTheta * 180.0f / (float)M_PI;

		if (ang1 < 0)ang1 += 360;
		if (ang2 < 0)ang2 += 360;


		float dir = CalcShortestRot(theta, targetTheta);

		if(ang1 == ang2){
			dir = 0.0f;
		}

		if(dir != 0){
			if (dir > 0) {
				theta += dtheta;
				dir = CalcShortestRot(theta, targetTheta);
				if (dir < 0) {
					theta = targetTheta;
					break;
				}
			}

			else if (dir < 0) {
				theta -= dtheta;
				if (dir > 0) {
					theta = targetTheta;
					dir = CalcShortestRot(theta, targetTheta);
					if (dir > 0) {
						theta = targetTheta;
						break;
					}
				}
			}

		}


		if (distance - v <= 5.0f) {

			this->x = StageM::slots[slot].x;
			this->y = StageM::slots[slot].y;

			if (type == ROCKET) this->y -= 40.0f;
			else this->y = StageM::slots[slot].y;

			if (p[i].theta == -1) {
				this->theta = -(float)M_PI / 2.0f;
			}
			else {
				this->theta = (float)M_PI / 2.0f;
			}

			dtheta = 0.0f;
			this->cur_cmd++;
			this->v = 0.0f;
			targetTheta = 0.0f;

		}

		break;
	}


	this->cosine = cos(this->theta);
	this->sine = sin(this->theta);
	this->x = (this->v * this->cosine) + this->x;
	this->y = (this->v * this->sine) + this->y;

	//std::cout << theta * 180.0f / (float)M_PI << std::endl;

	if (this->cur_cmd >= (int)p.size()) {

		this->endPattern = true;
		patternQueuePos++;

		if (patternQueuePos >= (int)PatternQueue.size()) {

			this->clearPatternQueue();
			this->endMotion = true;
			this->v = 0.0f;

		}
		else {
			cur_cmd = 0;
		}
	}


}

void GameObject::setPatternQueue(PATTERNQUEUE &patternQueue) {
	this->PatternQueue = patternQueue;
	this->patternQueuePos = 0;
	this->cur_pattern = this->PatternQueue[0];
	this->cur_cmd = 0;
}

void GameObject::clearPatternQueue()
{
	this->PatternQueue.clear();
	this->cur_pattern.clear();
	this->cur_cmd = 0;
	this->patternQueuePos = 0;

}
