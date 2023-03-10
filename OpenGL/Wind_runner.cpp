#include <windows.h> 
#include <gl/gl.h> 
#include <gl/glut.h>
#include<string>
#include "Entity.h"
#include "Ground.h"
#include "Hole.h"
#include "Character.h"
#include "Fire.h"
#include "Star.h"

Ground* ground;
Hole* hole;
Character* character;
Fire* fire;
Star* star;
bool isGameEnd = false;
int score = 0;

void init();
void draw();
void move(int time);
void reshape(int w, int h);
bool detectCollision(Entity* character, Entity* object);
void showText(float x, float y, std::string string);

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Wind Runner");
	init();
	glutDisplayFunc(draw);
	glutReshapeFunc(reshape);
	if (!isGameEnd) {
		glutTimerFunc(1, move, 0);
	}
	glutMainLoop();
	return 0;
}

void init(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);

	ground = new Ground();
	hole = new Hole();
	character = new Character();
	fire = new Fire();
	star = new Star();
}

void draw() {
	glClear(GL_COLOR_BUFFER_BIT);
	ground->draw();
	hole->draw();
	character->draw();
	if (fire != nullptr) {
		fire->draw();
	}
	if (star != nullptr) {
		star->draw();
	}
	std::string scoreText = "score: " + std::to_string(score);
	showText(0, 30, scoreText);
	if (isGameEnd) {
		showText(0, 60, "The Game End");
	}
	glutSwapBuffers();
}

void move(int time) {
	hole->move();
	if (fire != nullptr) {
		fire->move();
	}
	if (star != nullptr) {
		star->move();
	}
	glutPostRedisplay();

	if (detectCollision(character, hole)) {
		isGameEnd = true;
	}
	if (detectCollision(character, fire)) {
		isGameEnd = true;
		delete fire;
		fire = nullptr;
	}
	if (detectCollision(character, star)) {
		score += star->getPoint();
		delete star;
		star = nullptr;
	}

	if (!isGameEnd) {
		glutTimerFunc(1, move, 0);
	}
}

void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, w, 0, h, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	ground->reshape(w, h);
	hole->reshape(h);
	character->reshape(h);
	if (fire != nullptr) {
		fire->reshape(h);
	}
	if (star != nullptr) {
		star->reshape(h);
	}
}

bool detectCollision(Entity* character, Entity* object) {
	if (object == nullptr) {
		return false;
	}
	return character->getPositionX() + character->getWidth() >= object->getPositionX();
}

void showText(float x, float y, std::string string) {
	glColor3f(1.0, 1.0, 1.0);
	glRasterPos2f(x, y);
	const char* str = string.c_str();

	for (const char* c = str; *c != '\0'; c++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
	}
}