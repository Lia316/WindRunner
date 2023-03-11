#include <windows.h> 
#include <gl/gl.h> 
#include <gl/glut.h>
#include "Character.h"

Character::Character()
	: Entity(glutGet(GLUT_WINDOW_WIDTH) / 10, glutGet(GLUT_WINDOW_HEIGHT) / 4, 50, 50, 0) {
	jumpSpeed = 12;
	jumpState = false;
}

void Character::draw() {
	glColor3f(0.6, 0.2, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(x, y);
	glVertex2f(x + width, y);
	glVertex2f(x + width, y + height);
	glVertex2f(x, y + height);
	glEnd();
}

void Character::jump() {
	y += speed;
	if(jumpState == true)
		speed = speed - 0.4;
	if (speed <=-jumpSpeed) {
		speed = 0;
		y = glutGet(GLUT_WINDOW_HEIGHT) / 4;
		jumpState = false;
	}
}

void Character::reshape(float h) {
	Entity::reshape(x, h / 4, width, height);
}

void Character::setjump() {
	if (!jumpState) {//점프중이 아닐 때,
		speed = jumpSpeed;
		jumpState = true;
	}
}

void Character::sink() {
	y -= 10;
}