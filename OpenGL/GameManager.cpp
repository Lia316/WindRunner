#include <windows.h> 
#include <gl/gl.h> 
#include <gl/glut.h>
#include <random>
#include "GameManager.h"

using namespace std;

GameManager::GameManager() {
	ground = new Ground();
	hole = new Hole();
	character = new Character();
	fill_n(fire, MAXFIRE, nullptr);
	fill_n(star, MAXSTAR, nullptr);

	isGameEnd = false;
	score = 0;
	firenum = 0;
	starnum = 0;
}

void GameManager::draw() {
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
	string scoreText = "score: " + to_string(score);
	showText(0, 30, scoreText);
	if (isGameEnd) {
		showText(0, 60, "The Game End");
	}
}

void GameManager::move(void(*t)(int)) {
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

	if (isGameEnd) {
		character->sink();
		glutPostRedisplay();
	}
	if (!isGameEnd) {
		glutTimerFunc(10, t, 0);
	}
}

void GameManager::holemaker(void(*t)(int)) {
	hole = new Hole();
	glutTimerFunc(3000, t, 0);
}

void GameManager::firemaker(void(*t)(int)) {
	random_device rd;
	int pos = rd() % 225 + 175;
	fire[firenum] = new Fire(glutGet(GLUT_WINDOW_WIDTH), pos);
	if (firenum == MAXFIRE - 1)
		firenum = 0;
	else
		firenum++;
	if (!isGameEnd) {
		glutTimerFunc(1300, t, 0);
	}
}

void GameManager::starmaker(void(*t)(int)) {
	random_device rd;
	int pos = rd() % 250 + 150;
	star[starnum] = new Star(glutGet(GLUT_WINDOW_WIDTH), pos);
	if (starnum == MAXSTAR - 1)
		starnum = 0;
	else
		starnum++;
	if (!isGameEnd) {
		glutTimerFunc(500, t, 0);
	}
}

void GameManager::reshape(int w, int h) {
	ground->reshape(w, h);
	hole->reshape(h);
	character->reshape(h);

	for (int i = 0; i < MAXFIRE; i++) {
		if (fire[i] != nullptr) {
			fire[i]->reshape(h);
		}
	}
	for (int i = 0; i < MAXSTAR; i++) {
		if (star[i] != nullptr) {
			star[i]->reshape(h);
		}
	}
}

void GameManager::keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 32:
		character->setjump();
	}
	glutPostRedisplay();
}

bool GameManager::detectCollision(Entity* character, Entity* object) {
	if (object == nullptr) {
		return false;
	}
	bool collisionX = character->getPositionX() + character->getWidth() >= object->getPositionX() &&
		object->getPositionX() + object->getWidth() >= character->getPositionX();
	bool collisionY = character->getPositionY() + character->getHeight() >= object->getPositionY() &&
		object->getPositionY() + object->getHeight() >= character->getPositionY();

	return collisionX && collisionY;
}

bool GameManager::detectSink(Entity* character, Entity* hole) {
	bool collisionX = character->getPositionX() >= hole->getPositionX() &&
		hole->getPositionX() + hole->getWidth() >= character->getPositionX() + character->getWidth();
	bool collisionY = hole->getPositionY() + hole->getHeight() >= character->getPositionY();

	return collisionX && collisionY;
}

void GameManager::showText(float x, float y, std::string string) {
	glColor3f(1.0, 1.0, 1.0);
	glRasterPos2f(x, y);
	const char* str = string.c_str();

	for (const char* c = str; *c != '\0'; c++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
	}
}