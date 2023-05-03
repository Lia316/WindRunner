#include "Ground.h"

Ground::Ground(float posX, int height, Model* model, GLuint shaderProgram)
	: Entity(glutGet(GLUT_WINDOW_WIDTH), 0, 0, -3.5, model, shaderProgram) {
	x = posX;
	y = height * getHeight();
}

void Ground::draw() {
	glColor3f(0.7f, 0.5f, 0.3f);
	Entity::draw();
}
