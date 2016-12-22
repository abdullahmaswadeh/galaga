#include "CFG.h"
#include "shapes.h"
//Draw Player Bounds


/* ---- Shape ---- */
void shape::setColor(GLfloat R, GLfloat G, GLfloat B) {
	this->R = R;
	this->G = G;
	this->B = B;
}
/* ---- End of Shape */

//-----------------Rectangle------------//



rect::rect(GLfloat x, GLfloat y, GLfloat width, GLfloat height, GLfloat speedX, GLfloat speedY) {
	this->init(x,y,width,height,speedX,speedY);
}

rect::rect(GLfloat x, GLfloat y, GLfloat width, GLfloat height) {
	this->init(x, y, width, height, 0.0f, 0.0f);
};

rect::rect() { return; };

void rect::init(GLfloat x, GLfloat y, GLfloat width, GLfloat height, GLfloat speedX, GLfloat speedY) {
	this->width = width;
	this->height = height;
	this->x = x;
	this->y = y;
	this->speedX = speedX;
	this->speedY = speedY;
	this->vectorLeft = x - width / 2;
	this->vectorRight = x + width / 2;
	this->vectorTop = y + height / 2;
	this->vectorBottom = y - height / 2;
	this->initX = x;
	this->initY = y;

}

void rect::draw() {

	glPushMatrix();

	glTranslatef(x, y + speedY * CCFG::interpolation, 0);
	glBegin(GL_POLYGON);
	glColor3f(this->R, this->G, this->B);
	glVertex2f(-width / 2, -height / 2);
	glVertex2f(width / 2, -height / 2);
	glVertex2f(width / 2, height / 2);
	glVertex2f(-width / 2, height / 2);
	glVertex2f(-width / 2, -height / 2);
	glEnd();
	glPopMatrix();

	//update
	updateVectors();
}

void rect::updateVectors() {
	//Update Vectors
	this->vectorLeft = x - width / 2;
	this->vectorRight = x + width / 2;
	this->vectorTop = y + height / 2;
	this->vectorBottom = y - height / 2;
}

//----- End of rectangle -------//

// -- stars --//

star::star(GLfloat x, GLfloat y, GLfloat width, GLfloat height) {
	this->init(x, y, width, height, 0.0f, 0.0f);
	this->angleDir = 0.0f;
}
