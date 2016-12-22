#include "physix.h"
#include "CFG.h"
#include "timer.h"
#include "Resources.h"
#include "Elements.h"
#include "StageM.h"
#include "starsField.h"

//Distance between two points
GLfloat Distance(GLfloat dX0, GLfloat dY0, GLfloat dX1, GLfloat dY1)
{
	return sqrt((dX1 - dX0)*(dX1 - dX0) + (dY1 - dY0)*(dY1 - dY0));
}

float RandomFloat(float a, float b) {
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}


// If the return value is positive, then rotate to the left. Else,
// rotate to the right.
float CalcShortestRot(float from, float to)
{
	// If from or to is a negative, we have to recalculate them.
	// For an example, if from = -45 then from(-45) + 360 = 315.
	if (from < 0) {
		from += 2.0f*(float)M_PI;
	}

	if (to < 0) {
		to += 2.0f*(float)M_PI;
	}

	// Do not rotate if from == to.
	if ((from == to ||
		from == 0) && (to == 2.0f*(float)M_PI ||
		from == 2.0f*(float)M_PI) && to == 0)
	{
		return 0;
	}

	// Pre-calculate left and right.
	float left = (2.0f*(float)M_PI - from) + to;
	float right = from - to;
	// If from < to, re-calculate left and right.
	if (from < to) {
		if (to > 0) {
			left = to - from;
			right = (2.0f*(float)M_PI - to) + from;
		}
		else {
			left = (2.0f*(float)M_PI - to) + from;
			right = to - from;
		}
	}

	// Determine the shortest direction.
	return ((left <= right) ? left : (right * -1));
}

// Call CalcShortestRot and check its return value.
// If CalcShortestRot returns a positive value, then this function
// will return true for left. Else, false for right.
bool CalcShortestRotDirection(float from, float to)
{
	// If the value is positive, return true (left).
	if (CalcShortestRot(from, to) >= 0.0f) {
		return true;
	}
	return false; // right
}


bool BulletShipCollision(Ship & ship, Bullet & b)
{
	if (b.x > ship.leftBound && b.x < ship.rightBound &&
		b.y < ship.bottomBound && b.y > ship.topBound
		) {

		unsigned char res[4];
		glReadBuffer(GL_FRONT);
		glReadPixels((int)b.x, (int)CCFG::SCREEN_HEIGHT - (int)b.y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &res);

		if (res[0] != 0) {
			return true;
		}
	}
	return false;
}


bool BulletRocketCollision(Rocket & r, Bullet & b)
{
	if (b.x > r.leftBound && b.x < r.rightBound &&
		b.y < r.bottomBound && b.y > r.topBound
		) {

		unsigned char res[4];
		glReadBuffer(GL_FRONT);
		glReadPixels((int)b.x, (int)CCFG::SCREEN_HEIGHT - (int)b.y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &res);

		if (res[0] != 0) {
			return true;
		}
	}
	return false;
}

//Rocket Collide with Rocket
bool R_RCollision(Rocket & r, Rocket & r2)
{
	if (r.leftBound <   r2.rightBound &&
		r.rightBound >  r2.leftBound &&
		r.topBound <    r2.bottomBound &&
		r.bottomBound > r2.topBound
		) {

		return true;
	}
	return false;
}

void pullRocket(GameObject *obj) {

	Ship *ship = static_cast<Ship*>(obj);
	Rocket *r = &Elements::rocket[0];

	static Timer pt;
	static int frame = 0;
	static int state = 0;
	bool static sound = false;
	pt.start();


	float pLeftX = ship->x - 80.0f;
	float pRightX = ship->x  + 75.0f;

	if (!ship->alive) state = 7;
	if (r->state == 0) state = 6;



	//init
	if (state == 0) {
		CCFG::Sounds->PlayMusic(CCFG::Sounds->pullRocket,0);
		StageM::pullR.x = ship->x - 2.0f;
		StageM::pullR.y = ship->y + ship->tex->cellHeight / 2.0f + 4.0f;
		StageM::pullR.frame = 0;
		StageM::pullR.render = true;
		state = 1;
	}

	//throw out waves
	if (state == 1) {
		if (pt.checkFrameLoopAll(1)) {
			if (frame < 19) {
				frame++;
			}
			else {
				state = 2;
				pt.reset();
			}
		}
	}

	if (state == 2) {
		//check collision
		if (r->rightBound > pLeftX && r->leftBound < pRightX) {
			CCFG::Sounds->stopChunks(CCFG::Sounds->pullRocket);
			CCFG::Sounds->PlayChunk(CCFG::Sounds->revolve);
			state = 3;
			StarsField::reverse = true;
			r->pulling = true;
			r->v = 0;
			StageM::state = 4;
		}

		if (pt.checkFrameEnd(3000)) state = 6;
	}

	//if rocket collide start pulling to ship
	if (state == 3) {
		float xpos = r->x;
		float velocity = 3.0f;

		if (r->x < ship->x) {
			xpos += velocity;
			if (xpos >= ship->x) r->x = ship->x;
			else r->x += velocity;
		} else if (r->x > ship->x) {
			xpos -= velocity;
			if (xpos <= ship->x) r->x = ship->x;
			else r->x -= velocity;
		}

		if (r->y <= (ship->y + 50.0f)) {
			r->captuered = true;
		}

		if (r->y > (ship->y + 45.0f)) {

			r->y -= 2.0f;
			r->theta += (float)M_PI / 8.0f;
		}
		else {

			r->theta = -(float)M_PI/2.0f;
			r->captuered = true;
			r->color[0] = 0.95f; r->color[1] = 0.125f; r->color[2] = 0.125f;
			pt.reset();
			CCFG::Sounds->StopMusic();
			StageM::parkAll();
			state = 4;
			ship->rocket = r;
			r->capShip = ship;

		}

		r->updateBounds();
	}

	if (state == 4) {


		if (pt.checkFrameCap(400, 2300)) {
			Elements::FighterCapture = true;
		}



		if (pt.checkFrameEnd(700)) {
			if (!sound) {
				CCFG::Sounds->PlayMusic(CCFG::Sounds->pull2);
				sound = true;
			}
		}

		if (pt.checkFrameEnd(2300)) {
			Elements::FighterCapture = false;
			state = 5;
		}

		if (pt.checkFrameLoopAll(1)) {
			if (frame > -1) {
				frame--;
			}
			else {
				StageM::pullR.render = false;
			}
		}
	}

	//if captured pull up to slot
	if (state == 5) {
		ship->PatternQueue.push_back(Elements::patterns.findPath2);
		ship->cur_cmd++;

		StageM::state = 4;
		r->slot = ship->slot;
		r->setPatternQueue(Elements::patterns.rocketMoveToSlot);
		StarsField::easeDown = true;
		Elements::SwapRockets();
		Elements::state = 4;
		ship->rocket = &Elements::rocket[1];
		Elements::rocket[0].capShip = nullptr;
		Elements::rocket[1].capShip = ship;

		StageM::rocketPullAttack = false;

		ship = nullptr;
		r = nullptr;
		frame = 0;
		state = 0;
		pt.reset();
		sound = false;

	}

	//If rocket never approches
	if (state == 6) {
		if (frame > -1) {
			frame--;
		} else {
			ship->clearPatternQueue();

			ship->PatternQueue.push_back(Elements::patterns.bossPullRocketPark);
			ship->PatternQueue.push_back(Elements::patterns.findPath_Rotate);
			ship->cur_cmd = 0;
			ship->patternQueuePos = 0;
			ship->cur_pattern = ship->PatternQueue[ship->patternQueuePos];
			StarsField::easeDown = true;

			if(r->state != 0){
				StageM::state = 1;
			}

			StageM::rocketPullAttack = false;

			ship = nullptr;
			r = nullptr;
			frame = 0;
			state = 0;
			pt.reset();
			sound = false;

		}
	}

	if (state == 7) {

		CCFG::Sounds->stopChunks(CCFG::Sounds->pullRocket);
		CCFG::Sounds->stopChunks(CCFG::Sounds->revolve);

		StageM::pullR.frame = -1;
		StageM::pullR.render = false;

		if (r->y == 545.0f) {
			ship->PatternQueue.push_back(Elements::patterns.findPath2);
			ship->cur_cmd++;
			state = 0;
			StarsField::easeDown = true;
		}
		else {
			r->y+= 3.0f;
			r->theta += (float)M_PI/10.0f;
			if (r->y >= 545.0f) {
				r->theta = 0.0f;
				r->y = 545.0f;
				r->captuered = false;
				r->pulling = false;
				r->enabled = true;
				StageM::state = 1;
				StageM::rocketPullAttack = false;
				pt.reset();
				state = 0;
				frame = 0;
				sound = false;
			}

			r->updateBounds();
		}

		StarsField::easeDown = true;


	}

	if(frame > -1){
		StageM::pullR.frame = frame;
	}
}



void DrawPulling(int frame, float cx, float cy)
{
	float ypos = 0;
	float cone = 0.0f;
	int color = 0;

	for(int i = 0; i < frame; i++){

		if (color > 2) color = 0;
		DrawArc(cx, cy + ypos  , (float)i * 30.0f, 0, 30.0f + cone, 20, color);
		ypos += 9.0f;
		cone += 8.0f;

		color++;

	}

}



//Draw down arc
void DrawArc(float cx, float cy, float r, float start, float end, int num_segments, int color)
{

	float x = -abs(start - end) / 2.0f + 1.0f;
	float step = abs(start - end) / (float)num_segments;

	glPointSize(5);

	glPushMatrix();
	glTranslatef(cx, cy, 0.0f);
	glLineWidth(1.5f);
	glBegin(GL_LINE_STRIP);
	if (color == 1) glColor3f(0.662f, 0.125f, 0.125f);
	else if (color == 0) glColor3f(0.270f, 0.807f, 0.913f);
	else if (color == 2) glColor3f(0.090f, 0.090f, 0.662f);
	else glColor3f(1.0f,1.0f, 1.0f);

	for(int i =0; i < num_segments; i++){
		glVertex2f(x, -(x*x)/r);
		x += step;
	}
	glEnd();
	glPopMatrix();

}

void releaseRocket() {

	static Timer rt;
	rt.start();

	static int state = 0;

	StageM::state = 4;
	Rocket *r = nullptr;
	Rocket *r2 = nullptr;

	r = &Elements::rocket[1];
	r2 = &Elements::rocket[0];

	// :(
	Elements::state = 6;

	if((int)r->PatternQueue.size() > 0){
		r->clearPatternQueue();
	}

	if (state == 0) {

		r->v = 0.0f;
		r->color[0] = 1.0f;
		r->color[1] = 1.0f;
		r->color[2] = 1.0f;
		CCFG::Sounds->PlayMusic(CCFG::Sounds->pull2);
		state = 1;
		StageM::parkAll();
	}

	if (state == 1) {
		r->theta += (float)M_PI / 7.0f;

		if (!rt.checkFrameEnd(2000)) return;


		CCFG::controlsEnabled = false;
		r2->v = 0.0f;

		float x = (GLfloat)(CCFG::SCREEN_WIDTH / 2) - 100.0f - r2->tex->cellWidth / 2.0f - 1.0f;


		if (r2->x > x) {
			r2->x -= 2.0f;
			if (r2->x <= x) r2->x = x;
		}
		else if (r2->x < x) {
			r2->x += 2.0f;
			if (r2->x >= x) r2->x = x;
		}

		if (r2->x == x) {
			state = 2;
			r->theta = -(float)M_PI / 2.0f;
		}

	}

	if (state == 2) {
		float x2 = (GLfloat)(CCFG::SCREEN_WIDTH / 2) - 100.0f + r->tex->cellWidth / 2.0f - 1.0f;

		if (r->x < x2) {
			r->x += 2.0f;

			if (r->x > x2) {
				r->x = x2;
			}
		}

		if (r->x > x2) {
			r->x -= 2.0f;

			if (r->x < x2) {
				r->x = x2;
			}
		}

		if (r->x == x2) {
			state = 3;
		}



	}


	if (state == 3) {
		if (r->y < 545.0f) {
			r->y += 2.0f;
		}

		if (r->y > 545.0f) {
			r->y = 545.0f;
			state = 4;
		}
	}

	if (state == 4) {

		for (int i = 0; i < 2; i++) {

			if (!Elements::rocket[i].enabled) continue;

			Elements::rocket[i].capShip = nullptr;
			Elements::rocket[i].captuered = false;
			Elements::rocket[i].theta = 0.0f;
			Elements::rocket[i].v = Elements::rocket[i].speedX;
			Elements::rocket[i].pulling = false;
			Elements::rocket[i].enabled = true;
			Elements::rocket[i].attacking = false;
			Elements::rocket[i].contAttacking = false;
			Elements::rocket[i].updateBounds();
			Elements::rocket[i].updateMovementBounds();
			Elements::rocket[i].state = 1;

		}

		if(Elements::rocket[0].enabled){
			Elements::RocketsNum = 2;
			Elements::rocket[0].updateMovementBounds();
			Elements::rocket[1].updateMovementBounds();
		}
		else {

			Elements::SwapRockets();


			Elements::rocket[0].enabled = true;
			Elements::state = 6;
			CCFG::Sounds->volumeUP();
			Elements::rocketInitiated = true;
			Elements::rocket[1].enabled = false;
			Elements::RocketsNum = 1;
		}




		state = 0;

		r = nullptr;
		r2 = nullptr;

		CCFG::controlsEnabled = true;
		rt.reset();
		StageM::state = 1;




	}




}

void dumpRocket(bool reset) {
	static Timer dt;
	dt.start();
	static int state = 0;
	Rocket *r = &Elements::rocket[1];


	if (reset) {
		dt.reset();
		state = 0;
		Ship *ship = static_cast<Ship*>(r->capShip);
		ship->rocket = nullptr;
		r->capShip = nullptr;
		return;
	}

	//if destroyed
	if (!r->enabled) state = 2;

	if (dt.checkFrameEnd(1000) && state == 0) {
		if (r->capShip->slot == 0 || r->capShip->slot == 1) {
			r->setPatternQueue(Elements::patterns.BossAttackLeft);
		}
		else {
			r->setPatternQueue(Elements::patterns.BossAttackRight);
		}


		state = 1;

	}

	if (state == 1) {

		r->updatePos();
		r->updateBounds();

		if (r->y > CCFG::SCREEN_HEIGHT) {
			r->reset();

			dt.reset();
			state = 0;
			r = nullptr;
		}

	}

	if (state == 2) {
		dt.reset();
		state = 0;
		r->reset();
		r->state = 0;
		r = nullptr;
	}


}

float posCenter(Text2D &txt, bool nav) {

	float posX = CCFG::SCREEN_WIDTH / 2.0f - txt.sFont->w/2.0f;
	if (nav) posX -= 85.0f;
	return posX;

}

