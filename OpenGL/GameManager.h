#pragma once
#include <string>
#include "SceneNode.h"

#define MAXFIRE 4
#define MAXSTAR 10
#define MAXGROUND 30
#define MAXMUSH 2

#define FIRETIME 2100
#define STARTIME 1000
#define GROUNDTIME 100

class GameManager {
private: 
	SceneGraph* sceneGraph;
	GLuint objectProgram;
	int viewMode;
public:
	GameManager(GLuint, GLuint);
	void draw();
	void move(void(*t)(int));
	void characterAnimation(void(*t)(int));
	void firemaker(void(*t)(int));
	void starmaker(void(*t)(int));
	void groundmaker(void(*t)(int));
	void mushmaker(void(*t)(int));

	void keyboard(unsigned char key, int x, int y);
	void viewProjectionMode();
	void viewLookMode();

	bool detectCollisionX(Entity* character, Entity* object);
	bool detectCollisionY(Entity* character, Entity* object);
	bool detectCollision(Entity* character, Entity* object);
	bool detectIntersectY(Entity* character, Entity* object);
	bool detectCollisionYpredict(Entity* character, Entity* ground);
	bool detectSink(Entity* character);
	bool detectWindowOut(Entity* object);

	bool detectUnderobject(Entity* character, Entity* ground);
	void showText(float x, float y, std::string string);

	bool isGameEnd;
	int score;
	int firenum;
	int starnum;
	int groundnum;
	int mushnum;
	float groundMaxX;
	bool isHole;
};