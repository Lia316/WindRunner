#include <windows.h> 
#include <gl/gl.h> 
#include <gl/glut.h>
#include "Entity.h"

Entity::Entity(float x, float y, float width, float height, float speed)
: x(x), y(y), width(width), height(height), speed(speed) { }

void Entity::move() {
	x += speed;
}

void Entity::draw() {
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(x, y, 0);
	glPopMatrix();
}
