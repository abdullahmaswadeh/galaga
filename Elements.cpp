#include "Elements.h"
#include "Game.h"
#include "Core.h"
#include "Resources.h"
#include "physix.h"

Rocket Elements::rocket[2];
unsigned short Elements::RocketsNum = 1;
bool Elements::rocketInitiated = false;
std::vector<Bullet> Elements::bullets;
std::vector<Bullet> Elements::Shipsbullets;
unsigned int Elements::score = 0;
int Elements::state = 0;
Patterns Elements::patterns = Patterns();
bool Elements::FighterCapture = false;


/* ******************************************** */

void Elements::initElements() {
	Resources::initTextures();
	Resources::initFonts();
	patterns.initPatterns();


}

void Elements::renderStartScreen() {

	//Galaga
	Resources::bigTitle.render();

	//ScoreText
	Resources::scoreWord.render();

	//Score
	Resources::score.render();

	//HighScore Word
	Resources::HighScore.render();

	//HighScore Num
	Resources::hiScoreNum.render();

	//Push SpaceKey
	Resources::PushSpaceKey.render();

	//Namcot
	Resources::namcot.render();

	//Description
	Resources::desc1.render();
	Resources::desc2.render();

	//Copyrights sym
	Resources::cr_symbol.render(200, 440);
}


void Elements::initRightNav() {

	Resources::HighScore.setText("HIGH");
	Resources::HighScore.x = 640;
	Resources::HighScore.y = 60;

	Resources::scoreWord.x = Resources::HighScore.x + 25;
	Resources::scoreWord.y = 80;

	Resources::hiScoreNum.x = (Resources::scoreWord.x + Resources::scoreWord.sFont->w) - (Resources::hiScoreNum.sFont->w);
	Resources::hiScoreNum.y = 100;

	Resources::scoreWord2 = Resources::scoreWord;
	Resources::scoreWord2.x = Resources::HighScore.x;
	Resources::scoreWord2.y = 160;

	Resources::score.x = (Resources::scoreWord.x + Resources::scoreWord.sFont->w) - (Resources::score.sFont->w);
	Resources::score.y = 180;

}

void Elements::renderRightNav() {

	//BlackBox
	glDisable(GL_DEPTH_TEST);
	glBegin(GL_POLYGON);
	glColor3f(0, 0, 0);
	glVertex2f(630.0f, 000.0f);
	glVertex2f(800.0f, 000.0f);
	glVertex2f(800.0f, 600.0f);
	glVertex2f(630.0f, 600.0f);
	glEnd();
	glEnable(GL_DEPTH_TEST);

	//Right Bar Elements


	Resources::scoreWord.render();
	Resources::score.render();

	Resources::HighScore.render();
	Resources::hiScoreNum.render();

	if (Resources::scoreWord2.visible) {
		Resources::scoreWord2.render();
	}


	//Lives
	glColor3f(1, 1, 1);
	float x = Resources::HighScore.x;
	for (int i = 0; i < lives; i++) {
		Resources::rocket.render(x, 260.0f);
		x += Resources::rocket.getWidth() + 2.0f;
	}


	levels.renderLevels();


}

void Elements::updateLives() {
	if (lives >= Game::lives) {
		lives--;
	}
}

void Elements::showStageNum() {
	levels.reload();
}

void Elements::starterAnim() {
	static Timer starterTimer;
	starterTimer.start();

	//Render Game Start Text
	if (starterTimer.checkFrameCap(0, 7700)) {
		Resources::gameStart.render();
	}

	//Render Ready Text
	if (starterTimer.checkFrameCap(7700, 10000)) {
		Resources::readyWord.render();
	}

	//Remove Live from right Nav
	if (starterTimer.checkFrameEnd(10000)) {
		updateLives();
		if (!rocketInitiated) {
			initRockets();
			rocketInitiated = true;
		}
	}


	//Level Up !

	if (starterTimer.checkFrameEnd(11000)) {
		Game::gameState = 2;
		state = 6;
	}

}

void Elements::flashScore() {

	static Timer scoreTimer;
	scoreTimer.start();

	if (scoreTimer.newTime > 0 && scoreTimer.checkFrameLoop(500)) {
		if (Resources::scoreWord2.visible) {
			Resources::scoreWord2.visible = false;
		}
		else {
			Resources::scoreWord2.visible = true;
		}
	}
}

void Elements::Update() {

	if (state > 0) flashScore();

	if (state == 1) {
		initRightNav();

		CCFG::Sounds->PlayMusic(CCFG::Sounds->intro);
		state = 2;
		gameStarted = true;
	}

	if (state == 5) {
		nextStage();
	}

	//Move Rocket

	for (int i = 0; i < 2; i++) {
		rocket[i].update();
	}


	//Update Bullets

	if (CCore::spaceKey && rocketInitiated) {
		int max = 1;
		if (RocketsNum == 2) max = 2;
		if ((int)bullets.size() == max) {
			if (Distance(bullets[0].x, bullets[0].y, rocket[0].x, rocket[0].y)  > 200) {
				shoot();
			}
		}

		if ((int)bullets.size() == 0) {
			shoot();
		}

	}


	for (int i = 0; i < (int)bullets.size(); i++) {

		bullets[i].Update();


		if (bullets[i].y < 0 || bullets[i].y > CCFG::SCREEN_HEIGHT ||
			bullets[i].x < 0 || bullets[i].x > 630.0f) {
			bullets.erase(bullets.begin() + i);
		}
	}

	if ((int)Shipsbullets.size() > 0) {
		for (int i = 0; i < (int)Shipsbullets.size(); i++) {
			Shipsbullets[i].Update();
			if (Shipsbullets[i].y < 0 || Shipsbullets[i].y > CCFG::SCREEN_HEIGHT ||
				Shipsbullets[i].x < 0 || Shipsbullets[i].x > 630.0f) {
				Shipsbullets.erase(Shipsbullets.begin() + i);
			}
		}
	}


}

void Elements::Draw() {

	if (Game::gameState == 0) {
		renderStartScreen();
	}
	else if (Game::gameState > 0 && gameStarted)
	{
		renderRightNav();
	}

	if (state == 2) {
		starterAnim();
	}

	if (state == 4) {
		reIntRocket();
	}




	if (FighterCapture) {
		Resources::fighterCaptured.render();
	}

	/* Render Bullets */

	if ((int)bullets.size() > 0) {
		for (int i = 0; i < (int)bullets.size(); i++) {
			bullets[i].Render();
		}
	}

	if ((int)Shipsbullets.size() > 0) {
		for (int i = 0; i < (int)Shipsbullets.size(); i++) {
			Shipsbullets[i].Render();
		}
	}

	for (int i = 0; i < 2; i++) {
		if (rocket[i].enabled) {
			rocket[i].render();
		}
	}


	if (state == 7) {
		gameOver();
	}

	if (state == 8) {
		bonus();
	}

	if (next) {
		Resources::stageWord.render();
		if (StageM::stage - 1 == 4) {
			Resources::stageWord.y = 200.0f;
			Resources::troll.render(250.0f, 250.0f);
		}
		showStageNum();
	}

}

void Elements::nextStage() {

	if (Elements::rocket[1].captuered) return;
	if (StageM::stage > Game::numStages+1) return;

	static Timer t;
	static int nextState = 0;
	t.start();

	if (t.checkFrameEnd(1000) && nextState == 0) {
		StageM::stage++;
		nextState = 1;
	}

	if (nextState == 1) {

		if (StageM::bonusStage) {
			Resources::stageWord.setText("CHALLENGING STAGE");
			Resources::stageWord.x = (CCFG::SCREEN_WIDTH / 2.0f) - (Resources::stageWord.sFont->w / 2.0f) - 85.0f;
		} else {
			Resources::stageWord.setText("STAGE    " + std::to_string(StageM::stage-1));
			Resources::stageWord.x = (CCFG::SCREEN_WIDTH / 2.0f) - (Resources::stageWord.sFont->w / 2.0f) - 85.0f;
		}


		next = true;
		nextState = 2;

	}


	int del = 3000;
	if (StageM::stage == 5) del = 5000;

	if (t.checkFrameEnd(del) && nextState == 2) {
		nextState = 0;
		next = false;
		t.reset();
		Elements::state = 3;
		StageM::state = 0;

	}




}

void Elements::reIntRocket() {

	static Timer tre;
	static bool soundDone = false;
	tre.start();


	if (RocketsNum == 2) {

		if (!tre.checkFrameEnd(800)) {
			CCFG::Sounds->volumeDown();
		}

		if (!rocket[0].enabled) {
			rocket[0].x = rocket[1].x;
			rocket[0].enabled = true;
			rocket[0].state = 1;
			rocket[1].enabled = false;
			rocket[0].updateBounds();
		}

		RocketsNum--;
		state = 3;

		rocketInitiated = true;
		tre.reset();
		state = 6;
		soundDone = false;

		if(StageM::state !=0){
			StageM::state = 1;
		}
		rocket[0].updateMovementBounds();
		rocket[1].updateMovementBounds();
		StageM::rocketPullAttack = false;

		CCFG::Sounds->volumeUP();
		return;
	}


	rocketInitiated = false;

	if (StageM::state == 4) {
		soundDone = true;
	}

	//Disable sounds for sometime except rocket exp
	if (!tre.checkFrameEnd(800) && !soundDone) {
		CCFG::Sounds->volumeDown();
	}
	else {
		CCFG::Sounds->volumeUP();
		soundDone = true;
	}



	//All ships must be parked
	if(StageM::state !=0){
		for (int i = 0; i < 40; i++) {
			if (StageM::ships[i].alive && !StageM::ships[i].parked) {

				if (tre.checkFrameEnd(900)) {
					tre.reset();
				}
				return;
			}
		}
	}

	if (lives == 0) {

		if(tre.checkFrameEnd(3000)){

			state = 7;
			StageM::state = 5;
			return;
		}
		return;
	}

	if (tre.checkFrameEnd(1000)) {

		if (tre.checkFrameCap(1000, 3000)) {
			Resources::readyWord.render();
		}

		if (tre.checkFrameEnd(3000)) {
			lives--;


			rocket[0].enabled = true;
			rocket[0].state = 1;
			rocket[0].setCenterPos();
			rocket[0].theta = 0.0f;


			rocketInitiated = true;
			tre.reset();
			state = 6;
			soundDone = false;

			if(StageM::state != 0){
				StageM::state = 1;
			}
		}
	}

}

void Elements::initRockets()
{
	for (int i = 0; i < 2; i++) {
		rocket[i].init();
	}
	rocket[1].enabled = false;
	//RocketsNum = 2;
}

void Elements::updateScore(unsigned int n)
{
	score += n;
	Resources::score.setText(std::to_string(score));
	Resources::score.x = (Resources::scoreWord.x + Resources::scoreWord.sFont->w) - (Resources::score.sFont->w);
}

void Elements::shoot() {

	int max = 2;
	bool f = false;
	if (RocketsNum == 2) max = 4;
	if ((int)bullets.size() < max) {
		for (int i = 0; i < 2; i++) {

			if (rocket[i].enabled && !rocket[i].captuered) {


				if ((int)bullets.size() > 0 && RocketsNum < 2) {
					if (Distance(bullets[0].x, bullets[0].y, rocket[0].x, rocket[0].y) > 50) {
						rocket[i].shootBullet();
						f = true;
					}
				}
				else {

					rocket[i].shootBullet();
					f = true;
				}


			}

		}
		if (f) CCFG::Sounds->PlayChunk(CCFG::Sounds->bullet);
		CCFG::shots++;
	}


}

void Elements::SwapRockets() {

	Rocket r = Elements::rocket[0];
	Elements::rocket[0] = Elements::rocket[1];
	Elements::rocket[1] = r;

}

void Elements::gameOver() {

	static int gState = 0;
	static Timer go;
	go.start();


	float ratio = 0.0f;

	if (CCFG::shots > 0)
		ratio = (float)CCFG::hits / (float)CCFG::shots * 100.0f;
	else
		ratio = 0;


	if (gState == 0) {
		Resources::stageWord.setText("GAME OVER");
		Resources::stageWord.x = (float)((CCFG::SCREEN_WIDTH - 160) / 2 - Resources::stageWord.sFont->w / 2);
		Resources::stageWord.y = (float)(CCFG::SCREEN_HEIGHT / 2 - Resources::stageWord.sFont->h / 2);
		gState = 1;
	}

	if (gState == 1 && go.checkFrameEnd(1000)) {
		Resources::stageWord.render();

		if (go.checkFrameEnd(9000)) {
			gState = 2;
			Elements::rocket[0].enabled = false;
			Elements::rocket[1].enabled = false;
		}
	}

	if (gState == 2) {

		Resources::resultsWord.x = (float)((CCFG::SCREEN_WIDTH - 160) / 2 - Resources::resultsWord.sFont->w / 2);
		Resources::resultsWord.y = 160.0f;

		Resources::stageWord.setText("SHOTS FIRED                        " + std::to_string(CCFG::shots));
		Resources::stageWord.x = 100.0f;
		Resources::stageWord.y = 230.0f;

		Resources::PushSpaceKey.setText("NUMBER OF HITS                  " + std::to_string(CCFG::hits));
		Resources::PushSpaceKey.x = 100.0f;
		Resources::PushSpaceKey.y = 300.0f;

		Resources::readyWord.setText("HIT-MISS RATIO                 " + std::to_string((int)ratio) + "%");
		Resources::readyWord.x = 100.0f;
		Resources::readyWord.y = 370.0f;

		Resources::developedBy.x = 20.0f;
		Resources::developedBy.y = CCFG::SCREEN_HEIGHT - 30.0f;

		CCFG::Sounds->PlayMusic(CCFG::Sounds->gameOver);
		gState = 3;
		Game::gameState = 3;
	}

	if (gState == 3) {
		Resources::resultsWord.render();
		Resources::stageWord.render();
		Resources::PushSpaceKey.render();
		Resources::readyWord.render();
		Resources::developedBy.render();
	}

}

void Elements::bonus() {

	static Timer bt;
	static Timer sc;
	static Timer pTimer;
	static int bState = -1;
	static int pts = (StageM::bonusHits == 40)?10000:StageM::bonusHits * 100;
	static float pX = 0;
	static bool perfect = (StageM::bonusHits == 40) ? true : false;
	bt.start();


	//delay
	if (bState == -1 && bt.checkFrameEnd(1000)) {
		bState = 0;
		bt.reset();
	}

	if (bState == 0 && bt.checkFrameEnd(1500)) {

		if(perfect){
			CCFG::Sounds->PlayMusic(CCFG::Sounds->perfectBonus);
		} else {
			CCFG::Sounds->PlayMusic(CCFG::Sounds->imperfectBonus);
		}


		Resources::perfectWord.x = posCenter(Resources::perfectWord, true);
		Resources::perfectWord.y = 150.0f;


		Resources::stageWord.setText("NUMBER OF HITS");
		Resources::stageWord.x = posCenter(Resources::stageWord, true) - 30.0f;
		Resources::stageWord.y = 200.0f;

		Resources::PushSpaceKey.setText((perfect)? "SPECIAL BONUS": "BONUS");
		Resources::PushSpaceKey.x = posCenter(Resources::PushSpaceKey, true);
		Resources::PushSpaceKey.y = 250.0f;

		if (perfect) {
			Resources::PushSpaceKey.glcolor[0] = Resources::readyWord.glcolor[0];
			Resources::PushSpaceKey.glcolor[1] = Resources::readyWord.glcolor[1];
			Resources::PushSpaceKey.glcolor[2] = Resources::readyWord.glcolor[2];
		}

		Resources::bonusScore.setText(std::to_string(pts) + "   PTS");
		Resources::bonusScore.x = posCenter(Resources::bonusScore, true);
		Resources::bonusScore.y = 300.0f;
		pX = Resources::bonusScore.x + Resources::bonusScore.sFont->w;

		bState = 1;
	}

	if (bState == 1) {
		Resources::stageWord.render();
		if (bt.checkFrameEnd(2200)) {
			Resources::stageWord.setText("NUMBER OF HITS    " + std::to_string(StageM::bonusHits));
		}

		if (bt.checkFrameEnd(3200)) {
			Resources::PushSpaceKey.render();
			Resources::bonusScore.render();
		}

		if (bt.checkFrameEnd(4000) && perfect) {
			pTimer.start();

			if (pTimer.checkFrameLoop(500)) {
				Resources::perfectWord.visible = (Resources::perfectWord.visible) ? 0 : 1;
			}

			if (Resources::perfectWord.visible) {
				Resources::perfectWord.render();
			}


		}

		if ((!perfect && bt.checkFrameEnd(10000)) || (perfect && bt.checkFrameEnd(7200))) {
			sc.start();
			if (sc.checkFrameLoop(30) && pts > 0) {
				int s = 200;
				if (pts < s) s = pts;

				pts -= s;
				Elements::updateScore(s);
				if(!perfect)CCFG::Sounds->PlayMusic(CCFG::Sounds->scoreUp);
				Resources::bonusScore.setText(std::to_string(pts) + "   PTS");
				Resources::bonusScore.x = pX - Resources::bonusScore.sFont->w;
			}

			if (pts == 0) {
				bState = 2;
				bt.reset();
			}
		}
	}

	if (bState == 2) {

		Resources::stageWord.render();
		Resources::PushSpaceKey.render();
		Resources::bonusScore.render();

		if(perfect){
			Resources::perfectWord.visible = true;
			Resources::perfectWord.render();
		}

		if (bt.checkFrameEnd(3000)) {
			pts = 00;
			bt.reset();
			sc.reset();

			bState = -1;
			pts = 0;
			pX = 0;

			Elements::state = 3;
			StageM::nextStage();
		}
	}

}
