#include <windows.h> 
#include <gl/gl.h> 
#include <gl/glut.h>
#include "Character.h"

Character::Character()
	: Entity(glutGet(GLUT_WINDOW_WIDTH) / 10, glutGet(GLUT_WINDOW_HEIGHT) / 4, 50, 50, 0) {
	jumpSpeed = 5;
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

}

void Character::reshape(float h) {
	Entity::reshape(x, h / 4, width, height);
}