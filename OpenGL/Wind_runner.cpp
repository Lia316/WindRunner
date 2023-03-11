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
#include <random>

#define MAXFIRE 4
#define MAXSTAR 10

using namespace std;

Ground* ground;
Hole* hole;
Character* character;
Fire* fire[MAXFIRE];
Star* star[MAXSTAR];
bool isGameEnd = false;
int score = 0;
int firenum = 0;
int starnum = 0;

void init();
void draw();
void move(int time);
void reshape(int w, int h);
void holemaker(int time);
void firemaker(int time);
void starmaker(int time);
void keyboard(unsigned char key, int x, int y);
bool detectCollision(Entity* character, Entity* object);
bool detectSink(Entity* character, Entity* hole);
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
		glutTimerFunc(10, move, 0);
		glutTimerFunc(1300, firemaker, 0);
		glutTimerFunc(3000, holemaker, 0);
		glutTimerFunc(500, starmaker, 0);
	}
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}

void init(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);

	ground = new Ground();
	hole = new Hole();
	character = new Character();
	//fire = new Fire();
	//star = new Star();
}

void draw() {
	glClear(GL_COLOR_BUFFER_BIT);
	ground->draw();
	hole->draw();
	character->draw();
	for (int i = 0; i < MAXFIRE; i++) {
		if (fire[i] != nullptr) {
			fire[i]->draw();
		}
	}
	for (int i = 0; i < MAXSTAR; i++) {
		if (star[i] != nullptr) {
			star[i]->draw();
		}
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
	character->jump();
	for (int i = 0; i < MAXFIRE; i++) {
		if (fire[i] != nullptr) {
			fire[i]->move();
		}
	}
	for (int i = 0; i < MAXSTAR; i++) {
		if (star[i] != nullptr) {
			star[i]->move();
		}
	}
	glutPostRedisplay();

	if (detectSink(character, hole)) {
		isGameEnd = true;
	}
	for (int i = 0; i < MAXFIRE; i++) {
		if (detectCollision(character, fire[i])) {
			isGameEnd = true;
		}
	}
	for (int i = 0; i < MAXSTAR; i++) {
		if (detectCollision(character, star[i])) {
			score += star[i]->getPoint();
			delete star[i];
			star[i] = nullptr;
		}
	}

	if (!isGameEnd) {
		glutTimerFunc(10, move, 0);
	}
}

void holemaker(int time) {
	hole = new Hole();
	glutTimerFunc(3000, holemaker, 0);
}

void firemaker(int time) {
	random_device rd;
	int pos = rd() % 225 + 175;
	fire[firenum] = new Fire(glutGet(GLUT_WINDOW_WIDTH), pos);
	if (firenum == MAXFIRE - 1)
		firenum = 0;
	else
		firenum++;
	if (!isGameEnd) {
		glutTimerFunc(1300, firemaker, 0);
	}

}

void starmaker(int time) {
	random_device rd;
	int pos = rd() % 250 + 150;
	star[starnum] = new Star(glutGet(GLUT_WINDOW_WIDTH), pos);
	if (starnum == MAXSTAR - 1)
		starnum = 0;
	else
		starnum++;
	if (!isGameEnd) {
		glutTimerFunc(500, starmaker, 0);
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
	for (int i = 0; i < MAXFIRE; i++) {
		if (fire[i] != nullptr) {
			fire[i] -> reshape(h);
		}
	}
	for (int i = 0; i < MAXSTAR; i++) {
		if (star[i] != nullptr) {
			star[i]->reshape(h);
		}
	}
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 32:
		character->setjump();
	}
	glutPostRedisplay();
}

bool detectCollision(Entity* character, Entity* object) {
	if (object == nullptr) {
		return false;
	}
	bool collisionX = character->getPositionX() + character->getWidth() >= object->getPositionX() &&
		object->getPositionX() + object->getWidth() >= character->getPositionX();
	bool collisionY = character->getPositionY() + character->getHeight() >= object->getPositionY() &&
		object->getPositionY() + object->getHeight() >= character->getPositionY();

	return collisionX && collisionY;
}

bool detectSink(Entity* character, Entity* hole) {
	bool collisionX = character->getPositionX() >= hole->getPositionX() &&
		hole->getPositionX() + hole->getWidth() >= character->getPositionX() + character->getWidth();
	bool collisionY = hole->getPositionY() + hole->getHeight() >= character->getPositionY();

	return collisionX && collisionY;
}

void showText(float x, float y, std::string string) {
	glColor3f(1.0, 1.0, 1.0);
	glRasterPos2f(x, y);
	const char* str = string.c_str();

	for (const char* c = str; *c != '\0'; c++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
	}
}