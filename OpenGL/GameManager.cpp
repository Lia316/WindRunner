#include <windows.h> 
#include <gl/gl.h> 
#include <gl/glut.h>
#include <random>
#include "GameManager.h"

using namespace std;

GameManager::GameManager() {
	sceneGraph = new SceneGraph();

	isGameEnd = false;
	score = 0;
	firenum = 0;
	starnum = 0;
	groundnum = 0;
	mushnum = 0;
	groundMaxX = 0;
}

void GameManager::draw() {
	sceneGraph->draw();

	string scoreText = "score: " + to_string(score);
	showText(0, glutGet(GLUT_WINDOW_HEIGHT) - 30, scoreText);
	if (isGameEnd) {
		showText(0, glutGet(GLUT_WINDOW_HEIGHT) - 60, "The Game End");
	}
}

void GameManager::move(void(*t)(int)) {
	// 1. Character move
	Character* character = dynamic_cast<Character*>(sceneGraph->findNode(typeid(Character))->getEntity());
	character->jump();

	if (detectSink(character)) {
		//isGameEnd = true;
	}

	// 2. Ground
	SceneNode* groundGroup = sceneGraph->findGroup(typeid(Ground));
	for (auto groundNode = groundGroup->childBegin(); groundNode != groundGroup->childEnd(); ++groundNode) {
		Entity* ground = (*groundNode)->getEntity();

		ground->move();

		if (detectCollisionYpredict(character, ground)) {
			character->stop(ground);
		}
		if (!character->isJumping()) { // detectFall()
			if (detectCollisionX(character, ground)) break;
			character->setfall();
		}
		if (detectCollision(character, ground) && detectUnderobject(character, ground)) {
			//isGameEnd = true;
		}
	}

	// 3. Fire
	SceneNode* fireGroup = sceneGraph->findGroup(typeid(Fire));
	for (auto fireNode = fireGroup->childBegin(); fireNode != fireGroup->childEnd(); ++fireNode) {
		Entity* fire = (*fireNode)->getEntity();

		fire->move();

		if (detectCollision(character, fire)) {
			//isGameEnd = true;
		}
	}

	// 4. Star
	SceneNode* starGroup = sceneGraph->findGroup(typeid(Star));
	for (auto starNode = starGroup->childBegin(); starNode != starGroup->childEnd(); ++starNode) {
		Star* star = dynamic_cast<Star*>((*starNode)->getEntity());

		star->move();

		if (detectCollision(character, star)) {
			score += star->getPoint();
			delete star;
		}
	}

	// 5. Mushroom
	SceneNode* mushGroup = sceneGraph->findGroup(typeid(Mush));
	for (auto mushNode = mushGroup->childBegin(); mushNode != mushGroup->childEnd(); ++mushNode) {
		Mush* mush = dynamic_cast<Mush*>((*mushNode)->getEntity());

		mush->move();

		if (detectMushMove(mush)) {
			mush->reverse();
		}
		if (detectCollision(character, mush) && detectUnderobject(character, mush)) {
			//isGameEnd = true;
		}
		if (detectCollisionYpredict(character, mush)) {
			character->stepMush();
			delete mush;
		}
	}

	/*
	for (int i = 0; i < MAXSTAR; i++) {
		for (int j = 0; j < MAXGROUND; j++) {
			if (detectCollision(star[i],newground[j])) {
				star[i]->upper();//to prevent that stars were under the ground
			}
		}
	}

	for (int i = 0; i < MAXGROUND; i++) {
		for(int j = 0; j < MAXMUSH; j++)
		if (detectCollisionX(mush[j], newground[i])) {
			mush[j]->setY(newground[i]->getHeight());
		}
	}*/

	glutPostRedisplay();

	if (isGameEnd) {
		character->sink();
		glutPostRedisplay();
	}
	if (!isGameEnd) {
		glutTimerFunc(10, t, 0);
	}
}

// ###### Timer functions ######

void GameManager::characterAnimation(void(*t)(int)) {
	Character* character = dynamic_cast<Character*>(sceneGraph->findNode(typeid(Character))->getEntity());
	character->animation(t);
}

void GameManager::firemaker(void(*t)(int)) {
	random_device rd;
	int pos = rd() % 225 + 175;

	Entity* oldestFire = sceneGraph->findNode(typeid(Fire))->getEntity();

	if (detectWindowOut(oldestFire)) {
		delete oldestFire;
		firenum--;
	}
	if (firenum < MAXFIRE) {
		Fire* newFire = new Fire(glutGet(GLUT_WINDOW_WIDTH), pos, sceneGraph->materials->getModel(FIRE));
		SceneNode* fireNode = new SceneNode(newFire);
		sceneGraph->findGroup(typeid(Fire))->addChild(fireNode);
		firenum++;
	}
	if (!isGameEnd) {
		glutTimerFunc(FIRETIME, t, 0);
	}
}

void GameManager::starmaker(void(*t)(int)) {
	random_device rd;
	int pos = rd() % 250 + 150;

	Entity* oldestStar = sceneGraph->findNode(typeid(Star))->getEntity();

	if (detectWindowOut(oldestStar)) {
		delete oldestStar;
		starnum--;
	}
	if (starnum < MAXSTAR) {
		Star* newStar = new Star(glutGet(GLUT_WINDOW_WIDTH), pos, sceneGraph->materials->getModel(STAR));
		SceneNode* starNode = new SceneNode(newStar);
		sceneGraph->findGroup(typeid(Star))->addChild(starNode);
		starnum++;
	}
	if (!isGameEnd) {
		glutTimerFunc(STARTIME, t, 0);
	}
}

void GameManager::groundmaker(void(*t)(int)) {
	int height[20] = {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 3};
	random_device rd;
	int random = rd() % 20;

	Entity* oldestGround = sceneGraph->findNode(typeid(Ground))->getEntity();

	if (detectWindowOut(oldestGround)) {
		delete oldestGround;
		groundnum--;
	}
	if (groundnum < MAXGROUND) {
		for (int i = 0; i < height[random]; i++) {
			Ground* newGround = new Ground(groundMaxX, i, sceneGraph->materials->getModel(GROUND));
			SceneNode* groundNode = new SceneNode(newGround);
			groundNode->translate = vec3(0 , newGround->getHeight(), 0);

			sceneGraph->findGroup(typeid(Ground))->addChild(groundNode);

			groundMaxX = newGround->getPositionX() + newGround->getWidth() - 20;
			groundnum++;
		}
	}
	if (!isGameEnd) {
		glutTimerFunc(GROUNDTIME, t, 0);
	}
}

void GameManager::mushmaker(void(*t)(int)) {
	random_device rd;
	int coin = rd() % 2;

	Entity* oldestMush = sceneGraph->findNode(typeid(Mush))->getEntity();

	if (detectWindowOut(oldestMush)) {
		delete oldestMush;
		mushnum--;
	}
	if (mushnum < MAXMUSH) {
		Mush* newMush = new Mush(sceneGraph->materials->getModel(MUSHROOM));
		SceneNode* mushNode = new SceneNode(newMush);
		sceneGraph->findGroup(typeid(Mush))->addChild(mushNode);

		if (coin)
			newMush->reverse();
		mushnum++;
	}
	if (!isGameEnd) {
		glutTimerFunc(GROUNDTIME * 5 , t, 0);
	}
}

void GameManager::keyboard(unsigned char key, int x, int y) {
	Character* character = dynamic_cast<Character*>(sceneGraph->findNode(typeid(Character))->getEntity());

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

// ###### collision functions ######

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
bool GameManager::detectMushMove(Entity* mush) {
	SceneNode* groundGroup = sceneGraph->findGroup(typeid(Ground));
	for (auto groundNode = groundGroup->childBegin(); groundNode != groundGroup->childEnd(); ++groundNode) {
		Entity* ground = (*groundNode)->getEntity();

		if (detectCollisionX(mush, ground))
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