#pragma once

#ifndef CORE_H
#define CORE_H
#include "header.h"
#include "CFG.h"
#include "Game.h"

class CCore
{
private:

	SDL_Window* window;
	SDL_Event* mainEvent;
	SDL_GLContext gContext;



	// ----- Game Object
	static Game *game;


public:
	CCore(void);
	~CCore(void);

	// ----- INPUT
	static bool keyLeft, keyRight;

	static bool spaceKey;

	static bool quitGame;

	void mainLoop();
	void Input();

	void Update();
	void Draw();

};

#endif
