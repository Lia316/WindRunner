#pragma once
#include "Entity.h"

class Star : public Entity {
protected:
	int point;
public:
	Star();
	void draw();
	void move();
	void reshape(float);
	int getPoint();
};