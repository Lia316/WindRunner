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
#define MAXGROUND 4

#define GROUNDTIME 1700

class GameManager {
public:
	GameManager();
	void draw();
	void move(void(*t)(int));
	void characterAnimation(void(*t)(int));
	//void holemaker(void(*t)(int));
	void firemaker(void(*t)(int));
	void starmaker(void(*t)(int));
	void groundmaker(void(*t)(int));
	void keyboard(unsigned char key, int x, int y);

	bool detectCollisionX(Entity* character, Entity* object);
	bool detectCollisionY(Entity* character, Entity* object);
	bool detectCollisionYground(Entity* character, Entity* ground);
	bool detectCollision(Entity* character, Entity* object);
	bool detectSink(Entity* character);

	bool detectFall(Character* character, Ground** newground);
	bool detectUnderground(Entity* character, Entity* ground);
	void showText(float x, float y, std::string string);

	Ground* ground;
	//Hole* hole;
	Character* character;
	Fire* fire[MAXFIRE];
	Star* star[MAXSTAR];
	Ground* newground[MAXGROUND];

	bool isGameEnd;
	int score;
	int firenum;
	int starnum;
	int groundnum;
};