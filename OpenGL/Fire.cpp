#include <windows.h> 
#include <gl/gl.h> 
#include <gl/glut.h>
#include "Fire.h"

Fire::Fire(float x, float y, Model* model)
	: Entity(x, y, 0, -10, model) { }

void Fire::draw() {
	if (model == nullptr)
		return;

	glColor3f(9.0, 0.0, 0.0);
	glPushMatrix();
		glTranslatef(x, y, 0);
		glutSolidSphere(15, 15, 15);
	glPopMatrix();
	//Entity::draw();
}
