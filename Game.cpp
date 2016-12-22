#include "Game.h"
#include "physix.h"

/* ******************************************** */

short  Game::gameState = 0;
int  Game::lives = 3;
int  Game::numStages = 4;
Elements Game::mainElements = Elements();



Game::Game() {
	this->starsfield.initSpace();
	mainElements.initElements();

	/*--DUMMY---*/
/*
	mainElements.initRockets();
	Elements::rocketInitiated = true;
	mainElements.initRightNav();
	mainElements.state = 3;
	//mainElements.state = 8;
	mainElements.gameStarted = true;
	gameState = 2;
	*/

}

Game::~Game(){}



void Game::Draw(){
	//Show StarsField

	starsfield.Render();



	if (gameState ==2 && stageManager.initiated) {
		stageManager.Draw();
	}

	mainElements.Draw();


}

void Game::update() {
	this->starsfield.Update();
	mainElements.Update();


	if (gameState == 2) {

		if(stageManager.initiated == false){
			stageManager.Init();
			stageManager.initiated = true;
		}
		else {
			stageManager.Update();
		}

	}

}

void Game::Start() {
	this->gameState = 1;
	mainElements.state = 1;
}
