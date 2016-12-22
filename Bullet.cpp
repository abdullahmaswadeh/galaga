#include "Bullet.h"
#include "Elements.h"
#include "Resources.h"


Bullet::Bullet() {
	x = 0;
	y = 0;
	w = (float)Resources::bulletTex.getWidth();
	h = (float)Resources::bulletTex.getHeight();
	this->tex = &Resources::bulletTex;
	this->v = -13.0f;
	this->type = BULLET;
	this->theta = 0.0f;
	this->tex->angle = 0.0f;


}

Bullet::~Bullet() {}

void Bullet::Update() {



	if(this->theta == 0.0f){
		this->y += (int)v;
	}
	else {
		//std::cout << theta * 180.0f / (float)M_PI << std::endl;
		if (fromRocket) {
			this->cosine = cos(this->theta - (float)M_PI/2.0f);
			this->sine = sin(this->theta - (float)M_PI / 2.0f);
		}
		else {
			this->cosine = cos(this->theta);
			this->sine = sin(this->theta);
		}

		this->x = (abs(this->v) * this->cosine) + this->x;
		this->y = (abs(this->v) * this->sine) + this->y;

	}
}

void Bullet::Render() {



	//interpolation


	float angle = theta;

	if (!fromRocket) {
		angle = (float)M_PI;
	}

	if (theta != 0.0f) {
		float interpolationX = (abs(this->v) * this->cosine) * CCFG::interpolation;
		float interpolationY = (abs(this->v) * this->sine) * CCFG::interpolation;
		tex->renderCenter(x + interpolationX, y + interpolationY, NULL, (angle * 180.0f / (float)M_PI));
	}
	else {
		tex->renderCenter(x, y  + v * CCFG::interpolation);
	}

}
