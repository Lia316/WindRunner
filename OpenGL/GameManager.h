#pragma once
#include<string>
#include "Entity.h"
#include "Ground.h"
#include "Hole.h"
#include "Character.h"
#include "Fire.h"
#include "Star.h"

#define MAXFIRE 4
#define MAXSTAR 10

class GameManager {
public:
	GameManager();
	void draw();
	void move(void(*t)(int));
	void characterAnimation(void(*t)(int));
	void holemaker(void(*t)(int));
	void firemaker(void(*t)(int));
	void starmaker(void(*t)(int));
	void keyboard(unsigned char key, int x, int y);

	bool detectCollisionX(Entity* character, Entity* object);
	bool detectCollisionY(Entity* character, Entity* object);
	bool detectCollision(Entity* character, Entity* object);
	bool detectSink(Entity* character, Entity* hole);

	void showText(float x, float y, std::string string);

	Ground* ground;
	Hole* hole;
	Character* character;
	Fire* fire[MAXFIRE];
	Star* star[MAXSTAR];

	bool isGameEnd;
	int score;
	int firenum;
	int starnum;
};