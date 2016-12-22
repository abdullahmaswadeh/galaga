#include "StageM.h"
#include "Game.h"
#include "Formations.h"
#include <algorithm>
#include "stages.h"
#include "physix.h"

//init Vars
StageM::Slot StageM::slots[numShips] = {};
Ship StageM::ships[numShips] = {};
int StageM::state = 0;
int StageM::stage = 1;
int StageM::parkedElements = 0;
std::vector<StageM::Aexp> StageM::exps;
ATTACKINGPATTERNQUEUE *StageM::ATPQ;
Timer StageM::attTimer;
int StageM::alives = 40; //40;
int StageM::MAX_GROUP_ATTACK = 8;
std::vector<StageM::miniScore> StageM::miniScores;
StageM::pullRE StageM::pullR;
bool StageM::rocketPullAttack = false;
bool StageM::bonusStage = false;
int StageM::bonusHits  = 0;
int StageM::bonusGroupHits = 0;

//Init Patterns and Stage
void StageM::Init() {

	//Init Ships
	for (int i = 0; i < numShips; i++) {
		ships[i].Reset();
	}

	//Init Slots
	initSlots();

	//Init and load Stage
	stages::init();
	nextStage();


	//dummy
	if (false) {

		for (int i = 0; i < numShips; i++) {

			ships[i].x = slots[i].x;
			ships[i].y = slots[i].y;
			ships[i].slot = i;



			if (i < 4) {
				ships[i].tex = &Resources::boss;
				ships[i].type = BOSS;
			}

			if (i < 20 && i > 3) {
				ships[i].tex = &Resources::crab;
				ships[i].type = CRAB;
			}

			if (i < 40 && i > 19) {
				ships[i].tex = &Resources::fly;
				ships[i].type = FLY;
			}

			ships[i].alive = false;
			ships[i].parked = true;
			ships[i].theta = -(float)M_PI / 2;
			state = 1;
		}
		state = 1;
		ATPQ = &Elements::patterns.at1;
		ships[0].alive = true;
		//ships[31].alive = true;
		//ships[38].alive = true;
		//ships[39].alive = true;

	}
}

//Init Slots Locations
void StageM::initSlots() {

	float hSpace = 45.0f;
	float vSpace = 40.0f;

	float startPosX = 246.0f;
	float startPosY = 103.0f;

	float curPosX = startPosX;
	float curPosY = startPosY;

	//Init Slots
	for (int i = 0; i < numShips; i++) {

		Slot slot;

		if (i == 4 || i == 12) {
			curPosY += vSpace;
			curPosX = startPosX - hSpace * 2;
		}

		if (i == 20 || i == 30) {
			curPosY += vSpace;
			curPosX = startPosX - hSpace * 3;
		}


		slot.x = curPosX;
		slot.y = curPosY;


		StageM::slots[i] = slot;

		curPosX += hSpace;

	}



	//Assign Permenant Slot For Each Ship
	StageM::ships[0].slot = 7;
	StageM::ships[1].slot = 8;
	StageM::ships[2].slot = 15;
	StageM::ships[3].slot = 16;

	StageM::ships[4].slot = 24;
	StageM::ships[5].slot = 25;
	StageM::ships[6].slot = 34;
	StageM::ships[7].slot = 35;


	StageM::ships[8].slot = 0;
	StageM::ships[9].slot = 6;
	StageM::ships[10].slot = 1;
	StageM::ships[11].slot = 9;
	StageM::ships[12].slot = 2;
	StageM::ships[13].slot = 14;
	StageM::ships[14].slot = 3;
	StageM::ships[15].slot = 17;


	StageM::ships[16].slot = 5;
	StageM::ships[17].slot = 10;
	StageM::ships[18].slot = 4;
	StageM::ships[19].slot = 11;
	StageM::ships[20].slot = 13;
	StageM::ships[21].slot = 18;
	StageM::ships[22].slot = 12;
	StageM::ships[23].slot = 19;


	StageM::ships[24].slot = 23;
	StageM::ships[25].slot = 26;
	StageM::ships[26].slot = 22;
	StageM::ships[27].slot = 27;
	StageM::ships[28].slot = 33;
	StageM::ships[29].slot = 36;
	StageM::ships[30].slot = 32;
	StageM::ships[31].slot = 37;


	StageM::ships[32].slot = 21;
	StageM::ships[33].slot = 28;
	StageM::ships[34].slot = 20;
	StageM::ships[35].slot = 29;
	StageM::ships[36].slot = 31;
	StageM::ships[37].slot = 38;
	StageM::ships[38].slot = 30;
	StageM::ships[39].slot = 39;
}

//Animate Texures
void StageM::texAnimate() {

	static Timer j;
	j.start();

	static int Crabtxframe = 0;
	static int Bosstxframe = 0;



	//Crab
	if (j.checkFrameLoopAll(40)) {


		Crabtxframe = (Crabtxframe == 0) ? 1 : 0;
		for (int i = 0; i < numShips; i++) {
			if (ships[i].parked && (ships[i].type == CRAB || ships[i].type == FLY)) {
				ships[i].texFrame = Crabtxframe;
			}
		}
	}

	//Boss
	if (j.checkFrameLoopAll(60)) {
		Bosstxframe = (Bosstxframe == 0) ? 1 : 0;
		for (int i = 0; i < numShips; i++) {
			if (ships[i].parked && ships[i].type == BOSS) {
				ships[i].texFrame = Bosstxframe;
			}
		}
	}

}

bool StageM::runIntro(bool reset) {

	static Timer t = Timer();
	static unsigned short grp = 1;

	if (reset) {
		t.reset();
		grp = 1;
		return false;
	}

	if (state > 0) return false;





	int delay = 200;

	//group 1
	if (grp == 1 && parkedElements == 8) {
		t.start();

		if(t.checkFrameEnd(delay)){
			grp = 2;
			t.reset();
		}

		if (Elements::state == 4) t.reset();
		StageM::bonusGroupHits = 0;
	}

	if (grp == 2 && parkedElements == 16) {
		t.start();

		if (t.checkFrameEnd(delay)) {
			grp = 3;
			t.reset();
		}

		if (Elements::state == 4) t.reset();
		StageM::bonusGroupHits = 0;
	}

	if (grp == 3 && parkedElements == 24) {
		t.start();

		if (t.checkFrameEnd(delay)) {
			grp = 4;
			t.reset();
		}

		if (Elements::state == 4) t.reset();
		StageM::bonusGroupHits = 0;
	}


	if (grp == 4 && parkedElements == 32) {
		t.start();

		if (t.checkFrameEnd(delay)) {
			grp = 5;
			t.reset();
		}

		if (Elements::state == 4) t.reset();
		StageM::bonusGroupHits = 0;
	}



	for (int i = 0; i < numShips; i++) {

		if (ships[i].parked) {
			continue;
		}


		if (grp == 1 && i < 8) {
			ships[i].update();
		}

		if (grp == 2 && i < 16) {
			ships[i].update();
		}

		if (grp == 3 && i < 24) {
			ships[i].update();
		}

		if (grp == 4 && i < 32) {
			ships[i].update();
		}

		if (grp == 5 && i < 40) {
			ships[i].update();
		}



	}



	return true;

}

//Simulate Same distracting as Game
void StageM::distract() {
	static int count = 0;
	int space = 3;


	if (count == 0 || count == 1 || count == 4 || count == 5 || count == 8 || count == 9) {
		slots[11].x += space;
		slots[19].x += space;
		slots[29].x += 5;
		slots[39].x += 5;
		slots[28].x += space;
		slots[38].x += space;

		slots[4].x -= space;
		slots[12].x -= space;
		slots[20].x -= 5;
		slots[30].x -= 5;
		slots[21].x -= space;
		slots[31].x -= space;

		//Vertically
		for (int i = 20; i < 30; i++) {
			slots[i].y += 1;

		}

		for (int i = 30; i < 40; i++) {
			slots[i].y += 2;

		}


	}

	if (count == 12 || count == 13 || count == 16 || count == 17 || count == 20 || count == 21) {
		slots[11].x -= space;
		slots[19].x -= space;
		slots[29].x -= 5;
		slots[39].x -= 5;
		slots[28].x -= space;
		slots[38].x -= space;

		slots[4].x += space;
		slots[12].x += space;
		slots[20].x += 5;
		slots[30].x += 5;
		slots[21].x += space;
		slots[31].x += space;

		for (int i = 20; i < 30; i++) {
			slots[i].y -= 1;

		}

		for (int i = 30; i < 40; i++) {
			slots[i].y -= 2;

		}
	}

	if (count == 0 || count == 3 || count == 6 || count == 9) {
		slots[10].x += space;
		slots[18].x += space;
		slots[27].x += space;
		slots[37].x += space;


		slots[5].x -= space;
		slots[13].x -= space;
		slots[22].x -= space;
		slots[32].x -= space;

	}


	if (count == 12 || count == 15 || count == 18 || count == 21) {
		slots[10].x -= space;
		slots[18].x -= space;
		slots[27].x -= space;
		slots[37].x -= space;


		slots[5].x += space;
		slots[13].x += space;
		slots[22].x += space;
		slots[32].x += space;

	}

	if (count == 3 || count == 9) {
		slots[9].x += space;
		slots[17].x += space;
		slots[26].x += space;
		slots[36].x += space;


		slots[6].x -= space;
		slots[14].x -= space;
		slots[23].x -= space;
		slots[33].x -= space;

	}

	if (count == 15 || count == 21) {
		slots[9].x -= space;
		slots[17].x -= space;
		slots[26].x -= space;
		slots[36].x -= space;


		slots[6].x += space;
		slots[14].x += space;
		slots[23].x += space;
		slots[33].x += space;

	}

	if (count == 8) {
		slots[8].x += space;
		slots[16].x += space;
		slots[25].x += space;
		slots[35].x += space;

		slots[7].x -= space;
		slots[15].x -= space;
		slots[24].x -= space;
		slots[34].x -= space;
	}

	if (count == 20) {
		slots[8].x -= space;
		slots[16].x -= space;
		slots[35].x -= space;
		slots[25].x -= space;

		slots[7].x += space;
		slots[15].x += space;
		slots[24].x += space;
		slots[34].x += space;
	}


	count++;
	if (count > 23) count = 0;
}


void StageM::Update() {

	static Timer s;

	if (state != 3) {
		s.start();
	}


	if (alives == 0 && state !=4 && Elements::rocket[0].enabled) {

		if((int)Elements::Shipsbullets.size() == 0){

			state = 3;

			if(!bonusStage){

				if (stage == 5) {
					Elements::state = 7;
				} else {
					nextStage();
					Elements::state = 5;
				}

			} else {
				Elements::state = 8;
			}
		}
	}

	//Slots Movement
	if (s.checkFrameLoop(150)) {
		distract();
	}

	//Animate Ships textures
	texAnimate();

	//check collision
	checkCollision();

	//Update Explosions Frame
	UpdateExpsFrame();

	//Run Intro
	if (state == 0) {
		runIntro();
	}

	for (int i = 0; i < numShips; i++) {

		//Distract if ship is parked
		ships[i].distract();

		//Update ships
		if (ships[i].attacking == true) {
			ships[i].update();
		}
	}

	if (state == 1 && Elements::rocket[0].enabled) {
		attack();
	}

}

void StageM::exp(GLfloat x, GLfloat y, LTexture *tex) {
	Aexp ex;
	ex.tex = tex;
	ex.frame = 0;
	ex.x = x;
	ex.y = y;
	exps.push_back(ex);
}

void StageM::pushMiniScore(GLfloat x, GLfloat y, unsigned int val, float color[3])
{
	miniScore m;
	m.color[0] = color[0];
	m.color[1] = color[1];
	m.color[2] = color[2];
	m.value = val;
	m.x = x;
	m.y = y;

	miniScores.push_back(m);
}

void StageM::UpdateExpsFrame() {
	for (int j = 0; j < (int)exps.size(); j++) {

		exps[j].t.start();
		if (exps[j].t.checkFrameEnd(100)) {
			exps[j].frame++;
			exps[j].t.reset();
			if (exps[j].frame > exps[j].maxFrame) {
				try {
					exps.erase(exps.begin() + j);
				}
				catch (std::exception) {
					exps.clear();
				}
			}
		}

	}
}
void StageM::renderMiniScores() {

	for (int i = 0; i < (int)miniScores.size(); i++) {
		miniScores[i].t.start();

		Resources::miniScore.setText(std::to_string(miniScores[i].value));
		Resources::miniScore.x = miniScores[i].x - Resources::miniScore.sFont->w / 2.0f;
		Resources::miniScore.y = miniScores[i].y;
		Resources::miniScore.glcolor[0] = miniScores[i].color[0];
		Resources::miniScore.glcolor[1] = miniScores[i].color[1];
		Resources::miniScore.glcolor[2] = miniScores[i].color[2];
		Resources::miniScore.render();

		if (miniScores[i].t.checkFrameEnd(1500)) {
			miniScores.erase(miniScores.begin() + i);
		}
	}

}


void StageM::Draw() {

	//PullRocket
	if (pullR.render) {
		DrawPulling(pullR.frame, pullR.x, pullR.y);
	}

	//DrawPulling(0, 300, 300);

	for (int j = 0; j < (int)exps.size(); j++) {
		exps[j].tex->renderFrame(exps[j].frame, exps[j].x, exps[j].y);
	}

	for (int i = 0; i < numShips; i++) {
		if (ships[i].alive && !ships[i].attacking) {
			ships[i].draw();
		}
	}

	//Let Attacking element overlap others
	for (int i = 0; i < numShips; i++) {
		if (ships[i].alive && ships[i].attacking) {
			ships[i].draw();
		}
	}

	//Render small scores that appears on screen while fighting
	renderMiniScores();


	//Slots

	/*
	for (int i = 0; i < numShips; i++) {
		glPointSize(4);
		glColor3f(1, 1, 1);
		glBegin(GL_POINTS);

		glVertex2f(slots[i].x, slots[i].y);
		glEnd();
	}
	*/

}



void StageM::checkCollision() {



	for (int i = 0; i < numShips; i++) {

		if (!ships[i].alive) continue;

		//ships collision with Rocket Bullets
		if (Elements::bullets.size() > 0) {
			for (int x = 0; x < (int)Elements::bullets.size(); x++) {
				Bullet b = Elements::bullets[x];


				if (BulletShipCollision(ships[i], b)) {

					ships[i].destroy();

					//another check / if bullet hits two or more ships

					if(Elements::RocketsNum == 1){
						for (int f = 0; f < numShips; f++) {

							if (f == i || !ships[f].alive) continue;

							if (BulletShipCollision(ships[f], b)) {
								ships[f].destroy();
								break;
							}
						}
					}

						if(Elements::RocketsNum == 2){



							int s;
							if (x == 0 || x == 2) {
								s = x + 1;
							}
							else if(x == 1 || x == 3) {
								s = x - 1;
							}


							for (int j = 0; j < numShips; j++) {
								if (!ships[j].alive || j==i) continue;
								if (BulletShipCollision(ships[j], Elements::bullets[s])) {
									ships[j].destroy();
									break;
								}
							}

							if (s > x) {
								Elements::bullets.erase(Elements::bullets.begin() + s);
								Elements::bullets.erase(Elements::bullets.begin() + x);
							}
							else {
								Elements::bullets.erase(Elements::bullets.begin() + x);
								Elements::bullets.erase(Elements::bullets.begin() + s);
							}


						} else {
							//remove Bullet
							if ((int)Elements::bullets.size() > 1) {
								Elements::bullets.erase(Elements::bullets.begin() + x);
							}
							else if ((int)Elements::bullets.size() == 1) {
								Elements::bullets.erase(Elements::bullets.begin() + 0);
							}
						}

				}
			}
		}



		//Collision ship with Rocket or ship's bullets with rocket

		for (int z = 0; z < 2; z++) {
			if (Elements::rocket[z].state == 0 || Elements::rocket[z].pulling || !Elements::rocket[z].enabled || !CCFG::controlsEnabled) continue;

			if (!Elements::rocket[z].captuered) {

				//Ships Bullets with Rockets
				if ((int)Elements::Shipsbullets.size() > 0) {
					for (int k = 0; k < (int)Elements::Shipsbullets.size(); k++) {

						if (BulletRocketCollision(Elements::rocket[z], Elements::Shipsbullets[k])) {
							Elements::rocket[z].destroy();
							Elements::Shipsbullets.erase(Elements::Shipsbullets.begin() + k);
							parkAll();
							if(state != 0){
								state = 2;
							}
							attTimer.reset();
							break;
						}
					}
				}



				if (Elements::rocket[z].leftBound < ships[i].rightBound &&
					Elements::rocket[z].rightBound > ships[i].leftBound &&
					Elements::rocket[z].topBound < ships[i].bottomBound &&
					Elements::rocket[z].bottomBound > ships[i].topBound
					) {



					ships[i].destroy(true);
					Elements::rocket[z].destroy();
					parkAll();
					state = 2;
					attTimer.reset();
					break;
				}
			}
		}

	}


	if (Elements::rocket[1].captuered && Elements::rocket[1].enabled && Elements::rocket[1].state != 2) {
		if (Elements::bullets.size() > 0) {
			for (int x = 0; x < (int)Elements::bullets.size(); x++) {
				Bullet b = Elements::bullets[x];


				if (BulletRocketCollision(Elements::rocket[1], b)) {

					Elements::rocket[1].destroy(true);

					if ((int)Elements::bullets.size() > 1) {
						Elements::bullets.erase(Elements::bullets.begin() + x);
					}
					else if ((int)Elements::bullets.size() == 1) {
						Elements::bullets.erase(Elements::bullets.begin() + 0);
					}

					return;
				}
			}
		}

		if (R_RCollision(Elements::rocket[0], Elements::rocket[1])) {
			Elements::rocket[0].destroy();
			Elements::rocket[1].destroy(true);
			attTimer.reset();
			Elements::state = 4;
			StageM::state = 3;
		}


	}
}

void StageM::parkAll() {
	for (int i = 0; i < numShips; i++) {
		ships[i].contAttacking = false;
		if (ships[i].rocket != nullptr) ships[i].rocket->contAttacking = false;
	}
}
void StageM::attack() {

	attTimer.start();

	if (attTimer.delayed) {
		return;
	}


	if (!attTimer.checkFrameEnd(1000)) return;


	if (attackPos > (int)ATPQ->size() - 1) {
		attackPos = 0;
		attTimer.delay(100);
		std::random_shuffle(ATPQ->begin(), ATPQ->end());
		return;
	}



	int row = ATPQ->at(attackPos).row;
	bool groupAttack = ATPQ->at(attackPos).group;
	int direction = ATPQ->at(attackPos).direction;
	int index = 0;
	int i = 0;

	int delay = ATPQ->at(attackPos).delay;
	bool pullRocket = ATPQ->at(attackPos).pullRocket;


	if (row == 4) {
		i = (direction == 0) ? 30 : 39;
		while (i != 29 && i != 40) {

			int index = findBySlot(i);
			if (ships[index].attack()) break;

			if (direction == 0) i++;
			else i--;

			if (i == 29 || i == 40) delay = 0;
		}
	}

	if (row == 3) {
		i = (direction == 0) ? 20 : 29;
		while (i != 19 && i != 30) {

			index = findBySlot(i);
			if (ships[index].attack()) break;

			if (direction == 0) i++;
			else i--;
			if (i == 19 || i == 30) delay = 0;
		}
	}


	if (row == 2) {
		i = (direction == 0) ? 12 : 19;
		while (i != 11 && i != 20) {

			index = findBySlot(i);
			if (ships[index].attack()) break;

			if (direction == 0) i++;
			else i--;

			if (i == 11 || i == 20) delay = 0;
		}
	}



	if (row == 1) {
		i = (direction == 0) ? 4 : 11;
		while (i != 3 && i != 12) {

			index = findBySlot(i);
			if (ships[index].attack()) break;

			if (direction == 0) i++;
			else i--;

			if (i == 3 || i == 12) delay = 0;
		}
	}


	if (row == 0) {
		i = (direction == 0) ? 1 : 2;

		while (i != -1 && i != 4) {


			if (pullRocket) {
				if (Elements::rocket[0].captuered || Elements::rocket[1].captuered) {
					delay = 0;
					break;
				}

				if (rocketPullAttack || Elements::RocketsNum == 2) {
					delay = 0;
					break;
				}


			}

			index = findBySlot(i);

			if (ships[index].attack(false, 0, pullRocket)) {

				if (pullRocket == true) rocketPullAttack = true;

				if (groupAttack && StageM::alives > MAX_GROUP_ATTACK  && !rocketPullAttack) {
					if (i == 0 || i == 1) {
						if (ships[findBySlot(i + 6)].attack(true, 0)) ships[index].bonus += 1;
						if (ships[findBySlot(i + 7)].attack(true, 0)) ships[index].bonus += 1;

					}
					else {
						if (ships[findBySlot(i + 5)].attack(true, 1)) ships[index].bonus += 1;
						if (ships[findBySlot(i + 6)].attack(true, 1)) ships[index].bonus += 1;
					}
				}

				break;

			}


			if (direction == 0) i--;
			else i++;

			if (i == -1 || i == 4) delay = 0;
		}
	}


	if (alives < MAX_GROUP_ATTACK && delay > 0) delay = 80;

	if (stage == 5) delay = 20;


	if(delay > 0){
		attTimer.delay(delay);
	}
	attackPos++;

}

int StageM::findBySlot(int index) {

	for (int i = 0; i < numShips; i++) {
		if (ships[i].slot == index) {
			return i;
		}
	}

	return -1;
}


void StageM::nextStage() {


	alives = 40;
	parkedElements = 0;
	attTimer.reset();
	runIntro(true);

	bonusGroupHits = 0;
	bonusHits = 0;
	bonusStage = false;

	for (int i = 0; i < numShips; i++) ships[i].Reset();

	stages::loadStage(stage - 1);
	state = -1;
	Elements::state = 5;


}
