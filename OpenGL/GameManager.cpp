#include <random>
#include "GameManager.h"

using namespace std;

GameManager::GameManager(GLuint* objectShader, GLuint* lightShader) {
	objectProgram = objectShader;
	sceneGraph = new SceneGraph(objectShader, lightShader);
	text = new Text2D("Holstein.DDS");

	viewMode = 1;
	isGameEnd = false;
	score = 0;
	firenum = 0;
	starnum = 0;
	groundnum =0;
	mushnum = 0;

	groundMaxX = 1000;
	isHole = false;
	lightAngle = 0;
}

// ###### Draw ######

void GameManager::draw() {
	glUseProgram(*objectProgram);
	sceneGraph->draw();
}

void GameManager::drawText() {
	glUseProgram(text->getProgramID());
	string scoreText = isGameEnd ? "Game Over" : "score: " + to_string(score);
	text->printText2D(scoreText.c_str(), 20, 50, 20);

	glUseProgram(0);
}

// ###### Update ######

void GameManager::move(void(*t)(int)) {
	SceneNode* groundGroup = sceneGraph->findGroup(typeid(Ground));
	SceneNode* fireGroup = sceneGraph->findGroup(typeid(Fire));
	SceneNode* starGroup = sceneGraph->findGroup(typeid(Star));
	SceneNode* mushGroup = sceneGraph->findGroup(typeid(Mush));
	SceneNode* lightGroup = sceneGraph->findGroup(typeid(PointLight));

	// 1. Character move
	Character* character = dynamic_cast<Character*>(sceneGraph->findNode(typeid(Character))->getEntity());
	character->jump();

	if (detectSink(character)) {
		isGameEnd = true;
	}

	// 2. Ground
	bool fallFlag = true;
	for (auto groundNode = groundGroup->childBegin(); groundNode != groundGroup->childEnd(); ++groundNode) {
		Entity* ground = (*groundNode)->getEntity();

		ground->move();

		if (character->isJumping() && detectCollisionYpredict(character, ground)) {
			float groundHeight = ground->getHeight() + ground->getPositionY();
			character->stop(groundHeight);
		}
		else if (fallFlag && detectIntersectY(character, ground)) {
			fallFlag = false;
		}

		for (auto mushNode = mushGroup->childBegin(); mushNode != mushGroup->childEnd(); ++mushNode) {
			Mush* mush = dynamic_cast<Mush*>((*mushNode)->getEntity());
			if (detectCollisionX(mush, ground)) {
				float groundHeight = ground->getPositionY() + ground->getHeight();
				mush->setY(groundHeight);
				mush->reverse();
			}
		}
		for (auto starNode = starGroup->childBegin(); starNode != starGroup->childEnd(); ++starNode) {
			Star* star = dynamic_cast<Star*>((*starNode)->getEntity());
			if (detectCollision(star, ground)) {
				star->upper(); //to prevent that stars were under the ground
			}
		}
		if (detectCollision(character, ground) && detectUnderobject(character, ground)) {
			isGameEnd = true;
		}
	}
	if (fallFlag && !character->isJumping()) {
		character->setfall();
	}
	if (groundGroup->isChild()) {
		Entity* lastGround = (*prev((groundGroup->childEnd())))->getEntity();
		groundMaxX = lastGround->getPositionX() + lastGround->getWidth();
		if (isHole)
			groundMaxX += lastGround->getWidth();
	}

	// 3. Fire
	for (auto fireNode = fireGroup->childBegin(); fireNode != fireGroup->childEnd(); ++fireNode) {
		Entity* fire = (*fireNode)->getEntity();

		fire->move();

		if (detectCollision(character, fire)) {
			isGameEnd = true;
		}
	}

	// 4. Star
	for (auto starNode = starGroup->childBegin(); starNode != starGroup->childEnd(); ++starNode) {
		Star* star = dynamic_cast<Star*>((*starNode)->getEntity());

		star->move();

		if (detectCollision(character, star)) {
			score += star->getPoint();
			starGroup->deleteChild(*starNode);
			starnum--;
			break; // if not, out of idx
		}
	}

	// 5. Mushroom
	for (auto mushNode = mushGroup->childBegin(); mushNode != mushGroup->childEnd(); ++mushNode) {
		Mush* mush = dynamic_cast<Mush*>((*mushNode)->getEntity());

		mush->move();

		if (detectCollision(character, mush) && detectUnderobject(character, mush)) {
			isGameEnd = true;
		}
		if (detectCollisionYpredict(character, mush)) {
			character->stepMush();
			mushGroup->deleteChild(*mushNode);
			mushnum--;
			break;
		}
	}

	// 6. Point Light
	PointLight* light = dynamic_cast<PointLight*>(sceneGraph->findNode(typeid(PointLight))->getEntity());

	lightAngle += 0.05;
	if (lightAngle >= 360) 
		lightAngle -= 360;

	vec3 characterPos = character->getPosition();
	light->rotate(characterPos, lightAngle);
	vec4 lightPos = vec4(light->getPosition(), 1.0f);

	GLuint pointLightLoc = glGetUniformLocation(*objectProgram, "lightPosition");
	glUniform4fv(pointLightLoc, 1, &lightPos[0]);

	if (isGameEnd) {
		character->sink();
		glutPostRedisplay();
	}
	if (!isGameEnd) {
		glutPostRedisplay();
		glutTimerFunc(10, t, 0);
	}
}

void GameManager::keyboard(unsigned char key, int x, int y) {
	Character* character = dynamic_cast<Character*>(sceneGraph->findNode(typeid(Character))->getEntity());

	switch (key) {
	case '1':
		viewMode = 1;
		break;
	case '2':
		viewMode = 2;
		break;
	case '3':
		viewMode = 3;
		break;
	case 32:
		int mod = glutGetModifiers();
		if (mod == GLUT_ACTIVE_SHIFT)
			character->setjump();
		else
			character->setlowjump();
	}
	glutPostRedisplay();
}

void GameManager::viewProjectionMode() {
	switch (viewMode) {
	case 1:
		gluPerspective(60.0, 2.0, 1.0, 1000.0);
		break;
	case 2:
		gluPerspective(60.0, 2.0, 1.0, 700.0);
		break;
	case 3:
		glOrtho(0.0, 1000.0, 0.0, 500.0, -200.0, 200.0);
		break;
	}
}

void GameManager::viewLookMode() {
	switch (viewMode) {
	case 1:
		glTranslatef(0, -100, 0);
		gluLookAt(-300, 150, 0, 0, 0, 0, 0, 1, 0);
		break;
	case 2:
		glTranslatef(-500, -250, 0);
		gluLookAt(0, 0, 500, 0, 0, 0, 0, 1, 0);
		break;
	case 3:
		gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);
		break;
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

	Entity* oldestFire = sceneGraph->findNodeEntity(typeid(Fire));
	SceneNode* fireGroup = sceneGraph->findGroup(typeid(Fire));
	SceneNode* fireNode = sceneGraph->findNode(typeid(Fire));

	if (detectWindowOut(oldestFire)) {
		fireGroup->deleteChild(fireNode);
		firenum--;
	}
	if (firenum < MAXFIRE) {
		Fire* newFire = new Fire(glutGet(GLUT_WINDOW_WIDTH), pos, sceneGraph->materials->getModel(FIRE), objectProgram);
		SceneNode* fireNode = new SceneNode(newFire);
		sceneGraph->addChild(fireGroup, fireNode);
		firenum++;
	}
	if (!isGameEnd) {
		glutTimerFunc(FIRETIME, t, 0);
	}
}

void GameManager::starmaker(void(*t)(int)) {
	random_device rd;
	int pos = rd() % 250 + 150;

	Entity* oldestStar = sceneGraph->findNodeEntity(typeid(Star));
	SceneNode* starGroup = sceneGraph->findGroup(typeid(Star));
	SceneNode* starNode = sceneGraph->findNode(typeid(Star));

	if (detectWindowOut(oldestStar)) {
		starGroup->deleteChild(starNode);
		starnum--;
	}
	if (starnum < MAXSTAR) {
		Star* newStar = new Star(glutGet(GLUT_WINDOW_WIDTH), pos, sceneGraph->materials->getModel(STAR), objectProgram);
		SceneNode* starNode = new SceneNode(newStar);
		sceneGraph->addChild(starGroup, starNode);
		starnum++;
	}
	if (!isGameEnd) {
		glutTimerFunc(STARTIME, t, 0);
	}
}

void GameManager::groundmaker(void(*t)(int)) {
	int height[20] = {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 3};
	random_device rd;
	int random = rd() % 20;

	Entity* oldestGround = sceneGraph->findNodeEntity(typeid(Ground));
	SceneNode* groundGroup = sceneGraph->findGroup(typeid(Ground));
	SceneNode* groundNode = sceneGraph->findNode(typeid(Ground));

	if (detectWindowOut(oldestGround)) {
		groundGroup->deleteChild(groundNode);
		groundnum--;
	}
	if (groundnum < MAXGROUND) {
		for (int i = 0; i < height[random]; i++) {
			Ground* newGround = new Ground(groundMaxX, i, sceneGraph->materials->getModel(GROUND), objectProgram);
			SceneNode* groundNode = new SceneNode(newGround);

			sceneGraph->addChild(groundGroup, groundNode);
			groundnum++;
		}
		isHole = !height[random];
	}
	if (!isGameEnd) {
		glutTimerFunc(GROUNDTIME, t, 0);
	}
}

void GameManager::mushmaker(void(*t)(int)) {
	random_device rd;
	int coin = rd() % 2;

	Entity* oldestMush = sceneGraph->findNodeEntity(typeid(Mush));
	SceneNode* mushGroup = sceneGraph->findGroup(typeid(Mush));
	SceneNode* mushNode = sceneGraph->findNode(typeid(Mush));

	if (detectWindowOut(oldestMush)) {
		mushGroup->deleteChild(mushNode);
		mushnum--;
	}
	if (mushnum < MAXMUSH) {
		Mush* newMush = new Mush(sceneGraph->materials->getModel(MUSHROOM), objectProgram);
		SceneNode* mushNode = new SceneNode(newMush);
		sceneGraph->addChild(mushGroup, mushNode);

		if (coin)
			newMush->reverse();
		mushnum++;
	}
	if (!isGameEnd) {
		glutTimerFunc(GROUNDTIME * 5 , t, 0);
	}
}

// ###### Collision functions ######

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

bool GameManager::detectCollision(Entity* character, Entity* object) {
	if (character == nullptr || object == nullptr) {
		return false;
	}
	return detectCollisionX(character, object) && detectCollisionY(character, object);
}

bool GameManager::detectIntersectY(Entity* character, Entity* object) {
	if (character == nullptr || object == nullptr) {
		return false;
	}
	bool intersectY = object->getPositionY() + object->getHeight() + 1 >= character->getPositionY();
	return intersectY && detectCollisionX(character, object);
}

bool GameManager::detectCollisionYpredict(Entity* character, Entity* object) { // predict Character's next y pos, and then predict if it were crashed with ground.
	if (object == nullptr) {
		return false;
	}
	bool collisionY = object->getPositionY() + object->getHeight() >= character->getPositionY() + character->getSpeed();
	return collisionY && detectCollisionX(character, object);
}

bool GameManager::detectUnderobject(Entity* character, Entity* object) {
	if (character == nullptr || object == nullptr) {
		return false;
	}
	bool checkY = character->getPositionY() < object->getPositionY() + object->getHeight();
	return checkY && detectCollisionX(character, object);
}

bool GameManager::detectSink(Entity* character) {
	if (character->getPositionY() <= 55)
		return true;
	else
		return false;
}

bool GameManager::detectWindowOut(Entity* object) {
	if (object == nullptr) 
		return false;
	return object->getPositionX() + object->getWidth() <= 0;
}