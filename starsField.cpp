#include "starsField.h"
#include "physix.h"
#include <time.h>

bool StarsField::reverse = false;
bool StarsField::easeDown = false;

void  StarsField::initSpace() {

	GLfloat x;
	GLfloat y;
	GLfloat randSpeed;

	srand((unsigned int)time(NULL));
	revSpeed = 12.0f;
	for (int i = 0;i<200;i++) {
		x = RandomFloat(0, 800);
		y = RandomFloat(0, 600);

		randSpeed = getNewSpeed();
		star r = star(x, y, 2.0f, 2.0f);
		r.speedX = 0.0002f;
		r.speedY = randSpeed;
		r.setColor(0.6901f, 0.125f, 0.125f);
		starsField.push_back(r);

	}
}

void StarsField::Render() {
	for (unsigned int i = 0;i<starsField.size();i++) {
		//glDisable(GL_DEPTH);
		glClear(GL_DEPTH_BUFFER_BIT);
		starsField[i].draw();
		//
	}
}

float StarsField::getNewSpeed(){

    //return RandomFloat(0.09f, 0.80f);
    return RandomFloat(0.09f, 0.80f);

}

void StarsField::Update() {
	static Timer t;

	for (unsigned int i = 0;i < starsField.size();i++) {
		moveStarsfield(starsField[i]);
	}

	if (easeDown) {
		t.start();
		if (t.checkFrameEnd(100)) {
			revSpeed--;
			if (revSpeed == 0) {
				revSpeed = 12.0f;
				easeDown = false;
				reverse = false;
			}

			t.reset();

		}

	}
}

//starfield movement shape
void  StarsField::moveStarsfield(rect &star) {
	if (reverse) {
		star.y -= star.speedY * revSpeed;
	}
	else {
		star.y += star.speedY;
	}


	if (reverse) {
		if (star.vectorRight > 800 || star.vectorLeft < 0
			|| star.vectorTop < 0 || star.vectorBottom > 800) {

			star.x = RandomFloat(0, 800);
			star.y = RandomFloat(550, 600);

		}
		else {
			return;
		}

		return;

	}

	if (star.vectorRight > 800 || star.vectorLeft < 0
		|| star.vectorTop > 600 || star.vectorBottom < 0) {

		star.x = RandomFloat(0, 800);
		star.y = RandomFloat(0, 50);
	}
	else {
		return;
	}

	if (star.x == 0) star.x += 1.0f;
	if (star.y == 0) star.y += 1.0f;

	/*GLfloat theta = atan2(0.0f - star.y, 0.0f - star.x);
	GLfloat distance = Distance(star.x, star.y, 0.0f, 0.0f);

	distance += 0.00009f;

	GLfloat posX = (distance * cos(theta)) * -1;
	GLfloat posY = (distance * sin(theta)) * -1;


	star.x = posX;
	star.y = posY;
	*/


	star.speedY = getNewSpeed();

	if (reverse) {
		star.y -= star.speedY * revSpeed;
	}
	else {
		star.y += star.speedY;
	}




}
