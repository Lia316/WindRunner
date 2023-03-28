#pragma once
#include "Entity.h"

class Star : public Entity {
protected:
	int point;
public:
	Star(float x, float y);
	void draw();
	void move();
	int getPoint();
	void upper();
};