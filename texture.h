#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H
#include "header.h"

//Texture wrapper class
class LTexture
{
public:
	//Initializes variables
	LTexture();

	//Deallocates memory
	~LTexture();

	//Loads image at specified path
	bool loadFromFile(std::string path);
	void render(GLfloat x, GLfloat y, float color[3] = NULL);
	void renderCenter(GLfloat x, GLfloat y, float color[3] = NULL, GLfloat angle = 0.0f);

	void renderFrame(int frame, float x, float y, GLfloat angle = 0.0f);

	//Gets image dimensions
	int getWidth();
	int getHeight();
	void setWidth(int w);
	void setHeight(int h);
	GLfloat cellWidth = 0.0f;
	GLfloat cellHeight = 0.0f;
	float x;
	float y;
	GLuint texture = 0;  //this is a handle to our texture object
	GLenum texture_format = 0;
	GLint nofcolors;
	GLfloat angle;

private:

	//Image dimensions
	int mWidth;
	int mHeight;
};



#endif // !TEXTURE_H

