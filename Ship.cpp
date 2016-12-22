#include "Ship.h"
#include "Game.h"
#include "Resources.h"
#include <time.h>


void Ship::Reset() {
	this->x = 0.0f;
	this->y = 0.0f;
	this->v = 0.0f;
	this->theta = 0.0f;
	this->cosine = 0.0f;
	this->sine = 0.0f;
	this->dt = 0;
	this->dtheta = 0;


	this->cur_cmd = 0;
	this->patternQueuePos = 0;
	this->texFrame = 0;
	this->PatternQueue.clear();
	this->cur_pattern.clear();
	this->alive = true;
	this->parked = false;
	this->attacking = false;
	this->contAttacking = false;

	//Default Tex
	this->tex = &Resources::crab;

	this->setPos(-100.0f, -100.0f);
	this->updateBounds();
	this->Bosshits = 2;
	this->mTimer.reset();
	this->shootTime.clear();
	//this->formation_offset = 0.0f;
}

void Ship::setPos(GLfloat x, GLfloat y) {
	this->x = x;
	this->y = y;
}

void Ship::distract() {
	if (this->parked) {
		this->x = StageM::slots[this->slot].x;
		this->y = StageM::slots[this->slot].y;
		updateBounds();
	}
}

void Ship::update() {



	if ((int)this->PatternQueue.size() > 0) {
		this->mTimer.start();

		for (int i = 0; i < (int)shootTime.size(); i++) {
			if (this->mTimer.acc == shootTime[i]) {
				this->shoot();
				shootTime.erase(shootTime.begin() + i);
				break;
			}
		}
	}

	if (attacking && endPattern) {

		//Updates & Point to appropriate Pattern
		if (type == BOSS && !contAttacking && patternQueuePos == 2) {
			patternQueuePos = 3;
		}
		if (type == BOSS && contAttacking && patternQueuePos == 3) {
			patternQueuePos = 1;
		}

		//shoot times
		if ((type == BOSS  || type == CRAB) && contAttacking  && mTimer.acc > 180) {

			this->mTimer.reset();
			this->newRandomShots(1, 50);
		}

		if (type == CRAB && !contAttacking && patternQueuePos == 2) {
			patternQueuePos = 3;
		}
		if (type == CRAB && contAttacking && patternQueuePos == 3) {
			patternQueuePos = 1;
		}

		if (type == FLY && !contAttacking) {

			if (patternQueuePos == 3) {
				patternQueuePos = 1;
			}
			else if (patternQueuePos == 2) {
				patternQueuePos = 3;
			}

		}
		if (type == FLY && contAttacking && patternQueuePos == 3) {
			patternQueuePos = 1;
		}

		if (type == FLY && contAttacking && patternQueuePos == 2) {
			this->mTimer.reset();
			this->shootTime.push_back(80);
		}

		endPattern = false;
	}



	if(this->endMotion){

		//intro check
		if (StageM::state == 0) {
			StageM::parkedElements++;
			this->endMotion = false;
			this->parked = true;


			if (StageM::parkedElements == 40) {
				StageM::runIntro(true);

				if(!StageM::bonusStage){
					StageM::state = 1;
				}
			}
		}

		this->parked = true;
		this->attacking = false;
		this->bossoneAttack = false;
		this->endMotion = false;
		this->bonus = 0;
		this->mTimer.reset();
		if (this->rocket != nullptr) this->rocket->attacking = false;
	}

	if ((int)this->PatternQueue.size() > 0) {
		updatePos();
	}

	updateBounds();
}


void Ship::draw() {


	float interpolationX = (abs(this->v) * this->cosine) * CCFG::interpolation;
	float interpolationY = (abs(this->v) * this->sine) * CCFG::interpolation;



	this->tex->renderFrame(texFrame, x + interpolationX, y + interpolationY, this->theta * (GLfloat)(180 / M_PI) + 90.0f);


	/*
	glBegin(GL_LINE_STRIP);
	glVertex2f(this->leftBound, this->bottomBound);
	glVertex2f(this->rightBound, this->bottomBound);
	glVertex2f(this->rightBound, this->topBound);
	glVertex2f(this->leftBound, this->topBound);
	glVertex2f(this->leftBound, this->bottomBound);
	glEnd();
	*/

}

void Ship::newRandomShots(int startRange , int endRange) {

	srand((int)time(0));

	int shots = rand() % 3;
	if (StageM::stage == 5) shots += 1;

	if (shots > 0) {
		for (int i = 0; i < shots; i++) {
			int t = startRange + rand() % endRange;
			this->shootTime.push_back(t);
		}
	}

}

bool Ship::attack(bool bossAttack, int dir, bool pullRocket)
{
	if (this->attacking || !this->alive) return false;

	if ((int)this->PatternQueue.size() == 0) {

		//Fly Attack
		if (this->type == FLY) {
			if (this->x > 335) {
				this->setPatternQueue(Elements::patterns.FlyAttackRight);
			}
			else if (this->x < 335) {
				this->setPatternQueue(Elements::patterns.FlyAttackLeft);
			}
		}

		//Crab Attack
		if (this->type == CRAB) {

			if (bossAttack) {
				if(dir == 0) this->setPatternQueue(Elements::patterns.BossAttackLeft);
				else this->setPatternQueue(Elements::patterns.BossAttackRight);
			}
			else {

				if (this->x > 335) {
					this->setPatternQueue(Elements::patterns.CrabAttackRight);
				}
				else if (this->x < 335) {
					this->setPatternQueue(Elements::patterns.CrabAttackLeft);
				}
			}
		}

		//BossAttack Attack
		if (this->type == BOSS) {
			if (this->x > 335) {
				if (pullRocket) {
					this->setPatternQueue(Elements::patterns.bossPullRocketAttackRightQ);
				}
				else {
					this->setPatternQueue(Elements::patterns.BossAttackRight);
				}
			}
			else if (this->x < 335) {
				if (pullRocket) {
					this->setPatternQueue(Elements::patterns.bossPullRocketAttackLeftQ);
				}
				else {
					this->setPatternQueue(Elements::patterns.BossAttackLeft);
				}
			}

			if (this->rocket != nullptr) {
				this->rocket->setPatternQueue(this->PatternQueue);
				this->rocket->attacking = true;
			}

		}


		this->attacking = true;
		this->parked = false;
		this->texFrame = 0;
		if (StageM::alives < StageM::MAX_GROUP_ATTACK && !bossAttack) contAttacking = true;
		if (this->rocket != nullptr) this->rocket->contAttacking = this->contAttacking;
		CCFG::Sounds->PlayChunk(CCFG::Sounds->attack);

		if (this->type == BOSS && Bosshits == 2) {
			this->bossoneAttack = true;
		}

	}


	//shoots
	this->newRandomShots(10, 30);


	return true;


}



void Ship::destroy(bool all) {

	if (this->type == BOSS) {
		Bosshits--;

		if (all) Bosshits = 0;
		if (Bosshits > 0) {
			CCFG::Sounds->PlayChunk(CCFG::Sounds->bossDestroy_1);
			this->tex = &Resources::bossBlue;
			return;
		}

	}

	this->alive = false;

	if (this->type == CRAB) {

		CCFG::Sounds->PlayChunk(CCFG::Sounds->crabDestroy);
	}
	else if (this->type == FLY) {

		CCFG::Sounds->PlayChunk(CCFG::Sounds->flyDestroy);
	}
	else if (this->type == BOSS) {
		CCFG::Sounds->PlayChunk(CCFG::Sounds->bossDestroy_2);
	}


	StageM::exp(this->x , this->y);

	//Score
	if (type == FLY) {
		if(parked) Elements::updateScore(50);
		else Elements::updateScore(100);
	}

	if (type == CRAB) {
		if (parked) Elements::updateScore(80);
		else Elements::updateScore(160);
	}

	if (type == BOSS) {

		int score = 0;
		if (bonus == 1)  score = 800;
		else if (bonus == 2)  score = 1600;
		else if (bossoneAttack || StageM::bonusStage) score = 400;
		else if (parked) score = 150;
		else score = 300;

		if (this->rocket != nullptr && !parked) score = 400;

		Elements::updateScore(score);

		if (score > 300) {
			float color[3] = { 1.0f,1.0f,1.0f };

			if (score == 1600) {
				color[0] = 0.847f;  color[1] = 0.847f; color[2] = 0.125f;
			}
			StageM::pushMiniScore(this->x, this->y, score, color);
		}

	}
	StageM::alives--;
	CCFG::hits++;

	if (StageM::bonusStage) {
		//this->parked = true;
		this->endMotion = true;
		StageM::bonusHits++;
		StageM::bonusGroupHits++;

		if (StageM::bonusGroupHits == 8) {
			float color[3];
			color[0] = 0.847f;  color[1] = 0.847f; color[2] = 0.125f;
			Elements::updateScore(1000);
			StageM::pushMiniScore(this->x, this->y, 1000, color);
			StageM::bonusGroupHits = 0;
		}


	}

	if (this->rocket != nullptr) {
		if(this->attacking){
			this->rocket->state = 2;
			this->rocket = nullptr;
		}
		else {
			this->rocket->state = 3;
		}
	}


}




void Ship::updateBounds() {
	leftBound = x - tex->cellWidth/2.0f;
	rightBound = x + tex->cellWidth / 2.0f;
	topBound = y - tex->cellHeight / 2.0f;
	bottomBound = y + tex->cellHeight / 2.0f;
}


void Ship::shoot() {

	if (!this->alive) return;

	Bullet b = Bullet();
	b.x = this->x;
	b.y = this->y + 20.0f;

	b.v = 8.0f;

	float range = 120.0f;

	float dx = abs(Elements::rocket[0].x - this->x);

	//std::cout << dx << std::endl;

	float th = 0.0f;
	if (dx <= range) {
		th = atan2f(Elements::rocket[0].y - this->y, Elements::rocket[0].x - this->x);
	}
	else {
		if (Elements::rocket[0].x > this->x) {
			th = atan2f(Elements::rocket[0].y - this->y, (this->x + range) - this->x);
		}
		else {
			th = atan2f(Elements::rocket[0].y - this->y, (this->x - range) - this->x);
		}
	}


	b.theta = th;
	Elements::Shipsbullets.insert(Elements::Shipsbullets.begin(), b);
}


