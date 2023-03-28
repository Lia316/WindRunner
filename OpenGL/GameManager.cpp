#include <windows.h> 
#include <gl/gl.h> 
#include <gl/glut.h>
#include <random>
#include "GameManager.h"

using namespace std;

GameManager::GameManager() {
	ground = new Ground();
	//hole = new Hole();
	character = new Character();
	fill_n(fire, MAXFIRE, nullptr);
	fill_n(star, MAXSTAR, nullptr);
	fill_n(newground, MAXGROUND, nullptr);
	fill_n(mush, MAXMUSH, nullptr);
	isGameEnd = false;
	score = 0;
	firenum = 0;
	starnum = 0;
	groundnum = 0;
	mushnum = 0;
}

void GameManager::draw() {
	ground->draw();
	//hole->draw();
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

	for (int i = 0; i < MAXGROUND; i++) {
		if (newground[i] != nullptr) {
			newground[i]->draw();
		}
	}

	for (int i = 0; i < MAXMUSH; i++) {
		if (mush[i] != nullptr) {
			mush[i]->draw();
		}
	}
	string scoreText = "score: " + to_string(score);
	showText(0, glutGet(GLUT_WINDOW_HEIGHT) - 30, scoreText);
	if (isGameEnd) {
		showText(0, glutGet(GLUT_WINDOW_HEIGHT) - 60, "The Game End");
	}
}

void GameManager::move(void(*t)(int)) {
	ground->move();
	//hole->move();
	if (detectCollisionYground(character, ground))
		character->stop(ground);

	for (int i = 0; i < MAXGROUND; i++) {
		if (newground[i] != nullptr && detectCollisionYground(character, newground[i])) {
			character->stop(newground[i]);
		}
	}
	if (detectFall(character, ground, newground))
	  character->setfall();

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
	for (int i = 0; i < MAXGROUND; i++) {
		if (newground[i] != nullptr) {
			newground[i]->move();
		}
	}
	for (int i = 0; i < MAXGROUND; i++) {
		for(int j = 0; j < MAXMUSH; j++)
		if (detectCollisionX(mush[j], newground[i])) {
			mush[j]->setY(newground[i]->getHeight());
		}
	}
	for (int i = 0; i < MAXMUSH; i++) {
		if (mush[i] != nullptr) {
			mush[i]->move();
		}
	}
	for (int i = 0; i < MAXMUSH; i++) {
		if (detectMushMove(mush[i],newground)) {
			mush[i]->reverse();
		}
	}
	glutPostRedisplay();

	if (detectSink(character)) {
		isGameEnd = true;
	}
	
	//for (int i = 0; i < MAXFIRE; i++) {
	//	if (detectCollision(character, fire[i])) {
	//		isGameEnd = true;
	//	}
	//}테스트를 위해 임시로 비활성화
	
	for (int i = 0; i < MAXGROUND; i++) {
		if (detectCollision(character, newground[i]) && detectUnderground(character, newground[i])) {
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

	//for (int i = 0; i < MAXMUSH; i++) {
	//	if (detectCollision(character, mush[i])) {
	//		if()
	//	}
	//}

	glutPostRedisplay();

	if (isGameEnd) {
		character->sink();
		glutPostRedisplay();
	}
	if (!isGameEnd) {
		glutTimerFunc(10, t, 0);
	}
}

void GameManager::characterAnimation(void(*t)(int)) {
	character->animation(t);
}

//void GameManager::holemaker(void(*t)(int)) {
//	hole = new Hole();
//	glutTimerFunc(3000, t, 0);
//}

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
		glutTimerFunc(1000, t, 0);
	}
}

void GameManager::groundmaker(void(*t)(int)) {
	random_device rd;
	int height = rd() % (glutGet(GLUT_WINDOW_WIDTH)/2) + glutGet(GLUT_WINDOW_WIDTH) / 4 + 1;
	newground[groundnum] = new Ground(height); 
	if (groundnum == MAXGROUND - 1)
		groundnum = 0;
	else
		groundnum++;
	if (!isGameEnd) {
		glutTimerFunc(GROUNDTIME, t, 0);
	}
}

void GameManager::mushmaker(void(*t)(int)) {
	mush[mushnum] = new Mush();
	if (mushnum == MAXMUSH - 1)
		mushnum = 0;
	else
		mushnum++;
	if (!isGameEnd) {
		glutTimerFunc(GROUNDTIME * 2 , t, 0);
	}
}

void GameManager::keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 32:
		int mod = glutGetModifiers();
		if (mod == GLUT_ACTIVE_SHIFT)
			character->setjump();
		else
			character->setlowjump();
	}
	glutPostRedisplay();
}



bool GameManager::detectCollisionX(Entity* character, Entity* object) {
	if (character == nullptr || object == nullptr) {
		return false;
	}
	bool collisionX = character->getPositionX() + character->getWidth() > object->getPositionX() &&
		object->getPositionX() + object->getWidth() > character->getPositionX();
	return collisionX;
}

bool GameManager::detectCollisionY(Entity* character, Entity* object) {
	if (object == nullptr) {
		return false;
	}
	bool collisionY = character->getPositionY() + character->getHeight() > object->getPositionY() &&
		object->getPositionY() + object->getHeight() > character->getPositionY();
	return collisionY;
}

bool GameManager::detectCollisionYground(Entity* character, Entity* ground) { // predict Character's next y pos, and then predict if it were crashed with ground.
	if (ground == nullptr) {
		return false;
	}
	bool collisionY = ground->getHeight() > character->getPositionY() + character->getSpeed();
	return collisionY && detectCollisionX(character, ground);
}

bool GameManager::detectCollision(Entity* character, Entity* object) {
	return detectCollisionX(character,object) && detectCollisionY(character, object);
}

bool GameManager::detectUnderground(Entity* character, Entity* ground) {
	bool checkY = character->getPositionX() < ground->getHeight();
	return checkY && detectCollisionX(character, ground);
}

bool GameManager::detectSink(Entity* character) {
	if (character->getPositionY() <=0)
		return true;
	else
		return false;
}

bool GameManager::detectFall(Character* character, Ground* ground, Ground** newground) {
	if (detectCollisionX(character, ground))
		return false;
	if (character->isJumping())
		return false;
	for (int i = 0; i < MAXGROUND; i++) {
		if (detectCollisionX(character, newground[i]))
			return false;
	}
	return true;
}

bool GameManager::detectMushMove(Entity* mush, Ground** newground) {
	if (mush == nullptr)
		return false;
	for (int i = 0; i < MAXGROUND; i++) {
		if (detectCollisionX(mush, newground[i]))
			return false;
	}
	return true;
}

void GameManager::showText(float x, float y, std::string string) {
	glColor3f(1.0, 1.0, 1.0);
	glRasterPos2f(x, y);
	const char* str = string.c_str();

	for (const char* c = str; *c != '\0'; c++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
	}
}