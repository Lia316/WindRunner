#pragma once
#include <string>
#include "Entity.h"
#include "Ground.h"
#include "Character.h"
#include "Fire.h"
#include "Star.h"
#include "Mush.h"

#define MAXFIRE 4
#define MAXSTAR 10
#define MAXGROUND 4
#define MAXMUSH 4

#define FIRETIME 2100
#define STARTIME 1000
#define GROUNDTIME 1700

class GameManager {
public:
	GameManager();
	void draw();
	void move(void(*t)(int));
	void characterAnimation(void(*t)(int));
	void firemaker(void(*t)(int));
	void starmaker(void(*t)(int));
	void groundmaker(void(*t)(int));
	void mushmaker(void(*t)(int));

	void keyboard(unsigned char key, int x, int y);

	bool detectCollisionX(Entity* character, Entity* object);
	bool detectCollisionY(Entity* character, Entity* object);
	bool detectCollisionYpredict(Entity* character, Entity* ground);
	bool detectCollision(Entity* character, Entity* object);
	bool detectSink(Entity* character);
	bool detectMushMove(Entity* mush, Ground** newground);
	bool detectMushStep(Entity* character, Entity* mush);

	bool detectFall(Character* character, Ground* ground, Ground** newground);
	bool detectUnderobject(Entity* character, Entity* ground);
	void showText(float x, float y, std::string string);

	Ground* ground;
	Character* character;
	Fire* fire[MAXFIRE];
	Star* star[MAXSTAR];
	Ground* newground[MAXGROUND];
	Mush* mush[MAXMUSH];

	bool isGameEnd;
	int score;
	int firenum;
	int starnum;
	int groundnum;
	int mushnum;
};