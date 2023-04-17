#include <windows.h> 
#include <gl/gl.h> 
#include <gl/glut.h>
#include <random>
#include "GameManager.h"

using namespace std;

GameManager::GameManager() {
	materials = new Materials();

	Model* characterPoses[KEY_FRAME_NUM - 1] = { materials->getModel(CHARACTER1), materials->getModel(CHARACTER2), materials->getModel(CHARACTER3) };
	ground = new Ground(0, 1, materials->getModel(GROUND));
	character = new Character(characterPoses);

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
	groundMaxX = 0;
}

void GameManager::draw() {
	ground->draw();
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
	if (detectCollisionYpredict(character, ground))
		character->stop(ground);

	for (int i = 0; i < MAXGROUND; i++) {
		if (newground[i] != nullptr && detectCollisionYpredict(character, newground[i])) {
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

	for (int i = 0; i < MAXSTAR; i++) {
		for (int j = 0; j < MAXGROUND; j++) {
			if (detectCollision(star[i],newground[j])) {
				star[i]->upper();//to prevent that stars were under the ground
			}
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

	if (detectSink(character)) {
		//isGameEnd = true;
	}
	
	for (int i = 0; i < MAXFIRE; i++) {
		if (detectCollision(character, fire[i])) {
			//isGameEnd = true;
		}
	}
	for (int i = 0; i < MAXGROUND; i++) {
		if (detectCollision(character, newground[i]) && detectUnderobject(character, newground[i])) {
			//isGameEnd = true;
		}
	}
	for (int i = 0; i < MAXMUSH; i++) {
		if (detectCollision(character, mush[i]) && detectUnderobject(character, mush[i])) {
			//isGameEnd = true;
		}
	}
	for (int i = 0; i < MAXSTAR; i++) {
		if (detectCollision(character, star[i])) {
			score += star[i]->getPoint();
			delete star[i];
			star[i] = nullptr;
		}
	}
	for (int i = 0; i < MAXMUSH; i++) {
		if (detectCollisionYpredict(character, mush[i])) {
			character->stepMush();
			delete mush[i];
			mush[i] = nullptr;
		}
	}

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

void GameManager::firemaker(void(*t)(int)) {
	random_device rd;
	int pos = rd() % 225 + 175;
	if (fire[firenum]) delete fire[firenum];
	fire[firenum] = new Fire(glutGet(GLUT_WINDOW_WIDTH), pos, materials->getModel(FIRE));

	if (firenum == MAXFIRE - 1)
		firenum = 0;
	else
		firenum++;
	if (!isGameEnd) {
		glutTimerFunc(FIRETIME, t, 0);
	}
}

void GameManager::starmaker(void(*t)(int)) {
	random_device rd;
	int pos = rd() % 250 + 150;

	if (star[starnum]) delete star[starnum];
	star[starnum] = new Star(glutGet(GLUT_WINDOW_WIDTH), pos, materials->getModel(STAR));

	if (starnum == MAXSTAR - 1)
		starnum = 0;
	else
		starnum++;
	if (!isGameEnd) {
		glutTimerFunc(STARTIME, t, 0);
	}
}

void GameManager::groundmaker(void(*t)(int)) {
	int height[20] = {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 3};
	random_device rd;
	int random = rd() % 20;

	for (int i = 0; i < height[random]; i++) {
		if (newground[groundnum]) delete newground[groundnum];
		newground[groundnum] = new Ground(groundMaxX, i, materials->getModel(GROUND));
		groundMaxX = newground[groundnum]->getPositionX() + newground[groundnum]->getWidth() - 20;

		if (groundnum == MAXGROUND - 1)
			groundnum = 0;
		else
			groundnum++;
	}
	if (!isGameEnd) {
		glutTimerFunc(GROUNDTIME, t, 0);
	}
}

void GameManager::mushmaker(void(*t)(int)) {
	random_device rd;
	int coin = rd() % 2;
	if (mush[mushnum]) delete mush[mushnum];
	mush[mushnum] = new Mush(materials->getModel(MUSHROOM));

	if (coin)
		mush[mushnum]->reverse();
	if (mushnum == MAXMUSH - 1)
		mushnum = 0;
	else
		mushnum++;
	if (!isGameEnd) {
		glutTimerFunc(GROUNDTIME * 5 , t, 0);
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
	if (character == nullptr || object == nullptr) {
		return false;
	}
	bool collisionY = character->getPositionY() + character->getHeight() > object->getPositionY() &&
		object->getPositionY() + object->getHeight() > character->getPositionY();
	return collisionY;
}

bool GameManager::detectCollisionYpredict(Entity* character, Entity* object) { // predict Character's next y pos, and then predict if it were crashed with ground.
	if (object == nullptr) {
		return false;
	}
	bool collisionY = object->getPositionY() + object->getHeight() > character->getPositionY() + character->getSpeed();
	return collisionY && detectCollisionX(character, object);
}

bool GameManager::detectCollision(Entity* character, Entity* object) {
	if (character == nullptr || object == nullptr) {
		return false;
	}
	return detectCollisionX(character,object) && detectCollisionY(character, object);
}

bool GameManager::detectUnderobject(Entity* character, Entity* object) {
	if (character == nullptr || object == nullptr) {
		return false;
	}
	bool checkY = character->getPositionY() < object->getPositionY() + object->getHeight();
	return checkY && detectCollisionX(character, object);
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

bool GameManager::detectMushStep(Entity* character, Entity* mush) {
	return false;
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

bool GameManager::detectWindowOut(Entity* object) {
	if (object == nullptr) 
		return false;
	return object->getPositionX() + object->getWidth() <= 0;
}

void GameManager::showText(float x, float y, std::string string) {
	glColor3f(1.0, 1.0, 1.0);
	glRasterPos2f(x, y);
	const char* str = string.c_str();

	for (const char* c = str; *c != '\0'; c++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
	}
}