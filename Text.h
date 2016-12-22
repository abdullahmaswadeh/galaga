#pragma once
#ifndef _RENDER_TEXT_
#define _RENDER_TEXT_

#include "header.h"
#include "CFG.h"


class Text2D
{
public:
	int size = 50;
	std::string Message = "Test Text";
	SDL_Color color = { 255, 0 , 0, 255};
	float glcolor[3] = {0.0f, 0.0f, 0.0f};
	float x = 200;
	float y = 200;
	SDL_Surface * sFont;
	TTF_Font * font;
	GLuint texture;
	bool visible = true;
	Text2D();
	~Text2D();
	void loadFont(std::string file, SDL_Color color, int size, std::string message, int x, int y);
	void render();
	void setText(std::string message);
};

#endif // !_RENDER_TEXT_