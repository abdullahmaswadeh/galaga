#include "Rocket.h"
#include "Core.h"
#include "CFG.h"
#include "Resources.h"
#include "physix.h"

void Rocket::init() {

	speedX = 4.50f;

	w = (float)Resources::rocket.getWidth();
	h = (float)Resources::rocket.getHeight();
	y = 545.0f;
	v = 0.0f;
	boundLeft = 25.0f;
	boundRight = 620.0f;
	
	this->type = ROCKET;
	

	state = 1;
	
	this->tex = &Resources::rocket;
	this->enabled = true;

	setCenterPos(); 

}



void Rocket::update() {
	static Timer t;
	t.start();
	
	if (state == 2) {
		releaseRocket();
		return;
	}

	if (state == 3) {
		dumpRocket();
		return;
	}

	if ((int)this->PatternQueue.size() > 0) {

		//if Rocket was captured
		if (attacking) {

			//Updates & Point to appropriate Pattern
			if (!contAttacking && patternQueuePos == 2) {
				patternQueuePos = 3;
			}
			if (contAttacking && patternQueuePos == 3) {
				patternQueuePos = 1;
			}
		}

		updatePos();
		updateBounds();
		return;
	}


	if (!enabled || pulling || captuered) return;

	
	

	GLfloat posx = x;
	if (CCore::keyRight && state == 1) {
		posx += speedX;
		v = speedX;
		
		if ((posx + w/2.0f) >= boundRight) {
			posx = boundRight - w/2.0f;
			v = 0.0f;
		}
		x = posx;

		updateBounds();
	}


	if (CCore::keyLeft && state == 1) {
		posx -= speedX;
		v = -speedX;
		if (posx - w/2.0f <= boundLeft) {
			posx = boundLeft + w / 2.0f;
			v = 0.0f;
		}
		x = posx;

		updateBounds();
	}

}




void Rocket::render() {

	//Render Rocket
	if (this->captuered) {
		float interpolationX = (abs(this->v) * this->cosine) * CCFG::interpolation;
		float interpolationY = (abs(this->v) * this->sine) * CCFG::interpolation;

		this->tex->renderCenter(x + interpolationX, y + interpolationY, this->color , this->theta * (GLfloat)(180 / M_PI) + 90.0f);

	}
	else {
		if (!CCore::keyLeft && !CCore::keyRight) v = 0.0f;
		tex->renderCenter(x + (v * CCFG::interpolation), y, color, (theta * 180.0f / (float)M_PI));
	}
	
	//bounding Box
	/*
	glBegin(GL_LINE_STRIP);
		if (this == &Elements::rocket[0]) glColor3f(0.0f, 1.0f, 0.0f);
		if (this == &Elements::rocket[1]) glColor3f(0.0f, 0.0f, 1.0f);
		glVertex2f(this->leftBound, this->bottomBound);
		glVertex2f(this->rightBound, this->bottomBound);
		glVertex2f(this->rightBound, this->topBound);
		glVertex2f(this->leftBound, this->topBound);
		glVertex2f(this->leftBound, this->bottomBound);
	glEnd();
	*/
	
	

}


void Rocket::updateBounds() {
	leftBound = x - this->w / 2.0f;
	rightBound = x + w / 2.0f;
	topBound = y - this->h / 2.0f;
	bottomBound = y + h / 2.0f;
}

void Rocket::destroy(bool byR) {

	if (byR) {
		
		StageM::exp(x, y, &Resources::exp);
		CCFG::Sounds->PlayMusic(CCFG::Sounds->captive);

		//to reset dump rocket static vars and cont
		dumpRocket(true);
		
		float c[3] = { 0.0f, 0.392f, 0.0f };
		Elements::updateScore(1000);
		StageM::pushMiniScore(this->x, this->y, 1000, c);
		StageM::rocketPullAttack = false;
		StageM::state = 1;
		StageM::attTimer.reset();
		this->reset();

		
		this->enabled = false;

		return;
	}

	StageM::exp(x, y, &Resources::expRocket);

	CCFG::Sounds->volumeDown();
	CCFG::Sounds->PlayChunk(CCFG::Sounds->rocketexp);

	this->reset();

	
	Elements::state = 4;
	
	this->state = 0;
	this->enabled = false;
	

}

void Rocket::shootBullet() {

	if (this->captuered) return;


	Bullet b = Bullet();


	float cx = this->leftBound + this->w / 2.0f;
	float cy = this->topBound + this->h / 2.0f;

	b.fromRocket = true;
	if (this->theta != 0.0f) {
		b.theta = this->theta;
	}
	else {
		b.theta = 0.0f;
	}
	

	b.x = cx;
	b.y = cy;


	Elements::bullets.insert(Elements::bullets.begin(), b);


}

void Rocket::updateMovementBounds()
{

	//boundLeft = 25.0f;
	//boundRight = 620.0f;

	if (Elements::RocketsNum == 2) {
		if (this == &Elements::rocket[0]) {
			boundRight = 620.0f - tex->cellWidth + 1.0f;
		}
		else {
			boundLeft = 25.0f + tex->cellWidth - 1.0f;
		}
	} else {
		boundLeft = 25.0f;
		boundRight = 620.0f;
	}
}


void Rocket::setCenterPos() {

	x = (GLfloat)(CCFG::SCREEN_WIDTH / 2) - 100;
	

	if (Elements::RocketsNum == 2) {
		if (this == &Elements::rocket[0]) {
			x -= tex->cellWidth / 2.0f - 1.0f;
		}
		else {
			x += tex->cellWidth / 2.0f - 1.0f;
		}
	}

	updateBounds();
	updateMovementBounds();

}

void Rocket::reset() {
	this->init();
	this->enabled = false;
	this->captuered = false;
	this->attacking = false;
	this->capShip = nullptr;
	this->pulling = false;
	this->color[0] = 1.0f;
	this->color[1] = 1.0f;
	this->color[2] = 1.0f;
	this->contAttacking = false;
	this->clearPatternQueue();
	this->theta = 0.0f;
}