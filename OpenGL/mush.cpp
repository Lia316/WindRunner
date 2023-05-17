#include "Mush.h"

Mush::Mush(Model* model, GLuint shaderProgram)
	: Entity(glutGet(GLUT_WINDOW_WIDTH), 400, 0, -4.5, model, shaderProgram) { 
	const char* file[] = { "C:/Users/light/source/repos/textured_mesh/mushroom.bmp" ,
		 "C:/Users/light/source/repos/textured_mesh/fire_ball/M_ContentWindow_N.bmp" ,
		 "C:/Users/light/source/repos/textured_mesh/fire_ball/M_ContentWindow_S.bmp" };
	loadTexture(file, 3);
}

void Mush::draw() {
	glColor3f(2.0, 0.55, 0.0);
	Entity::draw();
}

void Mush::setY(float posY) {
	y = posY;
}

void Mush::reverse() {//reverse direction
	if (this->speed < -3.5)
		this->speed = -2.5;
	else
		this->speed = -4.5;
}
